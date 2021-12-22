# Linux Kernel System Call

## Goal
The kernel address space of all processes maps into the same physical address space.
* How does the kernel maintains the above property?
* You need to design and write code to proof your claim.

## Environment

OS : Ubuntu desktop 16.04 LTS 32bit

Architecture : x86

Kernel version : 3.10

## Methods
### Idea
* Every processes will map the content before virtual address 0xc0000000 (i.e., the user space) to its own Page Global Directory(PGD)
* On the other hand, the remaining entries (i.e., the kernel space) of every processes will be map to Master Kernel Page Global Directory(MKPGD)

In linux, the kernel space will be shared by all processes, whenever a new process was created, the kernel will copy all the information from the no. 768 entires to the last entires (representing the kernel space) from process 0's PGD.

Hence we can print out the content of MKPGD from different processes, if the results printing by different processes are the same, we can prove that the kernel space of all processes map to same physical space.

### Implementation

* Use `current->mm` to get the process memory descriptor
* Get the start address of PGD using `pgd_t* pgd = mm->pgd;`
* Use a while loop to get entries of the PGD, and print out the content of each entry

### Result
![image](https://user-images.githubusercontent.com/79996909/147092893-063421c4-f262-46c2-b18c-cfc1316fbf9d.png)




## How to add system call to kernel

* Download kernel source from [kernel archive](https://www.kernel.org/)

unzip to directory /usr/src
```
sudo tar -xvf linux-3.10.5.tar.xz -C /usr/src
```

* Create directory

```
cd /usr/src/linux-3.10.14
mkdir system_call
cd system_call
```

* Create helloworld.c
```
vim helloworld.c
```

```
#include <linux/kernel.h>
asmlinkage int sys_helloworld(void) {
    printk("hello world !\n");
    return 1;
}
```

* Create Makefile to insure helloworld.c will be compiled with kernel
```
vim Makefile
```
in Makefile : 
```
obj-y := helloworld.o
```

* Modify kernel source's Makefile
```
cd ..
vim Makefile
```
in Makefile, find this line : 
```
core-y += kernel/ mm/ fs/ ipc/ security/ crypto/ block/
```
add system_call/ at the end, so the compiler knows that our new system call is in the directory `system_call`
```
core-y += kernel/ mm/ fs/ ipc/ security/ crypto/ block/ system_call/
```

* Modify system call table to include our system call
```
vim arch/x86/syscalls/syscall_32.tbl
```
add our system call at the end of the table, for example, if the original system call table ends at number 354 :
```
354    ...     ...           ...                // the last system call from original table
355    i386    helloworld    sys_helloworld     // our new system call
```

* Modify system call header
```
vim include/linux/syscalls.h
```

add this line at the bottom of the header file

```
asmlinkage int helloworld(void)
```

* Install dependencies
```
sudo apt-get install libncurses5-dev
```
```
sudo make menuconfig
```
use the original setting will be fine

* Compile kernel
```
sudo make –j clean
sudo make –j 
sudo make modules –j 
sudo make modules_install
sudo make install
```

* reboot
```
sudo reboot
```

* Write a user program to test the system call
```c=
#include <syscall.h>
#include <sys/types.h>
int main(){
    int a = syscall(355);
    return 0;
}
```

use this command to check if the krenel print the message
```
dmesg
```
It should show "hello world !".













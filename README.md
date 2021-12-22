# Linux Kernel System Call

## Goal
The kernel address space of all processes maps into the same physical address space.
* How does the kernel maintains the above property?
* You need to design and write code to proof your claim. 

## How to add system call to kernel

* Check current kernel version
```
uname -r
```

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
add system_call/ at the end, so the compiler knows that our new system call is in the directory system_call
```
core-y += kernel/ mm/ fs/ ipc/ security/ crypto/ block/ system_call/
```

* Modify system call table to include our system call
```
vim arch/x86/syscalls/syscall_32.tbl
```

```
```

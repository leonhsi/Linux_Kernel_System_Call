# Linux Kernel System Call

## Goal
The kernel address space of all processes maps into the same physical address space.
* How does the kernel maintains the above property?
* You need to design and write code to proof your claim. 

## How to add system call to kernel
* Update system
```
sudo apt-get update
sudo apt-get upgrade
```

* Check current kernel version
```
uname -r
```

* Download kernel source from [kernel archive](https://www.kernel.org/)

unzip to directory /usr/src
```
sudo tar -xvf linux-4.10.5.tar.xz -C /usr/src
```

* Create directory

```
cd /usr/src/linux-4.10.14
mkdir system_call
cd system_call
```

* Create 

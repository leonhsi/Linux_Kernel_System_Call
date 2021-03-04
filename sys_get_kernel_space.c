#include <linux/linkage.h>
#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm_types.h>
#include <asm/pgtable.h>
#include <asm/page.h>
#include <asm/current.h>

asmlinkage int sys_get_kernel_space(int first, int last, int* result){
    struct mm_struct *mm = current->mm;
    pgd_t * pgd = mm->pgd;

    unsigned long value;

    while(first <= last){
        value = pgd_val( *(pgd+first) );
        result[first] = value;
        printk("entry %d : %lx \n",first, value);
        first++;
    }
}

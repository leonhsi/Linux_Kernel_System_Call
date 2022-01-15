#include <linux/kernel.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/list.h>

DECLARE_WAIT_QUEUE_HEAD(project2_queue_1);  
DECLARE_WAIT_QUEUE_HEAD(project2_queue_2); 
DECLARE_WAIT_QUEUE_HEAD(project2_queue_3); 

asmlinkage int enter_wait_queue(int x) {

	DEFINE_WAIT(p); 
	if (x==1){

		printk("project2_queue_1\n");
		prepare_to_wait(&project2_queue_1,&p,TASK_INTERRUPTIBLE);
		printk("project2_queue_1 schedule\n");
		schedule();
		printk("project2_queue_1 exit.\n");
		return 1;
	}
	else if (x==2){

		printk("project2_queue_2\n");
		prepare_to_wait(&project2_queue_2,&p,TASK_INTERRUPTIBLE);
		printk("project2_queue_2 schedule\n"); 
		schedule();
		printk("project2_queue_2 exit.\n");
		return 1;
	}
	else {

		printk("project2_queue_3\n");
		prepare_to_wait(&project2_queue_3,&p,TASK_INTERRUPTIBLE);
		printk("project2_queue_3 schedule\n");
		schedule();
		printk("project2_queue_3 exit.\n");
		return 1;
	}
	return 0;
}

asmlinkage int clean_wait_queue(int x) {

	if (x==1){
		printk("wake up Q1 \n");
		wake_up_all(&project2_queue_1);       
		return 1;
	}
	else if (x==2){
		printk("wake up Q2 \n");
		wake_up_all(&project2_queue_2);
		return 1;
	}
	else {
		printk("wake up Q3 \n");
		wake_up_all(&project2_queue_3);
		return 1;
	}
	return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <syscall.h>
#include <time.h>  

#define _GNU_SOURCE
#define gettid() syscall(SYS_gettid)                        

void main()
{
	int random_num1,random_num2;
	int ttid,count;
	char str[300];
	struct timeval t1, t2;
	FILE *fp;

	gettimeofday(&t1, NULL);
	ttid=gettid();
	count=0;
	srand(time(NULL));

	char filename[20];
	sprintf(filename, "file_%d.txt\n", ttid);
	while(1)
	{
		gettimeofday(&t2, NULL);

		int timediff=t2.tv_sec-t1.tv_sec;
		if (timediff>=15)break;
		random_num1= (rand()%3)+1;
		random_num2= (rand()%10);
		sleep(random_num2);
		sprintf(str, "Wake up all processes in wait queue project2_queue_%d at time ...\n", 1);

		fp = fopen(filename, "w");
		fprintf(fp, str);
		fclose(fp);

		syscall(360, random_num1);   
		printf("Done Q%d\n", random_num1);                     
	}

	syscall(360, 1);
	str[100]="Clean wait wait queue project2_queue_1"; 
	fp = fopen(filename, "w");
	fprintf(fp, str);
	fclose(fp);

	syscall(360, 2);
	str[100]="Clean wait wait queue project2_queue_2"; 
	fp = fopen(filename, "w");
	fprintf(fp, str);
	fclose(fp);

	syscall(360, 3);
	str[100]="Clean wait wait queue project2_queue_3"; 
	fp = fopen(filename, "w");
	fprintf(fp, str);
	fclose(fp);

	printf("process %d completes!\n", ttid);
}

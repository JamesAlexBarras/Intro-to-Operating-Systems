/*
 * COMP 3500: Project 5 Scheduling
 * Alex Barras (jab0217)
 *
 * All code for this project was done with no help from outside sources, other than Dr. Qin's starter code that was provided. 
 *
 * Version 1.0  11/18/2019
 *
 * This source code shows how to conduct separate compilation.
 *
 * How to compile using Makefile?
 * $make
 *
 * How to manually compile?
 * $gcc -c open.c
 * $gcc -c read.c
 * $gcc -c print.c
 * $gcc open.o read.o print.o scheduler.c -o scheduler
 *
 * How to run?
 * Case 1: no argument. Sample usage is printed
 * $./scheduler
 * Usage: scheduler <file_name>
 *
 * Case 2: file doesn't exist.
 * $./scheduler file1
 * File "file1" doesn't exist. Please try again...
 *
 * Case 3: Input file
 * $./scheduler task.list
 * data in task.list is printed below...
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scheduler.h"
#include "print.h"
#include "open.h"
#include "read.h"

int main( int argc, char *argv[] )  {
    char *file_name; /* file name from the commandline */
    FILE *fp; /* file descriptor */
    task_t task_array[MAX_TASK_NUM];

    
    u_int clock = 0;
    int error_code;
    u_int i;
    u_int count;
    u_int downTime = 0;

    if (argc < 2) {
        printf("\nUsage: input <file_name>\n");
        return EXIT_FAILURE;
    }

    error_code = open_file(argv[1], &fp);
    if (error_code == 1)
        return EXIT_FAILURE;

    read_file(fp, task_array, &count);
    print_task_list(task_array, count);


    if (argc == 1 || argc > 4) {
        printf("Usage: command file_name [FCFS|RR|SRFT] [time_quantum]\n");
        return 0;
    }

    /* Print file name */
    printf("The file name is %s\n", argv[1]);

    /* Print policy */
    printf("The chosen policy is %s\n", argv[2]);

    /* Handle the RR policy */
    if (strcmp(argv[2], "RR") == 0) {
        if (argc == 4)
            printf("time_quantum is set to %s\n", argv[3]);
        else printf("Please enter time_quantum for the RR policy!\n");
    }

    /* read data from input file 
    count = 0;
    while (fscanf(fp, "%u %u %u", &task_array[count].pid, &task_array[count].arrival_time, \
                  &task_array[count].burst_time)!= EOF) {
        count++;
    }*/

    printf("There are %u tasks loaded from %s ...\n", count, argv[1]);

    printf("Press any key to continue ...\n");
    getchar();

    printf("===============================\n");

/*
    int v = 0;
    while (v < count) 
   {
	task_array[v].done = 0;
	printf("Task %u done value set to %u\n", task_array[v].pid, task_array[v].done);
	v++;
   }
*/

    //policies
    // First Come First Serve
    if (strcmp("FCFS", argv[2]) == 0) 
    {
	//int timeLeft = 0;
	int j = 0;
	int gate = 0;	


	//printf("count is %u", count);
	while (j < count) 
	{		
		if (task_array[j].arrival_time <= clock)
		{
			if (task_array[j].remaining_time == 0)
			{
				printf("<Time %u> Process %u is finished...\n", clock, task_array[j].pid);
				task_array[j].finish_time = clock;
				j++;
				gate = 0;
				continue;
			} else 
			{ 	
				printf("<Time %u> Process %u is running\n", clock, task_array[j].pid);
				if (gate == 0) 
				{
					task_array[j].remaining_time = task_array[j].burst_time;
					task_array[j].start_time = clock;
					gate = 1;
				}

				task_array[j].remaining_time--;
				clock++;
			}
	
		} else 
		{
			clock++;
			downTime++;
		}



		
	}    


    } else if (strcmp("RR", argv[2]) == 0)
    {

    } else if (strcmp("SRTF", argv[2]) == 0)
    {

    }



    printf("===============================\n");

    //stat calculations
    float waitTime = 0;
    float responseTime = 0;
    float turnAroundTime = 0;
    float cpuUsage = 100;
    
    int k = 0;
    while (k < count)
    {
	waitTime += (float)(task_array[k].finish_time - task_array[k].burst_time);
        responseTime += (float)task_array[k].start_time;
	turnAroundTime += (float)task_array[k].finish_time;        
        k++;
    }
    waitTime /= count;
    responseTime /= count;
    turnAroundTime /= count; 
   // cpuUsage -= (float)downTime;

    printf("Average Waiting Time:     %f\n", waitTime);
    printf("Average Response Time:    %f\n", responseTime);
    printf("Average turnaround Time:  %f\n", turnAroundTime);
    printf("Overall CPU usage:        %f%\n", cpuUsage);

   


    printf("===============================\n");

    fclose(fp);
    return EXIT_SUCCESS;
}






#include <stdio.h>
#include <lab1.h>
#include <q.h>
#include <kernel.h>
#include <proc.h>

/* Scheduler identifier */
int current_sched_class = 0;

/* Used for storing current epoch duration */
int current_epoch_time;

/* Similar to proctab to store counter and goodness for each value */
struct linuxschedent schedtab[NPROC];

void setschedclass(int sched_class)
{
	if(sched_class == EXPDISTSCHED)
	{
		current_sched_class = EXPDISTSCHED;
	}
	else if(sched_class == LINUXSCHED)
	{
		current_sched_class = LINUXSCHED;
		
		/* Starting Epoch */
		current_epoch_time = 0;

		int i;
		/* Initializing the counter and goodness values for all processes */
		for(i=0; i < NPROC; i++)
		{
			/* Setting counter to priority of the process. Storing it in separate data structure
			so that changes in priority are effective only in next epoch */
			schedtab[i].pprio = proctab[i].pprio;
			
			/* For new processes, it did not execute in previous epoch, hence there are no previous counter values to consider */
			schedtab[i].counter = schedtab[i].pprio;
			
			/* Initially counter will be 0 because its the first epoch. */
			schedtab[i].goodness =  schedtab[i].pprio;
			

			/* Calculating epoch duration with respect to every existing process */
			if(proctab[i].pstate != PRFREE)
			{
				current_epoch_time += schedtab[i].counter;
				schedtab[i].epoch_flag = 1; /* Process can run in current epoch */
			}
			else
			{
				schedtab[i].epoch_flag = 0; /* Setting flag for non-existent processes */
			}
		}
	
	}
	else
	{
		kprintf("\n Using normal scheduler............\n");
	}
}


int getschedclass()
{
	return current_sched_class;
}

/* Retrieve the next process in ready queue according to random value - For Exponential Scheduler */
int getNextProcess(int random)
{

	int next;
	int prev;
	
	next = q[rdyhead].qnext;

	while (q[next].qkey < random)
	{
		next = q[next].qnext;
	}	
	
	if(next == rdytail)
	{
		return q[rdytail].qprev;
	}

	return next;
}

/* Retrieve the next process to execute from the ready queue based on goodness value in current epoch - Used by Linux-like scheduler */
int getNextProcessLinux()
{
	/* Start of the ready queue */
	int next = q[rdyhead].qnext;

	/* Initial max_goodness value */
	int max_goodness = schedtab[next].goodness;

	/* Initial process ID (NULLPROC). This will be returned if queue is empty */
	int nextpid = next;
	
	/* Find the first runnable process ID with remaining quantum (in the current epoch)  with highest goodness value in the ready queue. */ 
	while(next != rdytail)
	{	
		if(schedtab[next].epoch_flag == 1 && schedtab[next].counter > 0 && schedtab[next].goodness > max_goodness)
		{
			max_goodness = schedtab[next].goodness;
			nextpid = next;
		} 
		
		next = q[next].qnext;
	}
	/* Return the pid of the selected process */
	return nextpid;
}


/* Check if there is any runnable process in current epoch */
/* To check for any runnable process in current epoch, check if there is any process with positive non-zero goodness value */
int runnableExists()
{
	int total_goodness = 0;
	int pid;

	/* Start of the ready queue */
	int next = q[rdyhead].qnext;
	
	while(next != rdytail)
	{
		if(schedtab[next].epoch_flag)
		{
			total_goodness = total_goodness + schedtab[next].goodness;
		}
		next = q[next].qnext;
	}
	
	
	/* Return true or false */
	if(total_goodness > 0)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

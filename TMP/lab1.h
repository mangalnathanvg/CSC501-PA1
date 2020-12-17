#ifndef _LAB1_H_
#define _LAB1_H_

#define EXPDISTSCHED 1
#define LINUXSCHED 2

void setschedclass(int sched_class);
int getschedclass();
int getNextProcess(int random);
int runnableExists();
int getNextProcessLinux();

extern int current_epoch_time;

/* Custom data structure to monitor the epoch, goodness and counter values. */
struct linuxschedent
{
	int pprio;       /* Storing priority separately so changes can be reflected only in the next epoch. */
	int goodness;	 /* Goodness value metric as described in PA1 */
	int counter;	 /* To store value of the remaining ticks for the process */
	int epoch_flag;  /* Indicator to show if process can execute in current epoch or not. */
};

extern struct linuxschedent schedtab[];

#endif

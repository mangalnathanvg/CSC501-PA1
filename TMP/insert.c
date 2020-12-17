/* insert.c  -  insert */

#include <conf.h>
#include <kernel.h>
#include <q.h>
#include <lab1.h>
/*------------------------------------------------------------------------
 * insert.c  --  insert an process into a q list in key order
 *------------------------------------------------------------------------
 */
int insert(int proc, int head, int key)
{
	int	next;			/* runs through list		*/
	int	prev;

	int current_scheduler = getschedclass();	

	/* Custom insert for the two schedulers to implement Round Robin for processes with same priority/goodness value */
	if(current_scheduler == EXPDISTSCHED || current_scheduler == LINUXSCHED)
	{
	        next = q[head].qnext;
        	while (q[next].qkey <= key)      /* tail has maxint as key       */
                	next = q[next].qnext;
        	q[proc].qnext = next;
        	q[proc].qprev = prev = q[next].qprev;
        	q[proc].qkey  = key;
        	q[prev].qnext = proc;
	        q[next].qprev = proc;

	
	}
	else
	{
		next = q[head].qnext;
		while (q[next].qkey < key)	/* tail has maxint as key	*/
			next = q[next].qnext;
		q[proc].qnext = next;
		q[proc].qprev = prev = q[next].qprev;
		q[proc].qkey  = key;
		q[prev].qnext = proc;
		q[next].qprev = proc;
	}
	return(OK);
}

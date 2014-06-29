#include <stdio.h>
#include <stdlib.h>

#include "lqueue.h"

void printInt(int x)
{
	printf("%d, ", x);
}

#define queueStats(q) 	\
	do {	\
	printf("Queue Size: %zd\nQueue Empty: %d\n", lqueue_size(q), lqueue_empty(q));	\
	if(lqueue_size(q) > 0)	{	\
		printf("First Element: %d\n", lqueue_peek(q));	\
		printf("Queue Contents:\n");	\
		lqueue_foreach(printInt, q);	\
	}	\
	else {	\
		printf("Queue Contents:\n<Empty>");	\
	}	\
	} while(0)

#define section(headerStr, code)	\
printf("\n##############################################################\n");\
printf("--------------------------------------------------------------\n");\
printf(headerStr);			\
printf("\n--------------------------------------------------------------\n");\
code					\
printf("\n##############################################################\n")

LQUEUE_CREATE_DATATYPE(int_queue, int);

int
main(int argc, char **argv)
{
	int i;
	//struct int_queue q;
	lqueue_t(int) q;
	lqueue_init(q);

	section("Appending 1 Item to the Queue", 
		lqueue_append(101, q);
		queueStats(q);
	);

	section("Removing 1 Item from the Queue", 
		printf("Item removed: %d\n", lqueue_remove(q));
		queueStats(q);
	);

	section("Appending 1 Item to the Queue", 
		lqueue_append(33, q);
		queueStats(q);
	);

	section("Appending 100 Items to the Queue", 
		for(i = 0; i < 100; i++)
		{
			lqueue_append(i, q);
		}
		queueStats(q);
	);

	section("Removing 50 Items from the Queue", 
		printf("Items removed\n");
		for(i = 0; i < 50; i++)
		{
			printf("%d, ", lqueue_remove(q));
		}
		printf("\n");
		queueStats(q);
	);

	section("Appending 100 Items to the Queue", 
		for(i = 100; i < 200; i++)
		{
			lqueue_append(i, q);
		}
		queueStats(q);
	);

	section("Deleting the queue", 
		lqueue_del(q);
	);
	return 0;
}


#include <stdio.h>
#include <stdlib.h>

typedef struct dataNode
{
	int data;
	struct dataNode *next;
}node;

typedef struct linkqueue
{
	node *front, *rear;
}queue;

queue *insert(queue *hq, int x)
{
	node *s;
	s = (node *)malloc(sizeof(node));
	s->data = x;
	s->next = NULL;

	if(hq->rear == NULL){            //empty queue
		hq->front = s;
		hq->rear = s;
	}
	else{
		hq->rear->next = s;
		hq->rear = s;
	}

	return hq;
}

queue *del(queue *hq)
{
	node *p;

	if(hq->front == NULL){
		printf("empty queue,cannot del\n");
	}
	else {		
		p = hq->front;

		if(hq->front == hq->rear){
			hq->front = NULL;
			hq->rear = NULL;
		}
		else{
			hq->front = hq->front->next;
		}
	}

	free(p);

	return hq;
}

void printQueue(queue *hq)
{
        node *p;
        p = hq->front;

	printf("---------------------------------\n");
        while(p){
                printf("%d\n", p->data);
                p = p->next;
        }
        
        return;                                                                                                                                
}

int main()
{
	queue *mainQueue;
	mainQueue = (queue *)malloc(sizeof(queue));

	mainQueue->front = NULL;
	mainQueue->rear = NULL;

	mainQueue = insert(mainQueue, 1);
	mainQueue = insert(mainQueue, 2);
	mainQueue = insert(mainQueue, 3);

	printQueue(mainQueue);

	mainQueue = del(mainQueue);
	printQueue(mainQueue);

	mainQueue = del(mainQueue);
	printQueue(mainQueue);

	mainQueue = del(mainQueue);
	printQueue(mainQueue);

	mainQueue = del(mainQueue);
	printQueue(mainQueue);

	return 0;	
}

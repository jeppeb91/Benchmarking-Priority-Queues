#include <stdlib.h>
#include <unistd.h>

typedef struct{
	int size;
	long average;
	struct node *last;
	struct node *first;
}queue;

struct node{
	int prio;
	int val;
	struct node *next;
	struct node *prev;
};

int main(){
	struct node n_0;
	struct node n_1;
	struct node n_2;	

	n_0.prio = 1;
	n_1.prio = 2;
	n_2.prio = 3;	
	
	n_0.next = &n_1;
	n_0.prev = NULL;

	n_1.next = &n_2;
	n_1.prev = &n_1;

	n_2.next = NULL;
	n_2.prev = &n_1;				
	queue q;
	
	q.first = &n_0;
	q.last= &n_2;
	
	int i = 0;	
	printf("%d\n", n_2.prio);
	return 0;
}

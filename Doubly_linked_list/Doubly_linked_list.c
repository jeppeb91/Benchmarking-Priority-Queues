#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
typedef struct queue{
	int size;
	float average;
	struct node* last;
	struct node* first;
}queue;

typedef struct node{
	int prio;
	int val;
	struct node* next;
	struct node* prev;
}node;
node* make_node(){
	node* n = (node*)malloc(sizeof(node));
	n-> prio = 0;
	n->val = 0;
	n->next = NULL;
	n->prev = NULL;
	return n;
}
queue* make_queue(){
	queue* q = (queue*)malloc(sizeof(queue));
	q->size = 0;
	q->average = 0;
	q->first = NULL;
	q->last = NULL;	
	return q;
}
void insert(queue* q, int priority, int value){
	node* e = make_node();
	e->prio = priority;
	e->val = value;	
	int old_size = q->size;	
	int new_size = old_size + 1;	
	float old_average = q->average;
	if(q->last == NULL){
		//If there are no nodes in queue				
		q->first = e;
		q->last = e;
	}else{				
		printf("%f\n", old_average);		
		if(priority>old_average){
			printf("%f\n", old_average);			
			//Seek from highest prio
			node* current = q->last;			
			while(current->prio >= priority){				
				printf("%d\n", current->prio);											
				current = current->prev;			
				if(current->prev == NULL){
					//If no node with lower					
					e->next = current;					
					e->prev = make_node();					
					q->first = e;				
					break;
				}					
			}
			if(current == q->last){					
				//if none after				
				current->next = e;				
				e->prev = q->last;
				q->last = e;						
			}else{
				//If its supposed to go between two
				e->next = current->next;				
				node* after_e = current->next;					
				after_e->prev = e;				
				current->next = e;				
				e->prev = current;											
			 }
		}	
	}	

	float new_average = (float)(old_size*old_average + priority)/new_size;
	q->average = new_average;
	q->size = new_size;	
}
void iterqueue(node* n){
	//This method iterates through and prints a queue from its last element to its first
	//For testing purposes only	
	printf("%d : %d\n", n->prio, n->val);
	if(n->prev == NULL){
		return;
	}	
	iterqueue(n->prev);
}
int main(){
	int ITERATIONS = 100;	
	queue* q = make_queue();		
	for(int i = 1; i < ITERATIONS; i++){
		insert(q, i, i);
	}	
	insert(q, 51, 1337);	
	node* o = q->last;	
	iterqueue(o);		
	return 0;
}

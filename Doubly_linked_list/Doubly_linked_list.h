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
	float prio;
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

void insert_node(queue* q, node* e){
	int priority = e->prio;	
	int old_size = q->size;	
	int new_size = old_size + 1;	
	float old_average = q->average;
	if(q == NULL || e == NULL){
		return;
	}
	if(q->last == NULL){
		//If there are no nodes in queue				
		q->first = e;
		q->last = e;
	}else{				
		if(priority >= old_average){			
			//Seek from highest prio			
			node* current = q->last;			
			while(current->prio > priority){				
				current = current->prev;			
				if(current->prev == NULL){
					//If no node with lower					
					e->next = current;					
					e->prev = NULL;					
					q->first = e;				
					break;
				}					
			}
			if(current == q->last){					
				//if no node with higher				
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
		}else{		
			node* current = q->first;			
			while(current->prio < priority){				
				current = current->next;			
			}			
			if(current == q->first){					
				//if none before				
				current->prev = e;					
				e->prev = NULL;
				e->next = current;				
				q->first = e;						
			}else{
				//If its supposed to go between two
				e->next = current->next;				
				node* after_e = current->next;					
				after_e->prev = e;				
				current->next = e;				
				e->prev = current; current;											
			 }
		}	
	}	
	//General status updates which are common regardless of input
	float new_average = (float)(old_size * old_average + priority)/new_size;
	q->average = new_average;
	q->size = new_size;	
}
void insert_kv(queue* q, int priority, int value){
	//Inserts a new node with given priority and value in q	
	node* e =  make_node();
	e->prio = priority;
	e->val = value;		
	insert_node(q, e);
}
int pop(queue* q){	
	//Pops the lowest priority from the queue
	//For to equal priorities FIFO	
	if(q == NULL){
		return -1337;
	}	
	if(q->size < 1){
		return -1337;
	}	
	if(q->size == 1){		
		int value = q->first->val;				
		float priority =q->first->prio;			
		free(q->first);		
		q->last = NULL;
		q->first = NULL;	
		q->size = 0;			
		
		//update stats
		q->size = 0;
		q->average = 0;	
		return value;	
	}
	node* new_first = q->first->next;	
	int value = q->first->val;
	float priority =q->first->prio;		
	new_first->prev = NULL;
	free(q->first);	
	q->first = new_first;		
	
	//update stats
	int size = q->size;
	float old_average = q->average;		
	float new_average = (float)(old_average * size - priority)/(size -1);
	
	q->size = size - 1;
	q->average = new_average;
	return value;
}



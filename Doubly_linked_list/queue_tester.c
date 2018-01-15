#include "Doubly_linked_list.h"
int test_down(node* n, int min){
	//This method iterates through and prints a queue from its last element to its first
	//For testing purposes only	
	//printf("%d : %d\n", n->prio, n->val);
	if(n->prev != NULL){
		test_down(n->prev, min);
	}else{
		if(n->prio == min){
			return 1;
		}
		else{
			return 0;
		}
	}
}	
int test_up(node* n, int max){
	//This method iterates through and prints a queue from its last element to its first
	//For testing purposes only	
	printf("%d : %d\n", n->prio, n->val);
	if(n->next != NULL){
		test_up(n->next, max);
	}else{
		if(n->prio == max){
			return 1;
		}
		else{
			return 0;
		}
	}
}	

int test_updown(queue* q){
	int size = q->size;	
	test_up(q->first, 1);
	int vals [size];
	for(int i = 0; i < size; i++){
		vals[i] = pop(q);
		printf("Popped: %d, %d\n", vals[i], q->size);	
	}
	for(int i = 0; i < size; i++){
		insert_kv(q, i, vals[i]);	
	}
	return test_down(q->last, q->first->prio);
}

int main(){
	int ITERATIONS = 100000;	
	queue* q = make_queue();		
	for(int i = 1; i < ITERATIONS; i++){
		insert_kv(q, i, i);
	}								
	printf("Down: %d\n", test_down(q->last, 1));	
	printf("Up: %d\n", test_up(q->first, 99));		
	//printf("Average: %d\n", test_average(q));
	//printf("Inserts: %d\n", test_inserts(q));	
	printf("Up/Down: %d\n", test_updown(q));	
	return 0;
}

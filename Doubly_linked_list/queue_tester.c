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
	//printf("%d : %d\n", n->prio, n->val);
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
int test_average(queue* q){
	float before = (float)q->average;
	node* n = pop(q);
	insert_node(q, n);
	if(before == q->average){
		return 1;
	}
	return 0;
}
int test_updown(queue* q){
	int size = q->size;	
	test_up(q->first, 1);
	node* nodes [size];
	for(int i = 0; i < size - 1; i++){
		nodes[i] = pop(q);
		printf("%d\n", q->size);			
	}
	for(int i = 0; i < size; i++){
		insert_kv(q, i, i);	
	}
	free(nodes);
	return test_down(q->last, q->first->prio);
}
int test_inserts(queue* q){
	int mean = (int) q->average;
	insert_kv(q, q->first->prio - 1, 123);	
	insert_kv(q, mean, 1234);
	insert_kv(q, q->last->prio + 1, 2345);	
	if(test_down(q->last, q->first->prio)){
		if(test_up(q->first, q->last->prio)){
			node* current = pop(q); 			
			while(current->prio<mean){
				current = pop(q);		
			}
			if(pop(q)->prio == mean){				
				return 1;
			}				
		}
	}
	return 0;
}
int main(){
	int ITERATIONS = 100;	
	queue* q = make_queue();		
	for(int i = 1; i < ITERATIONS; i++){
		insert_kv(q, i, i);
	}								
	//printf("Down: %d\n", test_down(q->last, 1));	
	//printf("Up: %d\n", test_up(q->first, 99));		
	//printf("Average: %d\n", test_average(q));
	//printf("Inserts: %d\n", test_inserts(q));	
	printf("Up/Down: %d\n", test_updown(q));	
	return 0;
}

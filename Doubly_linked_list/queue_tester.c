#include "Doubly_linked_list.h"
int test_down(node* n, int min){
	//This method iterates through and prints a queue from its last element to its first
	printf("prio: %f Val: %d\n", n->prio, n->val);	
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
	//printf("prio: %d Val: %d\n", n->prio, n->val);		
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
		//printf("Popped: %d Size: %d\n", vals[i], q->size);	
	}
	for(int i = 0; i < size; i++){
		insert_kv(q, (float) i, i);	
		//printf("Inserted: %d Size: %d\n", vals[i], q->size);	
	}
	if (test_down(q->last, q->first->prio) || test_up(q->first, q->last->prio)){
		return 1;
	}
	return 0;
}

int test_middle(queue* q){
	float mean = q->average;	
	int size = q->size;	
	int before = 0;
	int current = 0;
	int after = 0;	
	insert_kv(q, mean, 13371337); 	
	test_down(q->last, q->first->prio);	
	for(int i = 0; i < size; i++){
		before = current;		
		current = pop(q);
		if(current == 13371337){
			after = pop(q);			
			current = mean;			
			break;
		}
	}	
	printf("Before: %d Middle(val): %d After: %d\n", before, current, after); 	
	if(before > current || current > after){
		return 0;
	}		
	return 1;	
}
int main(int argc, char **argv){
	int ITERATIONS = 100000;	
	queue* q = make_queue();		
	node** nodes = malloc(sizeof(node*)*ITERATIONS);	
	for(int i = 0; i < ITERATIONS; i++){
		nodes[i] = make_node();
		nodes[i]->prio = i;
		nodes[i]->val = i;
	}
	for(int i = 0; i < ITERATIONS; i++){
		insert_node(q, nodes[i]);
	}										
	printf("Up/Down: %d\n", test_updown(q));
	printf("Middle: %d\n", test_middle(q));		
	return 0;
}

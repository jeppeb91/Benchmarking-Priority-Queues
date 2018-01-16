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
	node* nodes [size];
	for(int i = 0; i < size; i++){
		nodes[i] = pop(q);
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
	node* before = NULL;
	node* current = NULL;
	node* after = NULL;	
	insert_kv(q, mean, 13371337); 	
	test_down(q->last, q->first->prio);	
	for(int i = 0; i < size; i++){
		before = current;		
		current = pop(q);
		if(current->val == 13371337){
			after = pop(q);			
			current->val = mean;			
			break;
		}
	}	
	printf("Before: %d Middle(val): %d After: %d\n", before->val, current->val, after->val); 	
	if(before->val > current->val || current->val > after->val){
		return 0;
	}		
	return 1;	
}
int main(int argc, char **argv){
	int ITERATIONS = 100;	
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
	free(nodes);	
	return 0;
}

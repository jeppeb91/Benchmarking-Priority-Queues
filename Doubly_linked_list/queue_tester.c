#include "Doubly_linked_list.h"
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
	for(int i = 3; i < ITERATIONS; i++){
		insert_kv(q, i, i);
	}			
	insert_kv(q, 101, 13381338);		
	insert_kv(q, 49, 1337);	
	insert_kv(q, 50, 1338);	
	node* o = q->last;	
	node* n = pop(q);
	insert_node(q, n);
	insert_kv(q, 1, 1);	
	insert_kv(q, 101, 1247);	
	printf("%p\n", n->next);	
	printf("%p\n", n->prev);	
	iterqueue(o);			
	return 0;
}

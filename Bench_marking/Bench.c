#include "Doubly_linked_list.h"
//#include "Skew_heap.h"
int main(int argc, char **argv){
	int ITERATIONS = strtoumax(argv[1], NULL, 10);
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
	for(int i = 0; i < ITERATIONS; i++){
		nodes[i] = pop(q);
		//printf("%f\n", nodes[i]->prio);
	}
	free(nodes);
	return 0;
}

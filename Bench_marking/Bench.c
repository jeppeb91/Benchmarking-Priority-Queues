//#include "Doubly_linked_list.h"
#include "Skew_heap.h"
int main(int argc, char **argv){
	int ITERATIONS = strtoumax(argv[1], NULL, 10);
	queue* q = make_queue();
	node** nodes = malloc(sizeof(node*)*ITERATIONS);
	srand(311);	
	for(int i = 0; i < ITERATIONS; i++){		
		nodes[i] = make_node();
		int number = rand();
		number = number % 100;
		nodes[i]->prio = (float) number;
		nodes[i]->val = i;
	}
	for(int i = 0; i < ITERATIONS; i++){
		insert_node(q, nodes[i]);
	}
	//tree_climber(q->root);
	for(int i = 0; i < ITERATIONS; i++){
		nodes[i] = pop(q);
		printf("%f\n", nodes[i]->prio);
	}
	free(nodes);
	return 0;
}

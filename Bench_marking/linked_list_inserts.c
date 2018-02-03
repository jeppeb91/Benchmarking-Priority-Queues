#include "lib/Doubly_linked_list.h"
//#include "lib/Skew_heap.h"
#include <time.h>
#include <sys/time.h>
#include "lib/priority_reader.h"

void iteration(float* rands, int iteration_no, unsigned long* rounds){
	queue* q = make_queue();	
	struct timeval start;
	struct timeval stops [975];
	int ITERATIONS = 2000; //10000
	node** nodes = malloc(sizeof(node*)*ITERATIONS);	
	for(int i = 0; i < ITERATIONS; i++){		
		nodes[i] = make_node();
		nodes[i]->prio = rands[i + 2000 * iteration_no];
		nodes[i]->val = i;
	}
	//Iterate Up and down first for stability		
	for(int i = 0; i < 1000; i++){
		insert_node(q, nodes[i]);
	}
	for(int i = 0; i < 1000; i++){
		nodes[i] = pop(q); 
	}
	for(int i = 1000; i < 1025; i++){
		insert_node(q, nodes[i]);
	}
	gettimeofday(&start, NULL);	
	for(int i = 1025; i < 2000; i++){
		insert_node(q, nodes[i]);
		gettimeofday(&stops[i - 1025], NULL);
	}
	for(int i = 0; i < 975; i++){
		rounds[i + 975 * iteration_no] = stops[i].tv_usec - start.tv_usec; 	
	}
	free(q);	
	free(nodes);	
}
int main(int argc, char **argv){
	unsigned long* rounds = malloc(sizeof(unsigned long)*4875);
	float* rands = read_priorities(argv[1]);	

	iteration(rands, 0, rounds);
	iteration(rands, 1, rounds);
	iteration(rands, 2, rounds);
	iteration(rands, 3, rounds);
	iteration(rands, 4, rounds);	
	for(int i = 3900; i < 4875; i++){
		printf("%d\t%lu\n", i + 25 - 3900, rounds[i]); 	
	}
	return 0;
}



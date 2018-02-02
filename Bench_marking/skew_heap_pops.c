//#include "lib/Doubly_linked_list.h"
#include "lib/Skew_heap.h"
#include <time.h>
#include <sys/time.h>
#include "lib/priority_reader.h"
int main(int argc, char **argv){
	struct timeval start;
	struct timeval stops [8975];	
	int ITERATIONS = 10000;	
	float* rands = read_priorities(argv[1]);	
	clock_t c_start, c_stop;	
	queue* q = make_queue();
	node** nodes = malloc(sizeof(node*)*ITERATIONS);
	int qsizes [8975];
	c_start = clock();	
	
	//Create all nodes and assign priorities and values	
	for(int i = 0; i < ITERATIONS; i++){		
		nodes[i] = make_node();
		nodes[i]->prio = rands[i];
		nodes[i]->val = i;
	}
	
	//Iterate Up and down first for stability	
	for(int i = 0; i < 1000; i++){
		insert_node(q, nodes[i]);
	}
	for(int i = 0; i < 1000; i++){
		nodes[i] = pop(q); 
	}
	for(int i = 1000; i < 10000; i++){
		insert_node(q, nodes[i]);
	}	
	//c_start = clock();
	gettimeofday(&start, NULL);	
	for(int i = 1025; i < 10000; i++){
		nodes[i] = pop(q);
		qsizes[i - 1025] = q->size;
		gettimeofday(&stops[i - 1025], NULL);
	}
	for(int i = 0; i < 8975; i++){
		printf("%d\t%lu\n", qsizes[i], stops[i].tv_usec - start.tv_usec); 	
	}

	free(nodes);
	c_stop = clock();
	printf("%lu\n", c_stop);		
	return 0;
}



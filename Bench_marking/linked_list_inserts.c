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
		nodes[i]->prio = rands[(i + 2000 * iteration_no) % 10000];
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
void print_avg(unsigned long* rounds, int repeats){
	unsigned long sum = 0;	
	for(int i = 0; i < 975; i++){
		sum = 0;
		for(int j = 0; j < repeats; j++){
			sum = sum + rounds[i + 975*j];		
		}		
		printf("%d\t%lu\n", i + 25, sum/repeats); 	
	}
}
void bench(int repeats, float* rands){
	unsigned long* rounds = malloc(sizeof(unsigned long)*975*repeats);
	for(int i = 0; i < repeats; i++){
		iteration(rands, i, rounds);		
	}
	print_avg(rounds, repeats);
}
int main(int argc, char **argv){
	unsigned long* rounds = malloc(sizeof(unsigned long)*975*10);
	float* rands = read_priorities(argv[1]);
	bench(100, rands);
	return 0;
}



//#include "lib/Doubly_linked_list.h"
#include "lib/Skew_heap.h"
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib/priority_reader.h"
char* parse_out_path(char* dist, char* filename)
{
	int counter = 0;	
	char * base_path = "./out/skew/";
	char *result = malloc(strlen(base_path)+strlen(&dist[6])+strlen(filename)+1);
	//in real code you would check for errors in malloc here
	strcpy(result, base_path);
	strcat(result, &dist[6]);
	strcat(&result[strlen(&dist[6]) + strlen(base_path)], filename);
	return result;
}
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
void print_avg(unsigned long* rounds, int repeats, FILE* fp){
	unsigned long sum = 0;	
	for(int i = 0; i < 975; i++){
		sum = 0;
		for(int j = 0; j < repeats; j++){
			sum = sum + rounds[i + 975*j];		
		}		
		fprintf(fp, "%d\t%lu\n", i + 25, sum/repeats); 	
	}
}
void print_worst(unsigned long* rounds, int repeats, FILE* fp){
	unsigned long worst = 0;	
	for(int i = 0; i < 975; i++){
		worst = rounds[i];
		for(int j = 0; j < repeats; j++){			
			if(rounds[i + 975 * j] > worst){
				worst = rounds[i + 975 * j];
			}		
		}		
		fprintf(fp, "%d\t%lu\n", i + 25, worst); 	
	}
}
void bench(int repeats, float* rands, char* dist){
	unsigned long* rounds = malloc(sizeof(unsigned long)*975*repeats);
	for(int i = 0; i < repeats; i++){
		iteration(rands, i, rounds);
	}
	char * path = parse_out_path(dist, "_inserts_worst.dat");
	FILE* fp = fopen(path, "w");
	print_worst(rounds, repeats, fp);
	fclose(fp);
	
	path = parse_out_path(dist, "_inserts_avg.dat");
	fp = fopen(path, "w");
	print_avg(rounds, repeats, fp);
	fclose(fp);
}
int main(int argc, char **argv){
	unsigned long* rounds = malloc(sizeof(unsigned long)*975*10);
	float* rands = read_priorities(argv[1]);
	bench(5, rands, argv[1]);
	return 0;
}



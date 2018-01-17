#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct queue{
	struct node* root;
	int size;
}queue;

typedef struct node{
	float prio;
	int val;
	struct node* left;
	struct node* right;
}node;
node* make_node(){
	node* n = (node*)malloc(sizeof(node));
	n-> prio = 0;
	n->val = 0;
	n->left = NULL;
	n->right = NULL;
	return n;
}
queue* make_queue(){
	queue* q = (queue*)malloc(sizeof(queue));
	q->size = 0;	
	q->root = NULL;
	return q;
}

void meld(node* p, node* q){
	//ger just nu falska minsta	
	node* subroot = NULL;	
	node* temp = NULL;			
	if(p->prio <= q->prio){
		subroot = p;//pop(p)					
	}else{
		subroot = q;//pop(q)	
	}	
	//Meld	
	while(p != NULL && q != NULL){
		//printf("%f\n", p->prio); 		
		if(p->prio <= q->prio){
			temp = p->right;			
			p->right = q;
			p = temp;		
		}else{
			temp = q->right;
			q->right = p;
			q = temp;		
		}
	}
	while(subroot->right != NULL){
		if(subroot->left != NULL){			
			temp = subroot->left;			
			subroot->left = subroot->right;					
		}
		temp = subroot->right;		
		subroot->right = subroot->left;
		subroot = temp;	
		printf("%f\n", subroot->prio);	
	}
	//Meld	
	return;	
}
void insert_kv(queue* q, int priority, int value){
	//Inserts a new node with given priority and value in q		
	//insert_node(q, e);
	return;
}
int pop(queue* q){	
	//Pops the lowest priority from the queue
	//For to equal priorities FIFO	
	//return value;
	return 0;
}

int main(){
	queue* q = make_queue();
	node* n = make_node();	
	node* m = make_node();
	node* o = make_node();
	n->prio = 1;
	m->prio = 2;
	o->prio = 3;	
	n->right = m;
	meld(n, o);
	return 0;
}

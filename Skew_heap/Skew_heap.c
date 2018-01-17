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

node* meld2(node* p, node* q, node* root) {	
	node* temp = NULL;
//	if(p == NULL && q == NULL) return NULL;
	if(p == NULL) return root;
	if(q == NULL) return root;
	if(p->prio <= q->prio) {
		if(p->right == NULL) return root;		
		if(root == NULL){
			root = p;
		}		
		temp = p->right;
		p->right = q;
		printf("p<q\n");		
		printf("p: %f\n", p->prio);
		printf("temp: %f\n", temp->prio);
		printf("q: %f\n", q->prio);		
		meld2(temp, q, root);
	}else{
		if(q->right == NULL) return root;				
		if(root == NULL){
			root = q;
		}		
		temp = q->right;
		q->right = p;
		printf("p<q\n");		
		printf("p: %f\n", p->prio);
		printf("temp: %f\n", temp->prio);
		printf("q: %f\n", q->prio);		
		meld2(temp, p, root);
	}
	return root;
}

node* flip(node* p){
	node* root = p;	
	node* temp = NULL;
	while(1){
		printf("%f%f\n", p->prio, p->prio);					
		temp = p->left;
		p->left = p->right;
		p->right = temp;
		p = p->left;					
		if(p->right == NULL){
			printf("Broke %f%f\n", p->prio, p->prio);								
			break;
		}
	}
	return root;
}
node* meld(node* p, node* q){
	//ger just nu falska minsta
	node* subroot = NULL;	
	node* temp = NULL;			
	if(p->prio <= q->prio){
		subroot = p;
		p = p->right;					
	}else{
		subroot = q;	
		q = q->right;
	}	
	//Start from subroot
	temp = subroot;	
	while(p->right != NULL || q->right != NULL){
	//Iterate until none of the nodes has a right child node		
		printf("p: %f\n", p->prio);
		printf("q: %f\n", q->prio);					
		if(p->prio <= q->prio){
			temp->right = p;					
			p = p->right;		
		}else{
			temp->right = q;			
			q = q->right;		
		}
		temp = temp->right;			
	}
	//Add the last two nodes
	if(p->prio <= q->prio){
		temp->right = p;		
		temp = temp->right;
		temp->right = q;
	}else{
		temp->right = q;		
		temp = temp->right;
		temp->right = p;
	}
	return flip(subroot);	
}
void meldTest() {
	node* p1 = make_node();
	node* p2 = make_node();
	node* q1 = make_node();
	node* q2 = make_node();
	p1->prio = 1;
	p2->prio = 10;
	q1->prio = 5;
	q2->prio = 12;
	p1->right = p2;
	q1->right = q2;
	node* test = meld(p1, q1);
	while(test != NULL){
		printf("%f\n", test->prio);
		test = test->left;
	}

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
//	meld(n, o);
	meldTest();
	return 0;
}

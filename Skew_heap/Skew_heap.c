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
	node* test = meld2(p1, q1, NULL);
	while(test != NULL){
		printf("%f\n", test->prio);
		test = test->right;
	}

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
//	meld(n, o);
	meldTest();
	return 0;
}

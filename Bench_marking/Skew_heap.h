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

node* flip(node* p){
	node* root = p;	
	node* temp = NULL;
	while(1){
		temp = p->left;
		p->left = p->right;
		p->right = temp;
		p = p->left;					
		if(p->right == NULL){
			break;
		}
	}
	return root;
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
	return flip(root);
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
	if(p == NULL && q){
		subroot->right = q;		
		return flip(subroot);
	}
	if(q == NULL){
		subroot->right = p;		
		return flip(subroot);
	}
	//Start from subroot		
	temp = subroot;		
	while(p->right != NULL && q->right != NULL){							
	//Iterate until none of the nodes has a right child node				
		if(p->prio <= q->prio){						
			temp->right = p;					
			p = p->right;		
		}else{
			temp->right = q;			
			q = q->right;		
		}
		temp = temp->right;	
	}
	while(p->right != NULL && p->prio <= q->prio){		
		temp->right = p;
		temp = temp->right;
		p = p->right;		
	}
	while(q->right != NULL && q->prio < p->prio){		
		temp->right = q;
		temp = temp->right;
		q = q->right;		
	}
	//Add the last nodes
	
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

void insert_node(queue* q, node* e){	
	q->size ++;		
	if(q->root == NULL && e != NULL){
		q->root = e;
		return;
	}	
	q->root = meld(q->root, e);	
}
void insert_kv(queue* q, float priority, int value){
	//Inserts a new node with given priority and value in q		
	node* e = make_node();
	e->prio = priority;
	e->val = value;
	insert_node(q, e);
}
node* pop(queue* q){	
	//Pops the lowest priority from the queue
	if(q->root == NULL){
		return NULL;	
	}
	q->size --;	
	node* e = q->root;	
	if(e->left == NULL && e->right == NULL){
		q->root = NULL;
		return e;
	}
	if(e->left == NULL && e->right){
		q->root = e->right;
		return e;		
	}
	if(e->right == NULL && e->left){
		q->root = e->left;
		return e; 		
	}
	q->root = meld(e->left, e->right);	
	e->left = NULL;
	e->right = NULL;	
	return e;
}
void tree_climber(node* root){
//This methods goes from parent node to its left and right child
//Prints the priority of each visited node
	node* previous = NULL;	
	while(1){	
		printf("%f\n", root->prio);		
		char c = getchar();
		if(c == 'l'){
			previous = root;			
			root = root->left;
		}
		else if(c == 'r'){
			previous = root;			
			root = root->right;
		}
		else if(c == 'p'){
			root = previous;
		}		
	}	
}
void meldTest() {
	//Left test tree	
	node* p1 = make_node();
	node* p2 = make_node();
	node* p3 = make_node();
	node* p4 = make_node();
	node* p5 = make_node();
	node* p6 = make_node();
	node* p7 = make_node();
	
	p1->prio = 1;
	p2->prio = 50;
	p3->prio = 10;
	p4->prio = 13;
	p5->prio = 20;
	p6->prio = 16;
	p7->prio = 25;
	
	p1->left = p2;
	p1->right = p3;
	p3->left = p4;
	p3->right = p5;
	p4->right = p6;
	p5->left = p7;
	
	//Right test tree
	node* q1 = make_node();
	node* q2 = make_node();
	node* q3 = make_node();
	node* q4 = make_node();
	node* q5 = make_node();
	node* q6 = make_node();

	q1->prio = 5;
	q2->prio = 19;
	q3->prio = 40;
	q4->prio = 12;
	q5->prio = 30;
	q6->prio = 14;
	
	q1->left = q2;
	q1->right = q4;
	q2->left = q3;
	q4->left = q5;
	q4->right = q6;

	node* test = meld(p1, q1);
	//node* test = meld2(p1, q1, NULL);
	//tree_climber(test);
	queue* q = make_queue();
	q->root = test;
	printf("%f\n", pop(q)->prio);
	printf("%f\n", pop(q)->prio);
	printf("%f\n", pop(q)->prio);
	printf("%f\n", pop(q)->prio);
	printf("%f\n", pop(q)->prio);
	printf("%f\n", pop(q)->prio);
	printf("%f\n", pop(q)->prio);
	printf("%f\n", pop(q)->prio);
	printf("%f\n", pop(q)->prio);
	printf("%f\n", pop(q)->prio);
	printf("%f\n", pop(q)->prio);
	printf("%f\n", pop(q)->prio);
	tree_climber(q->root);
}


//This program implements the create/delete/insert/sort/reverse of a single-linked list.

#include <stdio.h>
#include <stdlib.h>
			
typedef struct link_node
{
	int data;
	struct link_node *next;
}Node;

Node * create_list(int len) //crerte a list with the given length
{
	Node *head, *p, *s;
	int x;
	int cycle = 1;
	head = (Node *)malloc(sizeof(Node));
	p = head;
	while(len--){
		printf("please input a data\n");
		scanf("%d", &x);
		s = (Node *)malloc(sizeof(Node));
		s->data = x;
		p->next = s;
		p = s;
	}
	head = head->next;
	p->next = NULL;
	return head;
}

int list_lenth(Node *head)  //calculate the length of the list
{
	int length = 0;
	Node *p;
	p = head;
	while(p){
		length ++;
		p = p->next;
	}
	return length;
}

int show_list(Node *head)  //print each data of the list
{
	Node *p;
	p = head;
	printf("list data:\n");
	while(p){
		printf("%d\n", p->data);
		p = p->next;
	}
	return 0;
}

Node *delete_node(Node *head, int num)
{
	Node *p1, *p2;
	p1 = head;

	while((p1->data != num)&&(p1->next != NULL)){
		p2 = p1;
		p1 = p1->next;
	}
	
	if(p1->data == num){
		if(p1 == head)	//the node is head
			head = p1->next;
		else	//the node is not head
			p2->next = p1->next;
		free(p1);
	}
	else
		printf("num %d cannot be found\n", num);

	return head;
}

Node *insert_node(Node *head, int num)
{
	Node *p0, *p1, *p2;

	p1 = head;
	p0 = (Node *)malloc(sizeof(Node));
	p0->data = num;
	while((p0->data >= p1->data)&&(p1->next != NULL)){
		p2 = p1;
		p1 = p1->next;
	}
	if(p0->data <= p1->data){	//insert at head
		if(p1 == head){
			head = p0;
			head->next = p1;
		}
		else{	//insert at middle
			p2->next = p0;
			p0->next = p1;
		}
	}
	else{	//insert at end
		p1->next = p0;
		p0->next = NULL;
	}
	
	return head;
}

Node *reverse_node(Node *head)
{
	Node *p1, *p2, *p3;

	if((head == NULL) || (head->next == NULL))
		return head;	
	
	p1 = head, p2 = head->next;
	while(p2){
		p3 = p2->next;
		p2->next = p1;
		p1 = p2;
		p2 = p3;
	}	

	head->next = NULL;
	head = p1;

	return head;
}

Node *sort_node(Node *head)	//use bubble sort to do the list sort
{
	Node *p;
	int len, temp;
	int i, j;
	
	if((head == NULL) || (head->next == NULL))
		return head;
	
	len = list_lenth(head);
	for(i = 0; i < len - 1; i++){
		p = head;
		for(j = 0; j < len - i - 1; j++){
			if(p->data > p->next->data){
				temp = p->data;
				p->data = p->next->data;
				p->next->data = temp;
			}
			p = p->next;
		}
	}

	return head;
}

int main()
{
	int ret, len;

	Node *single_linked_list;
	single_linked_list = create_list(3);
	ret = show_list(single_linked_list);

	//len = list_lenth(single_linked_list);
	//printf("the length of the list is %d\n", len);

	//single_linked_list = delete_node(single_linked_list, 3);
	//single_linked_list = insert_node(single_linked_list, 4);
	//single_linked_list = sort_node(single_linked_list);
	single_linked_list = reverse_node(single_linked_list);
	ret = show_list(single_linked_list);

	return 0;
}

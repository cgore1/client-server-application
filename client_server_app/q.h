#include "TCB.h"

void printQ()
{

}

void rotateQ(struct TCB_t **ptr_to_head)
{
	struct TCB_t *head = *ptr_to_head;
	if(head == NULL) // Queue empty
	{
		return;
	}

	*ptr_to_head = head -> next;
}

struct TCB_t* popQ(struct TCB_t **ptr_to_head)
{
	struct TCB_t *head = *ptr_to_head;
	if(head == NULL) // Queue empty
	{
		return NULL;
	}
	else
	{
		struct TCB_t *last_node = head -> previous;
		
		if(last_node == head) // Only one element in the queue
		{
			*ptr_to_head = NULL;
			return last_node;
		}
		else
		{
			last_node -> next = head -> next;
			head -> next -> previous = last_node;
			
			*ptr_to_head = head -> next;
			return head;
		}
	}
}

addQ(struct TCB_t **ptr_to_head, struct TCB_t *item)
{
	struct TCB_t *head = *ptr_to_head;

	if(head == NULL) // Queue empty
	{
		head = item;
		head -> previous = head;
		head -> next = head;
		
		*ptr_to_head = head;
	}
	else
	{
		struct TCB_t *last_node = head -> previous;
		last_node -> next = item;
		
		item -> previous = last_node;
		item -> next = head;

		head -> previous = item;
	}
}

void initQ(struct TCB_t **ptr_to_head)
{	
}

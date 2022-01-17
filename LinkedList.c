#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node* next;
};

// Linked List Traversal
// This function prints contents of linked list starting from the given node.
void printList(struct Node* node) {
  while (node != NULL) {
    printf(" %d ", node->data);
    
    node = node->next;
  }

  printf("\n");
}

// add a node at the front
void push(struct Node** head_ref, int new_data)
{
  // 1. allocate node
  struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

  // 2. put in the data
  new_node->data  = new_data;

  // 3. make next of new node as head
  new_node->next = *head_ref;

  // 4. move the head to point to the new node 
  *head_ref = new_node;
}

// add a node after a given node
void insertAfter(struct Node* prev_node, int new_data) {
  // 1. check if the given prev_node is NULL
  if (prev_node == NULL) {
    printf("the given previous node cannot be NULL \n");

    return;
  }

  // 2. allocate new node
  struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

  // 3. put in the data
  new_node->data  = new_data;

  // 4. make next of new node as next of prev_node
  new_node->next = prev_node->next;

  // 5. move the next of prev_node as new_node
  prev_node->next = new_node;
}

// add a node at the end
void append(struct Node** head_ref, int new_data) {
  // 1. allocate node
  struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

  struct Node* last = *head_ref;  // used in step 5

  // 2. put in the data
  new_node->data  = new_data;

  // 3. This new node is going to be the last node, so make next of it as NULL.
  new_node->next = NULL;

  // 4. If the Linked List is empty, then make the new node as head.
  if (*head_ref == NULL) {
    *head_ref = new_node;

    return;
  }

  // 5. Else traverse till the last node
  while (last->next != NULL) {
    last = last->next;
  }

  // 6. Change the next of last node
  last->next = new_node;
}

void deleteNode_byValue(struct Node** head_ref, int key) {
  // store head node
  struct Node *temp = *head_ref, *prev;

  // if head node itself holds the key to be deleted
  if (temp != NULL && temp->data == key) {
    *head_ref = temp->next; // changed head
    
    free(temp); // free old head
    
    return;
  }

  // Search for the key to be deleted, keep track of the
  // previous node as we need to change 'prev->next'.
  while (temp != NULL && temp->data != key) {
    prev = temp;
    temp = temp->next;
  }
}

// delete a Linked List node at a given position
void deleteNode_byIndex(struct Node** head_ref, int position) {
  // store head node
  struct Node* temp = *head_ref;

  // if linked list is empty
  if (*head_ref == NULL)
    return;
 
  // if head needs to be removed
  if (position == 0) {
    *head_ref = temp->next; // change head

    free(temp); // free old head
    
    return;
  }
 
  // find previous node of the node to be deleted
  for (int i = 0; temp != NULL && i < position - 1; i++)
    temp = temp->next;

  // if position is more than number of nodes
  if (temp == NULL || temp->next == NULL)
    return;

  // Node temp->next is the node to be deleted.
  // store pointer to the next of node to be deleted
  struct Node* next = temp->next->next;

  // unlink the node from linked list
  free(temp->next); // free memory

  temp->next = next; // unlink the deleted node from list
}

/* Function to delete the entire linked list */
void deleteList(struct Node** head_ref)
{
  /* deref head_ref to get the real head */
  struct Node* current = *head_ref;
  struct Node* next;
 
  while (current != NULL) {
    next = current->next;
    
    free(current);
    
    current = next;
  }
   
  // deref head_ref to affect the real head back in the caller.
  *head_ref = NULL;
}

int getCount(struct Node* head) {
  int count = 0;
  struct Node* current = head;

  while (current != NULL) {
    count++;
    current = current->next;
  }
  
  return count;
}

bool search(struct Node* head, int x) {
  struct Node* current = head;

  while (current != NULL) {
    if (current->data == x)
      return true;
    
    current = current->next;
  }

  return false;
}

int GetNth(struct Node* head, int index) {
  struct Node* current = head;
 
  int count = 0;
  
  while (current != NULL) {
    if (count == index)
      return (current->data);
    
    count++;
    current = current->next;
  }

  return 0;
}

int countTime(struct Node* head, int search_for) {
  struct Node* current = head;
  int count = 0;

  while (current != NULL) {
    if (current->data == search_for)
      count++;
    
    current = current->next;
  }
  
  return count;
}

void swapNodes(struct Node** head_ref, int x, int y) {
  // Nothing to do if x and y are same.
  if (x == y)
    return;
 
  // search for x (keep track of prevX and CurrX)
  struct Node *prevX = NULL, *currX = *head_ref;

  while (currX != NULL && currX->data != x) {
    prevX = currX;
    currX = currX->next;
  }
 
  // search for y (keep track of prevY and CurrY)
  struct Node *prevY = NULL, *currY = *head_ref;

  while (currY && currY->data != y) {
    prevY = currY;
    currY = currY->next;
  }
 
  // If either x or y is not present, nothing to do.
  if (currX == NULL || currY == NULL)
    return;

  // if x is not head of linked list
  if (prevX != NULL)
    prevX->next = currY;
  else // else make y as new head
    *head_ref = currY;

  // if y is not head of linked list
  if (prevY != NULL)
    prevY->next = currX;
  else // else make x as new head
    *head_ref = currX;
 
  // swap next pointers
  struct Node* temp = currY->next;
  
  currY->next = currX->next;
  currX->next = temp;
}

void moveToFront(struct Node **head_ref) {
  // If linked list is empty, or it contains only one node,
  // then nothing needs to be done, simply return.
  if (*head_ref == NULL || (*head_ref)->next == NULL)
    return;
 
  // initialize second last and last pointers
  struct Node *secLast = NULL;
  struct Node *last = *head_ref;
 
  //After this loop secLast contains address of second last
  // node and last contains address of last node in Linked List.
  while (last->next != NULL) {
    secLast = last;
    last = last->next;
  }
 
  // set the next of second last as NULL
  secLast->next = NULL;

  // set next of last as head node
  last->next = *head_ref;

  // change the head pointer to point to last node now
  *head_ref = last;
}

static void reverse(struct Node** head_ref) {
  struct Node* prev = NULL;
  struct Node* current = *head_ref;
  struct Node* next = NULL;

  while (current != NULL) {
    // Store next
    next = current->next;

    // Reverse current node's pointer
    current->next = prev;

    // Move pointers one position ahead.
    prev = current;
    current = next;
  }
  
  *head_ref = prev;
}

// linked list with 3 nodes
int main() {
	/* Start with the empty list */
  struct Node* head = NULL;

  // Insert 6.  So linked list becomes 6->NULL
  append(&head, 6);

  // Insert 7 at the beginning. So linked list becomes 7->6->NULL
  push(&head, 7);

  // Insert 1 at the beginning. So linked list becomes 1->7->6->NULL
  push(&head, 1);

  // Insert 4 at the end. So linked list becomes 1->7->6->4->NULL
  append(&head, 4);

  // Insert 8, after 7. So linked list becomes 1->7->8->6->4->NULL
  insertAfter(head->next, 8);

  push(&head, 3);

  printList(head);

  // deleteNode(&head, 4);
  deleteNode_byValue(&head, 3);
  deleteNode_byValue(&head, 6);
  deleteNode_byValue(&head, 4);

  printList(head);

  push(&head, 3);
  push(&head, 2);
  push(&head, 8);

  printList(head);

  deleteNode_byIndex(&head, 0);
  deleteNode_byIndex(&head, 2);

  printList(head);

  deleteList(&head);

  push(&head, 9);
  push(&head, 6);
  push(&head, 3);

  printList(head);

  printf("count of nodes is %d \n", getCount(head));

  search(head, 1) ? printf("Yes \n") : printf("No \n");
  search(head, 6) ? printf("Yes \n") : printf("No \n");

  printf("Element at index 1 is %d. \n", GetNth(head, 1));

  push(&head, 1);
  push(&head, 1);
  push(&head, 1);

  printList(head);

  printf("count of 1 is %d. \n", countTime(head, 1));

  push(&head, 4);

  printList(head);

  swapNodes(&head, 4, 3);

  printList(head);

  moveToFront(&head);

  printList(head);

  reverse(&head);

  printf("Reversed Linked list: \n");
  printList(head);

	return 0;
}
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// DLL Traversal
// This function prints contents of linked list starting from the given node.
void printList(struct Node* node)
{
  struct Node* last;

  printf("\nTraversal in forward direction \n");
  
  while (node != NULL) {
    printf(" %d ", node->data);

    last = node;
    node = node->next;
  }

  printf("\nTraversal in reverse direction \n");
  
  while (last != NULL) {
    printf(" %d ", last->data);
    
    last = last->prev;
  }
}

// add a node at the front
void push(struct Node** head_ref, int new_data) {
    // 1. allocate node
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

    // 2. put in the data
    new_node->data = new_data;

    // 3. make next of new node as head and previous as NULL
    new_node->next = *head_ref;
    new_node->prev = NULL;

    // 4. change prev of head node to new node
    if (*head_ref != NULL)
      (*head_ref)->prev = new_node;

    // 5. move the head to point to the new node
    *head_ref = new_node;
}

// add a node after a given node
void insertAfter(struct Node* prev_node, int new_data) {
  // 1. check if the given prev_node is NULL
  if (prev_node == NULL) {
    printf("The given previous node cannot be NULL.");
    
    return;
  }

  // 2. allocate new node
  struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

  // 3. put in the data
  new_node->data = new_data;

  // 4. make next of new node as next of prev_node
  new_node->next = prev_node->next;

  // 5. make the next of prev_node as new_node
  prev_node->next = new_node;

  // 6. make prev_node as previous of new_node
  new_node->prev = prev_node;

  // 7. change previous of new_node's next node
  if (new_node->next != NULL)
    new_node->next->prev = new_node;
}

// add a node at the end
void append(struct Node** head_ref, int new_data) {
  // 1. allocate node
  struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
  struct Node* last = *head_ref; // used in step 5

  // 2. put in the data
  new_node->data = new_data;

  // 3. This new node is going to be the last node, so make next of it as NULL.
  new_node->next = NULL;

  // 4. If the Linked List is empty, then make the new node as head.
  if (*head_ref == NULL) {
    new_node->prev = NULL;
    *head_ref = new_node;
    
    return;
  }

  // 5. Else traverse till the last node.
  while (last->next != NULL)
    last = last->next;

  // 6. change the next of last node
  last->next = new_node;

  // 7. make last node as previous of new node
  new_node->prev = last;

  return;
}

/* Driver program to test above functions*/
int main() {
  // Start with the empty list
  struct Node* head = NULL;

  // Insert 6.  So linked list becomes 6->NULL
  append(&head, 6);

  // Insert 7 at the beginning. So linked list becomes
  // 7->6->NULL
  push(&head, 7);

  // Insert 1 at the beginning. So linked list becomes
  // 1->7->6->NULL
  push(&head, 1);

  // Insert 4 at the end. So linked list becomes
  // 1->7->6->4->NULL
  append(&head, 4);

  // Insert 8, after 7. So linked list becomes
  // 1->7->8->6->4->NULL
  insertAfter(head->next, 8);

  printf("Created DLL is: ");
  printList(head);
  printf("\n");

  return 0;
}
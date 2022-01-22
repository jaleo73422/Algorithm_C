#include <stdio.h>
#include <stdlib.h>

void printCurrentLevel(struct node* root, int level);
int height(struct node* node);

// a linked list (LL) node to store a queue entry
struct QNode {
  struct node* data;
  struct QNode* next;
};

// The queue, front stores the front node of LL and rear stores the last node of LL.
struct Queue {
  struct QNode *front, *rear;
};

struct node {
  int key;
  struct node* left;
  struct node* right;
};

// a utility function to create a new linked list node.
struct QNode* newQueueNode(struct node* node) {
  struct QNode* temp = (struct QNode*) malloc(sizeof(struct QNode));
  temp->data = node;
  temp->next = NULL;

  return temp;
}

// a utility function to create an empty queue
struct Queue* createQueue() {
  struct Queue* q = (struct Queue*) malloc(sizeof(struct Queue));
  q->front = q->rear = NULL;
  
  return q;
}

// the function to add a key k to q
void enQueue(struct Queue* q, struct node* node) {
  // create a new LL node
  struct QNode* temp = newQueueNode(node);

  // If queue is empty, then new node is front and rear both.
  if (q->rear == NULL) {
    q->front = q->rear = temp;
    
    return;
  }

  // add the new node at the end of queue and change rear
  q->rear->next = temp;
  q->rear = temp;
}

// function to remove a key from given queue q
void deQueue(struct Queue* q) {
  // If queue is empty, return NULL.
  if (q->front == NULL)
    return;

  // store previous front and move front one node ahead
  struct QNode* temp = q->front;

  q->front = q->front->next;

  // If front becomes NULL, then change rear also as NULL.
  if (q->front == NULL)
    q->rear = NULL;

  free(temp);
}

struct node* newTreeNode(int data) {
  struct node* node = (struct node*) malloc(sizeof(struct node));
 
  // assign data to this node
  node->key = data;

  // initialize left and right children as NULL
  node->left = NULL;
  node->right = NULL;
  
  return node;
}

// postorder (Left, Right, Root)
// Given a binary tree, print its nodes according to the 
// "bottom-up" postorder traversal.
void printPostorder(struct node* node) {
  if (node == NULL)
    return;

  // first recur on left subtree
  printPostorder(node->left);

  // then recur on right subtree
  printPostorder(node->right);

  // now deal with the node
  printf("%d ", node->key);
}
 
// inorder (Left, Root, Right)
// Given a binary tree, print its nodes in inorder.
void printInorder(struct node* node) {
  if (node == NULL)
    return;

  // first recur on left child
  printInorder(node->left);

  // then print the data of node
  printf("%d ", node->key);

  // now recur on right child
  printInorder(node->right);
}

// preorder (Root, Left, Right)
// Given a binary tree, print its nodes in preorder.
void printPreorder(struct node* node) {
  if (node == NULL)
    return;

  // first print data of node
  printf("%d ", node->key);

  // then recur on left subtree
  printPreorder(node->left);

  // now recur on right subtree
  printPreorder(node->right);
}

void printLevelOrder(struct node* node) {
  int h = height(node);
  int i;

  for (i = 1; i <= h; i++) {
    printCurrentLevel(node, i);
  }
}

int height(struct node* node) {
  if (node == NULL)
    return 0;
  else {
    // compute the height of each subtree
    int lheight = height(node->left);
    int rheight = height(node->right);

    // use the larger one
    if (lheight > rheight)
      return (lheight + 1);
    else
      return (rheight + 1);
  }
}

void printCurrentLevel(struct node* root, int level) {
  if (root == NULL)
    return;

  if (level == 1)
    printf("%d ", root->key);
  else if (level > 1) {
    printCurrentLevel(root->left, level - 1);
    printCurrentLevel(root->right, level - 1);
  }
}

struct node* insertNode(struct node* root, int data) {
  // If the tree is empty, assign new node address to root.
  if (root == NULL) {
    root = newTreeNode(data);
    
    return root;
  }

  struct Queue* q = createQueue();
  enQueue(q, root);

  while (q->rear != NULL) {
    struct node* temp = q->front->data;
    deQueue(q);
 
    if (temp->left != NULL)
      enQueue(q, temp->left);
    else {
      temp->left = newTreeNode(data);

      return root;
    }
 
      if (temp->right != NULL)
        enQueue(q, temp->right);
      else {
        temp->right = newTreeNode(data);
        
        return root;
      }
    }

  return root;
}

// method 1
struct node* deletion(struct node* root, int key) {
  if(root == NULL) {
    return NULL;
  }

  if(root->left == NULL && root->right == NULL) {
    if(root->key == key)
      return NULL;
    else
      return root;
  }

  struct node* key_node = (struct node*) malloc(sizeof(struct node));
  key_node->key = NULL;
  key_node->left = NULL;
  key_node->right = NULL;
  struct node* temp = (struct node*) malloc(sizeof(struct node));
  struct node* last = (struct node*) malloc(sizeof(struct node));
  struct Queue* q = createQueue();
  enQueue(q, root);

  while(q->rear != NULL) {
    temp = q->front->data;
    deQueue(q);

    if(temp->key == key) {
      key_node = temp;
    }

    if(temp->left) {
      // storing the parent node
      last = temp;
      
      enQueue(q, temp->left);
    }

    if(temp->right) {
      // storing the parent node
      last = temp;
      
      enQueue(q, temp->right);
    }
  }

  if(key_node != NULL) {
    //replacing key_node's data to deepest node's data
    key_node->key = temp->key;

    if(last->right == temp) {
      last->right = NULL;
    } else {
      last->left = NULL;
    }
      
    free(temp);
  }
  
  return root;
}


// method 2
void deletDeepest(struct node* root, struct node* d_node) {
  struct Queue* q = createQueue();
  enQueue(q, root);

  // do level order traversal until last node
  struct node* temp = (struct node*) malloc(sizeof(struct node));

  while (q->rear != NULL) {
    temp = q->front->data;
    deQueue(q);

    if (temp == d_node) {
      temp = NULL;
      
      free(d_node);

      return;
    }

    if (temp->right) {
      if (temp->right == d_node) {
        temp->right = NULL;
        
        free(d_node);
        
        return;
      } else {
        enQueue(q, temp->right);
      }
    }

    if (temp->left) {
      if (temp->left == d_node) {
        temp->left = NULL;

        free(d_node);
        
        return;
      } else {
        enQueue(q, temp->left);
      }
    }
  }
}

struct node* deletion_2(struct node* root, int key) {
  if (root == NULL)
    return NULL;

  if (root->left == NULL && root->right == NULL) {
    if (root->key == key)
      return NULL;
    else
      return root;
  }

  struct node* key_node = (struct node*) malloc(sizeof(struct node));
  key_node->key = NULL;
  key_node->left = NULL;
  key_node->right = NULL;
  struct node* temp = (struct node*) malloc(sizeof(struct node));
  struct Queue* q = createQueue();
  enQueue(q, root);

  while (q->rear != NULL) {
    temp = q->front->data;
    deQueue(q);

    if (temp->key == key)
      key_node = temp;

    if (temp->left)
      enQueue(q, temp->left);

    if (temp->right)
      enQueue(q, temp->right);
  }

  if (key_node != NULL) {
    int x = temp->key;

    deletDeepest(root, temp);
    
    key_node->key = x;
  }
  
  return root;
}
 
int main() {
  // create root
  struct node* root = newTreeNode(1);
  /* following is the tree after above statement
       1
      / \
    NULL NULL
  */

  root->left = newTreeNode(2);
  root->right = newTreeNode(3);
  /* 2 and 3 become left and right children of 1
          1
       /     \
      2       3
    /  \     /  \
  NULL NULL NULL NULL
  */

  root->left->left = newTreeNode(4);
  /* 4 becomes left child of 2
          1
        /    \
      2      3
    /  \    /  \
    4 NULL NULL NULL
  / \
NULL NULL
  */

  root->right->left = newTreeNode(6);

  printf("\n Preorder traversal of binary tree is \n");
  printPreorder(root);

  printf("\n Inorder traversal of binary tree is \n");
  printInorder(root);

  printf("\n Postorder traversal of binary tree is \n");
  printPostorder(root);

  printf("\n Level Order traversal of binary tree is \n");
  printLevelOrder(root);

  printf("\n");

  root = insertNode(root, 5);

  printf("--- insert 5 ---");

  printf("\n Preorder traversal of binary tree is \n");
  printPreorder(root);

  printf("\n Inorder traversal of binary tree is \n");
  printInorder(root);

  printf("\n Postorder traversal of binary tree is \n");
  printPostorder(root);

  printf("\n Level Order traversal of binary tree is \n");
  printLevelOrder(root);

  root = deletion(root, 6);

  printf("\n");

  printf("--- delete 6 ---");

  printf("\n Level Order traversal of binary tree is \n");
  printLevelOrder(root);

  printf("\n");

  return 0;
}
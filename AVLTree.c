#include<stdio.h>
#include<stdlib.h>
 
// an AVL tree node
struct node {
  int key;
  struct node* left;
  struct node* right;
  int height;
};
 
// a utility function to get maximum of two integers
// int max(int a, int b);
 
// a utility function to get the height of the tree
int height(struct node* node) {
  if (node == NULL)
    return 0;
  
  return node->height;
}
 
// a utility function to get maximum of two integers
int max(int a, int b) {
  return (a > b) ? a : b;
}
 
// helper function that allocates a new node with the given key and
// NULL left and right pointers.
struct node* newNode(int key) {
  struct node* node = (struct node*) malloc(sizeof(struct node));
  
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;  // new node is initially added at leaf
  
  return node;
}

/*
     A                            B
    / \     Right Rotation       / \
   B   C    - - - - - - - >     D   A
  / \       < - - - - - - -        / \
 D   E       Left Rotation        E   C
*/

struct node* rightRotate(struct node* node) {
  struct node* left = node->left;
  struct node* left_right = left->right;

  // perform rotation
  left->right = node;
  node->left = left_right;

  // update heights
  node->height = max(height(node->left), height(node->right)) + 1;
  left->height = max(height(left->left), height(left->right)) + 1;

  // return new root
  return left;
}
 
struct node* leftRotate(struct node* node) {
  struct node* right = node->right;
  struct node* right_left = right->left;

  // perform rotation
  right->left = node;
  node->right = right_left;

  // update heights
  node->height = max(height(node->left), height(node->right)) + 1;
  right->height = max(height(right->left), height(right->right)) + 1;

  // return new root
  return right;
}
 
int getBalance(struct node* node) {
  if (node == NULL)
    return 0;
  
  return height(node->left) - height(node->right);
}
 
// recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
struct node* insert(struct node* node, int key) {
  // 1. perform the normal BST insertion
  if (node == NULL)
    return(newNode(key));

  if (key < node->key)
    node->left = insert(node->left, key);
  else if (key > node->key)
    node->right = insert(node->right, key);
  else // equal keys are not allowed in BST
    return node;

  // 2. update height of this ancestor node
  node->height = 1 + max(height(node->left), height(node->right));

  // 3. Get the balance factor of this ancestor node to check 
  // whether this node became unbalanced 
  int balance = getBalance(node);

  // If this node becomes unbalanced, then there are 4 cases.
  // Left Left Case
  if (balance > 1 && key < node->left->key)
    return rightRotate(node);

  // Right Right Case
  if (balance < -1 && key > node->right->key)
    return leftRotate(node);

  // Left Right Case
  if (balance > 1 && key > node->left->key) {
    node->left =  leftRotate(node->left);

    return rightRotate(node);
  }

  // Right Left Case
  if (balance < -1 && key < node->right->key) {
    node->right = rightRotate(node->right);

    return leftRotate(node);
  }

  // return the (unchanged) node pointer
  return node;
}

// Given a non-empty binary search tree, return the
// node with minimum key value found in that tree.
// Note that the entire tree does not need to be
// searched.
struct node* minValueNode(struct node* node) {
  struct node* current = node;

  // loop down to find the leftmost leaf
  while (current->left != NULL)
    current = current->left;

  return current;
}
 
// recursive function to delete a node with given key
// from subtree with given root
struct node* deleteNode(struct node* root, int key) {
  // step 1: peform standard BST delete
  if (root == NULL)
    return root;

  // If the key to be deleted is smaller than the
  // root's key, then it lies in left subtree.
  if ( key < root->key )
    root->left = deleteNode(root->left, key);

  // If the key to be deleted is greater than the
  // root's key, then it lies in right subtree.
  else if( key > root->key )
    root->right = deleteNode(root->right, key);

  // If key is same as root's key, then This is
  // the node to be deleted.
  else {
    // node with only one child or no child
    if((root->left == NULL) || (root->right == NULL)) {
      struct node* temp = root->left ? root->left : root->right;

      // no child case
      if (temp == NULL)
        root = NULL;
      // one child case
      else
        // copy the contents of the non-empty child
        *root = *temp;

      free(temp);
    }
    else {
      // node with two children: get the inorder
      // successor (smallest in the right subtree)
      struct node* temp = minValueNode(root->right);

      // copy the inorder successor's data to this node
      root->key = temp->key;

      // delete the inorder successor
      root->right = deleteNode(root->right, temp->key);
    }
  }
 
  // if the tree had only one node then return
  if (root == NULL)
    return root;

  // step 2: update height oh the current node
  root->height = 1 + max(height(root->left), height(root->right));
 
  // step 3: get the balance factor of this node 
  // (to check whether this node became unbalanced)
  int balance = getBalance(root);

  // If this node becomes unbalanced, then there are 4 cases.
 
  // Left Left Case
  if (balance > 1 && getBalance(root->left) >= 0)
  // if (balance > 1 && key < node->left->key)
    return rightRotate(root);
 
  // Left Right Case
  if (balance > 1 && getBalance(root->left) < 0) {
  // if (balance > 1 && key > node->left->key)
    root->left =  leftRotate(root->left);

    return rightRotate(root);
  }
 
  // Right Right Case
  if (balance < -1 && getBalance(root->right) <= 0)
  // if (balance < -1 && key > node->right->key)
    return leftRotate(root);

  // Right Left Case
  if (balance < -1 && getBalance(root->right) > 0) {
  // if (balance < -1 && key < node->right->key)
    root->right = rightRotate(root->right);

    return leftRotate(root);
  }
 
  return root;
}
 
// a utility function to print preorder traversal of the tree
// the function also prints height of every node
void preOrder(struct node* root) {
  if(root != NULL) {
    printf("%d ", root->key);
    
    preOrder(root->left);
    preOrder(root->right);
  }
}
 
int main() {
  struct node* root = NULL;
  struct node* root_2 = NULL;
 
  // constructing tree given in the above figure
  root = insert(root, 10);
  root = insert(root, 20);
  root = insert(root, 30);
  root = insert(root, 40);
  root = insert(root, 50);
  root = insert(root, 25);
 
  /* the constructed AVL Tree would be
            30
           /  \
         20   40
        /  \     \
       10  25    50
  */
 
  printf("Preorder traversal of the constructed AVL tree is \n");
  preOrder(root);

  // constructing tree given in the above figure
  root_2 = insert(root_2, 9);
  root_2 = insert(root_2, 5);
  root_2 = insert(root_2, 10);
  root_2 = insert(root_2, 0);
  root_2 = insert(root_2, 6);
  root_2 = insert(root_2, 11);
  root_2 = insert(root_2, -1);
  root_2 = insert(root_2, 1);
  root_2 = insert(root_2, 2);
 
  /* the constructed AVL Tree would be
          9
          /  \
        1    10
      /  \     \
      0    5     11
    /    /  \
    -1   2    6
  */
 
  printf("Preorder traversal of the constructed AVL tree is \n");
  preOrder(root_2);

  root = deleteNode(root_2, 10);
 
  /* The AVL Tree after deletion of 10
          1
          /  \
        0    9
      /     /  \
      -1    5     11
          /  \
        2    6
  */
 
  printf("\nPreorder traversal after deletion of 10 \n");
  preOrder(root);

  printf("\n");
 
  return 0;
}
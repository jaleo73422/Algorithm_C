#include<stdio.h>
#include<stdlib.h>

void preOrder(struct node* root);

// An AVL tree node
struct node {
  int key;
  struct node* left;
  struct node* right;
  struct node* parent;
};

// global root for the entire tree
struct node* root = NULL;
 
// Helper function that allocates a new node with the given key and
// NULL left and right pointers.
struct node* newNode(int key) {
  struct node* node = (struct node*) malloc(sizeof(struct node));
  
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->parent = NULL;
  
  return node;
}

struct node* maxNode(struct node* node) {
  while(node->right != NULL)
    node = node->right;
  
  return node;
}

void setVariable(struct node* node) {
  root = node;
}

/*      y                                      x
       / \     Zig (Right Rotation)           / \
      x  T3    - - - - - - - - - >          T1   y 
     / \       < - - - - - - - - -              / \
    T1  T2     Zag (Left Rotation)            T2   T3 */

// a utility function to right rotate subtree rooted with y
// see the diagram given above.
void rightRotate(struct node* x) {
  struct node* y = x->left;

  x->left = y->right;

  if(y->right != NULL) {
    y->right->parent = x;
  }

  y->parent = x->parent;

  if(x->parent == NULL)
    root = y;
  else if(x == x->parent->right)
    x->parent->right = y;
  else if(x == x->parent->left)
    x->parent->left = y;

  y->right = x;
  x->parent = y;
}
 
// a utility function to left rotate subtree rooted with x
// see the diagram given above.
void leftRotate(struct node* x) {
  struct node* y = x->right;
  
  x->right = y->left;

  if(y->left != NULL)
    y->left->parent = x;

  y->parent = x->parent;

  if(x->parent == NULL)
    root = y;
  else if(x == x->parent->left)
    x->parent->left = y;
  else if(x == x->parent->right)
    x->parent->right = y;

  y->left = x;
  x->parent = y;
}
 
// This function brings the key at root if key is present in tree.
// If key is not present, then it brings the last accessed item at root.
// This function modifies the tree and returns the new root
void splay(struct node* now, int key) {
  struct node* node = now;
  struct node* temp = now->parent;

  while(node->key != key) {
    if(node->key > key) {
      if(node->left == NULL)
        break;
      else
        node = node->left;
    }
    else if(node->key < key) {
      if(node->right == NULL)
        break;
      else
        node = node->right;
    }
  }

  // node is not root
  while(node->parent != temp) {  
    // node is child of root, one rotation
    if(node->parent == now) {
      if(node == node->parent->left)
        rightRotate(node->parent);
      else 
        leftRotate(node->parent);
    }
    else {
      // Zig-Zig (Left Left)
      if(node->parent->left == node && node->parent->parent->left == node->parent) {
        rightRotate(node->parent->parent);
        rightRotate(node->parent);
      }
      // Zag-Zag (Right Right)
      else if(node->parent->right == node && node->parent->parent->right == node->parent) {
        leftRotate(node->parent->parent);
        leftRotate(node->parent);
      }
      // Zig-Zag (Left Right)
      else if(node->parent->right == node && node->parent->parent->left == node->parent) {
        leftRotate(node->parent);
        rightRotate(node->parent);
      }
      // Zag-Zig (Right Left)
      else if(node->parent->left == node && node->parent->parent->right == node->parent) {
        rightRotate(node->parent);
        leftRotate(node->parent);
      }
    }
  }
}
 
// The search function for Splay tree.
// Note that this function returns the new root of Splay Tree.
// If key is present in tree then, it is moved to root.
void search(struct node* root, int key) {
  return splay(root, key);
}

// Function to insert a new key k in splay tree with given root
struct node* insert(struct node* root, int k) {
  if (root == NULL)
    return newNode(k);

  struct node* newnode = newNode(k);
  struct node* parent;
  struct node* temp = root;

  while (temp != NULL) {
    parent = temp;

    if (newnode->key < temp->key)
      temp = temp->left;
    else
      temp = temp->right;
  }

  if (parent == NULL)
    return newnode;
  else if (newnode->key < parent->key) {
    parent->left = newnode;
    newnode->parent = parent;
  }
  else {
    parent->right = newnode;
    newnode->parent = parent;
  }

  splay(root, k);

  // newnode becomes new root
  return newnode;
}

// the delete function for Splay tree
// Note that this function returns the new root of Splay Tree after removing the key 
void delete_key(int key) {
  struct node* temp;

  if(!root)
    printf("Tree is empty.");

  // splay the given key    
  splay(root, key);

  if (!root->left) {
    temp = root;
    root->right->parent = NULL;
    root = root->right;
  }
  // else if left child exits
  else {
    struct node* maxnode = NULL;
    temp = root;

    maxnode = maxNode(root->left);

    splay(root->left, maxnode->key);

    root->left->parent = NULL;

    root = root->left;
        
    root->right = temp->right;
    
    if(temp->right != NULL)
      root->right->parent = root;
  }
    
  // free the previous root node, that is, the node containing the key
  free(temp);
}

// A utility function to print preorder traversal of the tree.
// The function also prints height of every node.
void preOrder(struct node* root) {
  if (root != NULL) {
    printf("%d ", root->key);
    
    preOrder(root->left);
    preOrder(root->right);
  }
}
 
int main() {
  struct node* root1 = NULL;
  
  setVariable(root1);

  root = insert(root, 15);
  root = insert(root, 10);
  root = insert(root, 17);
  root = insert(root, 7);
  root = insert(root, 13);
  root = insert(root, 16);
  
  printf("Preorder traversal of the Splay tree is \n");
  preOrder(root);
  printf("\n");

  struct node* root2 = NULL;

  setVariable(root2);

  root = newNode(12);
  root->left = newNode(10);
  root->left->parent = root;
  root->left->left = newNode(7);
  root->left->left->parent = root->left;
  root->right = newNode(13);
  root->right->parent = root;
  root->right->right = newNode(14);
  root->right->right->parent = root->right;
  root->right->right->right = newNode(16);
  root->right->right->right->parent = root->right->right;
  root->right->right->right->left = newNode(15);
  root->right->right->right->left->parent = root->right->right->right;
  root->right->right->right->right = newNode(17);
  root->right->right->right->right->parent = root->right->right->right;

  printf("Preorder traversal of the Splay tree is \n");
  preOrder(root);
  printf("\n");

  delete_key(16);
  delete_key(12);
  delete_key(7);
  delete_key(17);

  printf("Preorder traversal of the modified Splay tree is \n");
  preOrder(root);
  printf("\n");
  
  return 0;
}
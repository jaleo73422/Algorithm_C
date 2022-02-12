#include <stdio.h>
#include <stdlib.h>

// structure to represent each node in a red-black tree
struct node {
  int data;
  int color; // 1 red, 0 black
  struct node* parent; // parent
  struct node* right; // right child
  struct node* left; // left child
};
 
// global root for the entire tree
struct node* root = NULL;

struct node* search(struct node* root, int key);
struct node* successor(struct node* node);
struct node* predecessor(struct node* node);
void addNULLnode(struct node* node);
void deleteNULLnode(struct node* node);

// function performing right rotation of the passed node
void rightRotate(struct node* node) {
  struct node* left = node->left;
  node->left = left->right;
  
  if (node->left)
    node->left->parent = node;
  
  left->parent = node->parent;
  
  if (!node->parent)
    root = left;
  else if (node == node->parent->left)
    node->parent->left = left;
  else
    node->parent->right = left;
  
  left->right = node;
  node->parent = left;
}
 
// function performing left rotation of the passed node
void leftRotate(struct node* node) {
  struct node* right = node->right;
  node->right = right->left;

  if (node->right)
    node->right->parent = node;
  
  right->parent = node->parent;
  
  if (!node->parent)
    root = right;
  else if (node == node->parent->left)
    node->parent->left = right;
  else
    node->parent->right = right;
  
  right->left = node;
  node->parent = right;
}

// function to perform BST insertion of a node
struct node* bstInsert(struct node* node, struct node* new_node) {
  // If the tree is empty, return a new node.
  if (node == NULL)
    return new_node;

  // otherwise recur down the tree
  if (new_node->data < node->data) {
    node->left = bstInsert(node->left, new_node);
    node->left->parent = node;
  }
  else if (new_node->data > node->data) {
    node->right = bstInsert(node->right, new_node);
    node->right->parent = node;
  }

  // return the (unchanged) node pointer
  return node;
}

// This function fixes violations caused by BST insertion.
void insertFixup(struct node* root, struct node* pt) {
  struct node* parent_pt = NULL;
  struct node* grand_parent_pt = NULL;

  // 1 red, 0 black
  while (pt != root && pt->color != 0 && pt->parent->color == 1) {
    parent_pt = pt->parent;
    grand_parent_pt = pt->parent->parent;

    //  Case: parent of pt is left child of grandparent of pt.
    // LL or LR
    if (parent_pt == grand_parent_pt->left) {
      struct node* uncle_pt = grand_parent_pt->right;

      // Case B: the uncle of pt is also red.
      // only Recoloring required
      if (uncle_pt != NULL && uncle_pt->color == 1) {
        grand_parent_pt->color = 1;
        parent_pt->color = 0;
        uncle_pt->color = 0;
        pt = grand_parent_pt;
      }
      else {
        // case A2: pt is right child of its parent. (LR)
        // Left-rotation required
        // convert LR to LL
        if (pt == parent_pt->right) {
          leftRotate(parent_pt);

          pt = parent_pt;
          // not sure if this line can be deleted
          parent_pt = pt->parent;
        }

        // Case  A1: pt is left child of its parent. (LL)
        // Right-rotation required
        rightRotate(grand_parent_pt);

        int t = parent_pt->color;     
        
        parent_pt->color = grand_parent_pt->color;
        grand_parent_pt->color = t;
        pt = parent_pt;
      }
    }

    // Case : parent of pt is right child of Grand-parent of pt.
    // RR or RL
    else {
      struct node* uncle_pt = grand_parent_pt->left;

      // Case B: the uncle of pt is also red.
      // Only Recoloring required
      if (uncle_pt != NULL && uncle_pt->color == 1) {
        grand_parent_pt->color = 1;
        parent_pt->color = 0;
        uncle_pt->color = 0;
        pt = grand_parent_pt;
      }
      else {
        // Case A2: pt is left child of its parent. (RL)
        // Right-rotation required
        // convert RL to RR
        if (pt == parent_pt->left) {
          rightRotate(parent_pt);

          pt = parent_pt;
          // not sure if this line can be deleted
          parent_pt = pt->parent;
        }

        // Case A1: pt is right child of its parent. (RR)
        // Left-rotation required
        leftRotate(grand_parent_pt);
        
        int t = parent_pt->color;
        
        parent_pt->color = grand_parent_pt->color;
        grand_parent_pt->color = t;
        pt = parent_pt;
      }
    }
  }

  while (root->parent)
    root = root->parent;

  root->color = 0;
}

void deleteFixup(struct node* root, struct node* current) {  
  addNULLnode(root);

  // Case 1, 2, 3, 4
  while (current != root && current->color == 0) {
    // current is left child
    if (current == current->parent->left) {
      struct node* sibling = current->parent->right;
      
      // Case1
      if (sibling->color == 1) {
        sibling->color = 0;
        current->parent->color = 1;

        leftRotate(current->parent);
        
        sibling = current->parent->right;
      }

      // Case2
      if (sibling->left->color == 0 && sibling->right->color == 0) {
        sibling->color = 1;
        current = current->parent;
      }
      // Case3, 4
      else {
        // Case3
        if (sibling->right->color == 0){
          sibling->left->color = 0;
          sibling->color = 1;

          rightRotate(sibling);

          sibling = current->parent->right;
        }

        // Case 4
        sibling->color = current->parent->color;
        current->parent->color = 0;
        sibling->right->color = 0;
        
        leftRotate(current->parent);
        
        // let current as root, then leave loop
        current = root;
      }
    }
    // current is right child
    else {  
      struct node* sibling = current->parent->left;
      
      // Case1
      if (sibling->color == 1) {
        sibling->color = 0;
        current->parent->color = 1;
        
        rightRotate(current->parent);
        
        sibling = current->parent->left;
      }

      // Case2
      if (sibling->left->color == 0 && sibling->right->color == 0) {
        sibling->color = 1;
        current = current->parent;
      }
      // Case3, 4
      else {
        // case3
        if (sibling->left->color == 0){
          sibling->right->color = 0;
          sibling->color = 1;
          
          leftRotate(sibling);
          
          sibling = current->parent->left;
        }
          
        // Case 4
        sibling->color = current->parent->color;
        current->parent->color = 0;
        sibling->left->color = 0;
        
        rightRotate(current->parent);
        
        // let current as root, then leave loop
        current = root;
      }
    }
  }

  // (1) Case0: if current is red, color it black.
  // (2) If current is root, color it black.
  current->color = 0;
}

// bst delete
void rbtDelete(struct node* root, int key) {
  struct node* deleted_node = search(root, key);

  if (deleted_node == NULL)
    printf("Key not found. \n");
  
  // Step1: replace replacement to current.
  // Step2: replace deleted note to replacement.
  // If at least one of the deleted node's children is NULL,
  // replacement equal to deleted node.
  // Step1 can view as replace ddeleted node to current and
  // neglect step2. 
  struct node* replacement = NULL;
  struct node* current = (struct node*) malloc(sizeof(struct node));

  // chek if at least one of the deleted node's children is NULL
  if (deleted_node->left == NULL || deleted_node->right == NULL)
    replacement = deleted_node;
  else
    replacement = successor(deleted_node);

  if (replacement->left != NULL) {
    current = replacement->left;
    // step1
    current->parent = replacement->parent;
  }
  else if (replacement->left == NULL && replacement->right != NULL) {
    current = replacement->right;
    // step1
    current->parent = replacement->parent;
  }
  else {
    current->right = NULL;
    current->left = NULL;
    current->parent = NULL;
    current->data = -1;
    current->color = 0;

    current->parent = replacement->parent;
  }

  // step1
  if (replacement->parent == NULL)
    root = current;
  else if (replacement == replacement->parent->left)
    replacement->parent->left = current;
  else
    replacement->parent->right = current;

  // step2
  if (replacement != deleted_node)
    deleted_node->data = replacement->data;

  // If color of replacement is black, fixup current node.
  if (replacement->color == 0) {
    deleteFixup(root, current);
  }

  free(replacement);

  deleteNULLnode(root);
}

struct node* search(struct node* root, int key) {
  struct node* current = root;

  // If there is not ket, return NULL (0).
  while (current != NULL && key != current->data) {
    if (key < current->data)
      current = current->left;
    else
      current = current->right;
  }

  return current;
}

struct node* successor(struct node* node) {
  struct node* temp = node->right;

  if (temp != NULL) {
    while (temp->left != NULL)
      temp = temp->left;
  }

  return temp;
}

struct node* predecessor(struct node* node){
  struct node* temp = node->left;

  if (temp != NULL) {
    while (temp->right != NULL)
      temp = temp->right;
  }

  return temp;
}

void addNULLnode(struct node* node) {
  if (node->left == NULL && node->right != NULL) {
    struct node* temp = (struct node*) malloc(sizeof(struct node));

    temp->right = NULL;
    temp->left = NULL;
    temp->parent = NULL;
    temp->data = -1;
    temp->color = 0;

    temp->parent = node;
    
    node->left = temp;
  
    addNULLnode(node->right);
      
    return;
  }
  else if (node->left != NULL && node->right == NULL) {
    struct node* temp = (struct node*) malloc(sizeof(struct node));

    temp->right = NULL;
    temp->left = NULL;
    temp->parent = NULL;
    temp->data = -1;
    temp->color = 0;

    temp->parent = node;
    
    node->right = temp;

    addNULLnode(node->left);
    
    return;
  }
  else if (node->left == NULL && node->right == NULL) {
    struct node* temp_left = (struct node*) malloc(sizeof(struct node));
    struct node* temp_right = (struct node*) malloc(sizeof(struct node));

    temp_left->right = NULL;
    temp_left->left = NULL;
    temp_left->parent = NULL;
    temp_left->data = -1;
    temp_left->color = 0;

    temp_left->parent = node;

    temp_right->right = NULL;
    temp_right->left = NULL;
    temp_right->parent = NULL;
    temp_right->data = -1;
    temp_right->color = 0;

    temp_right->parent = node;
    
    node->left = temp_left;
    node->right = temp_right;

    return;
  }

  addNULLnode(node->left);  
  addNULLnode(node->right);
}

void deleteNULLnode(struct node* node) {
  if (node == NULL)
    return;
 
  deleteNULLnode(node->left);

  if (node->data == -1) {
    if (node == node->parent->left)
      node->parent->left = NULL;
    else
      node->parent->right = NULL;

    free(node);
  }
  
  deleteNULLnode(node->right);
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

void currentLevel(struct node* root, int level) {
  if (root == NULL)
    return;

  if (level == 1)
    printf("%d(%d) ", root->data, root->color);
  else if (level > 1) {
    currentLevel(root->left, level - 1);
    currentLevel(root->right, level - 1);
  }
}

void printPreorder(struct node* node) {
  if (node == NULL)
    return;

  // first print data of node
  printf("%d(%d) ", node->data, node->color);

  // then recur on left subtree
  printPreorder(node->left);

  // now recur on right subtree
  printPreorder(node->right);
}

// function to print inorder traversal of the fixated tree
void inorder(struct node* node) {
  if (node == NULL)
    return;
  
  inorder(node->left);

  printf("%d(%d) ", node->data, node->color);
  
  inorder(node->right);
}

void levelOrder(struct node* node) {
  int h = height(node);
  int i;

  for (i = 1; i <= h; i++)
    currentLevel(node, i);
}
 
int main() {
  // example 1
  // int n = 7;
  // int a[7] = {7, 6, 5, 4, 3, 2, 1};

  // example 2
  int n = 11;
  int a[11] = {7, 3, 18, 10, 22, 8, 11, 26, 2, 6, 13};
 
  for (int i = 0; i < n; i++) {
    // allocating memory to the node and initializing:
    // 1. color as red
    // 2. parent, left and right pointers as NULL
    // 3. data as i-th value in the array
    struct node* node = (struct node*) malloc(sizeof(struct node));
    node->right = NULL;
    node->left = NULL;
    node->parent = NULL;
    node->data = a[i];
    node->color = 1;

    // calling function that performs bst insertion of
    // this newly created node
    root = bstInsert(root, node);

    // calling function to preserve properties of rb tree
    insertFixup(root, node);
  }

  printf("\n \n");
 
  printf("Inorder Traversal of Created Tree\n");
  
  inorder(root);

  printf("\n");
  printf("Level Order Traversal of Created Tree\n");

  levelOrder(root);

  printf("\n");

  // printPreorder(root);

  // printf("root is %d \n", root->data);

  // search test
  // int n2 = 30;
  // struct node* node_t1 = search(root, n2);

  // if (node_t1 == NULL)
  //   printf("Key not found. \n");
  // else
  //   printf("%d \n", node_t1->data);

  // successor and predecessor test
  // struct node* node_t2 = successor(root->left->left);
  // printf("%d \n", node_t2->data);
  // struct node* node_t2 = predecessor(root);
  // printf("%d \n", node_t2->data);

  // int n3 = 10;
  // bstDelete(root, n3);

  // levelOrder(root);

  // printf("\n");

  // addNULLnode(root);
  rbtDelete(root, 18);
  rbtDelete(root, 11);
  rbtDelete(root, 3);
  rbtDelete(root, 10);
  rbtDelete(root, 22);

  // addNULLnode(root);

  printf("Inorder Traversal of Created Tree \n");
  
  inorder(root);

  printf("\n");
  printf("Level Order Traversal of Created Tree \n");

  levelOrder(root);

  printf("\n");

  // printf("%d \n", root->right->right->right->data);

  return 0;
}
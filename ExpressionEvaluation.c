#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// step1: convert infix to postfix.
// step2: evualate postfix.

struct Stack {
  int top;
  unsigned capacity;
  int* array;
};

// Stack Operations
struct Stack* createStack(unsigned capacity) {
  struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));

  if (!stack) 
    return NULL;

  stack->top = -1;
  stack->capacity = capacity;
  stack->array = (int*) malloc(stack->capacity * sizeof(int));

  return stack;
}

int isEmpty(struct Stack* stack) {
  return stack->top == -1 ;
}

int peek(struct Stack* stack) {
  return stack->array[stack->top];
}

char pop(struct Stack* stack) {
  if (!isEmpty(stack))
    return stack->array[stack->top--] ;
  
  return '$';
}

void push(struct Stack* stack, int op) {
  

  stack->array[++stack->top] = op;
}

// Function to find precedence of operators.
int precedence(char op) {
  switch (op) {
    case '+': return 1;
    case '-': return 1;
    case '*': return 2;
    case '/': return 2;
  }

  return -1;
}
 
// Function to perform arithmetic operations.
int applyOp(int a, int b, char op) {
  switch(op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
  }

  return 0;
}

int evaluate(const char* exp) {
  int i;

  // Create a stack of capacity equal to expression size. 
  struct Stack* values = createStack(strlen(exp));

  struct Stack* ops = createStack(strlen(exp));

  for (i = 0; i < strlen(exp); i++) {
    // Current token is a whitespace skip it.
    if(exp[i] == ' ')
      continue;
    
    // Current token is an opening brace, push it to 'ops'.
    else if(exp[i] == '(') {
      push(ops, exp[i]);
    }

    // Current token is a number, push it to stack for numbers.
    else if(isdigit(exp[i])) {
      int val = 0;
             
      // There may be more than one digits in number.
      while(i < strlen(exp) && isdigit(exp[i])) {
        val = (val * 10) + (exp[i] - '0');
        i++;
      }
             
      push(values, val);
             
      i--;
    }

    // Closing brace encountered, solve entire brace.
    else if(exp[i] == ')') {
      while(!isEmpty(ops) && peek(ops) != '(') {
        int val2 = peek(values);
        pop(values);
        
        int val1 = peek(values);
        pop(values);
                
        char op = peek(ops);
        pop(ops);
                
        push(values, applyOp(val1, val2, op));
      }
            
      // pop opening brace
      if(!isEmpty(ops))
        pop(ops);
    }

    // Current token is an operator.
    else {
      // While top of 'ops' has same or greater precedence to current token, which is an operator.
      //  Apply operator on top of 'ops' to top two elements in values stack.
      while(!isEmpty(ops) && precedence(peek(ops)) >= precedence(exp[i])) {
        int val2 = peek(values);
        pop(values);
                 
        int val1 = peek(values);
        pop(values);
                 
        char op = peek(ops);
        pop(ops);
                 
        push(values, applyOp(val1, val2, op));
      }
             
      // Push current token to 'ops'.
      push(ops, exp[i]);
    }    
  }

  // Entire expression has been parsed at this point, 
  // apply remaining ops to remaining values.
  while (!isEmpty(ops)) {
    int val2 = peek(values);
    pop(values);

    int val1 = peek(values);
    pop(values);

    char op = peek(ops);
    pop(ops);

    push(values, applyOp(val1, val2, op));
  }

  // Top of 'values' contains result, return it.
  return peek(values);
}
 
int main() {
  printf("%d \n", evaluate("10 + 2 * 6"));
  printf("%d \n", evaluate("100 * 2 + 12"));
  printf("%d \n", evaluate("100 * ( 2 + 12 )"));
  printf("%d \n", evaluate("100 * ( 2 + 12 ) / 14"));

  return 0;
}
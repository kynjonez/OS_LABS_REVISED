// <Author - Kyndall Jones>
// Collaborated with: Zoe Carter and Abigial Thomas
// Resources: stackoverflow and geeksforgeeks

#include <stdio.h>
#include <stdlib.h>

/* IMPLEMENT ME: Declare your functions here */
typedef int(*Operation) (int a, int b);
int add (int a, int b);
int sub (int a, int b);
int mult(int a, int b);
int divide (int a, int b);


int main (void)
{
	/* IMPLEMENT ME: Insert your algorithm here */
  Operation operations[4];
  char operation[10];
  int op;

  operations[0] = &add;
  operations[1] = &sub;
  operations[2] = &mult;
  operations[3] = &divide;

  int a = 6;
  int b = 3;
  int r;

  while(1) 
  {
    printf("Operand 'a' : %d | Operand 'b' : %d \n Specify the operation to perform \n(0 : add | 1 : subtract | 2 : multiply | 3: divide | 4 : exit):", a, b);
    scanf("%s", operation);
    op = atoi(operation);
    while (op > 4)
    {
      printf("Specify the operation to perform (0 : add | 1 : subtract | 2 : Multiply | 3 : divide | 4 : exit):");
      scanf("%s", operation);
      op = atoi(operation);
    }
    if (op == 4){ break; }
    r = (*operations[op])(a, b);
    printf("x = %d\n", r);

  }

	return 0;
}

/* IMPLEMENT ME: Define your functions here */
int add (int a, int b) { printf ("Adding 'a' and 'b'\n"); return a + b;}
int sub (int a, int b) { printf ("Subtracting 'a' and 'b'\n"); return a - b;}
int mult (int a, int b) { printf ("Multiplying 'a' and 'b'\n"); return a * b;}
int divide (int a, int b) { printf ("Dividing 'a' and 'b'\n"); return a / b;}

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int precedence(char * operator);
int is_number(char * input);
char associativity(char * operator);
float compute_rpn(char ** tokens, int size);
float compute_operator(char * operator, int leftNumber, int rightNumber);
char ** shunt(char * tokens[], int size, char * output[]);

int precedence(char * operator)
{
   if ('^' == *operator) return 2;
   if ('x' == *operator || '/' == *operator || '%' == *operator) return 1;
   if ('+' == *operator || '-' == *operator) return 0;
   return -1;
}

int is_number(char * input)
{
   int i = 0;
   char * validInputs = "0123456789";
   
   // Ignore negative sign
   if (input[0] == '-')
   {
      i = 1;
   }
   
   for (; i < strlen(input); i++)
   {
      if (!strchr(validInputs, input[i])) {
         return 0;
      }
   }
   
   return 1;
}

char associativity(char * operator)
{
   if ('^' == *operator) return 'r';
   return 'l';
}

char ** shunt(char* tokens[], int size, char* output[])
{
   int number;
   int outputCount = 0, operatorCount = 0;
   const char * validOperators = "+-x/%"; // Option: add ^ to support powers in expressions
   char * operators[size], * operator1, * operator2;
   
   for (int i = 0; i < size; i++)
   {
      number = atoi(tokens[i]);
      
      if (i % 2 == 0)
      {
         // If the token is a number, add it to the output queue.
         if (is_number(tokens[i]) && ('0' == *tokens[i] || abs(number) > 0))
         {
            output[outputCount] = tokens[i];
            outputCount++;
            continue;
         }
         else
         {
            printf("Invalid number in expression.\n");
            exit(0);
         }
      }
      
      
      // If the token is not a number, then it is an operator...
      operator1 = tokens[i];
      
      if (!strchr(validOperators, *operator1) || (int)strlen(operator1) != 1)
      {
         printf("Invalid math operation in expression.\n");
         exit(0);
      }
      
      // While there is an operator operator2 atop the operator stack and either
      // - operator1 is left associative, and precedence(operator1) <= precedence(operator2)
      // - operator1 is right-associative, and precedence(operator1) < precedence(operator2)
      // Pop o2 off the stack onto the output queue
      while (operatorCount > 0 && (operator2 = operators[operatorCount - 1]))
      {
         if (( associativity(operator1) == 'l' && precedence(operator1) <= precedence(operator2) )
             ||
             ( associativity(operator1) == 'r' && precedence(operator1) < precedence(operator2) )
         ) {
            output[outputCount] = operator2;
            outputCount++;
            operatorCount--;
         }
         else
         {
            break;
         }
      }
      
      // Push the operator onto the operator stack.
      operators[operatorCount] = operator1;
      operatorCount++;
   }
   
   // Dump the rest of the operators onto the output stack
   while (operatorCount > 0)
   {
      output[outputCount] = operators[operatorCount - 1];
      outputCount++;
      operatorCount--;
   }
   
   return output;
}

float compute_rpn(char ** tokens, int size)
{
   char * operator;
   int numberCount = 0;
   int numbers[size], leftNumber, rightNumber, number;
   
   for (int i = 0; i < size; i++)
   {
      number = atof(tokens[i]);

      // If the token is a number, add it to the number stack
      if ('0' == *tokens[i] || abs(number) > 0)
      {
         numbers[numberCount] = number;
         numberCount++;
         continue;
      }
      
      // The token is an operator (operator); we pop two numbers (rightNumber, leftNumber)
      // from the number stack, compute leftNumber operator rightNumber and
      // push its value to the number stack
      leftNumber = numbers[numberCount - 2];
      operator = tokens[i];
      rightNumber = numbers[numberCount - 1];
      
      if (rightNumber == 0 && *operator == '/')
      {
         printf("Division by zero.\n");
         exit(0);
      }
      
      numbers[numberCount - 2] = compute_operator(operator, leftNumber, rightNumber);
      numberCount--;
   }
   
   return numbers[0];
}

float compute_operator(char* operator, int leftNumber, int rightNumber)
{
   if ('x' == *operator) return leftNumber * rightNumber;
   if ('/' == *operator) return leftNumber / rightNumber;
   if ('+' == *operator) return leftNumber + rightNumber;
   if ('-' == *operator) return leftNumber - rightNumber;
   if ('%' == *operator) return fmod(leftNumber, rightNumber);
   if ('^' == *operator) return powf(leftNumber, rightNumber);
   return 0;
}

int main(int argc, char* argv[])
{
   int size = argc - 1;
   
   printf("Calculator by Abdelrahman Ahmed (12445336)\n");
   
   if (size <= 0) {
      printf("Invalid arguments in expression.\n");
      exit(0);
   }
   
   for (int i = 1; i < argc; i++)
   {
      argv[i - 1] = argv[i];
   }
   
   // Convert to reverse polish notation
   char* rpn[size];
   shunt(argv, size, rpn);
   
   // Using float for more accurate results
   int result = compute_rpn(rpn, size);
   
   printf("%d\n", result);
}

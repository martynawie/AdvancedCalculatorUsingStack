/***************************************************************/
/* Programmer: Martyna Wieczorek                               */ 
/* Program: Advanced Calculator                                */
/*        -Evaluate arithmetic expression using stacks,        */
/*        -The program works on integers but can return double */
/*        -The program ignores spaces,                         */
/*        -The program include imput validations,              */
/*        -Program can include negative numbers,               */
/*          examples:                                          */
/*                    -2-(-2) = 0                              */
/*                    6/0 = Error                              */
/*                    6 + 7 - 12/2+ (7-10) = 4                 */
/*                    11/5 = 2.2                               */
/*                    -2*7+1-1/2*5 = -15.5                     */
/***************************************************************/

#include <iostream>
#include <cctype>
#include "Stack.cpp"
using namespace std;

//Functions prototypes
int printMenu();
int priority(char);
double solveOperation(double, double, char);
double evaluteExpression(string);
bool isOperator(char);


//************************** Main Program ************************/
int main ()
{
  int choice;
  string userExpression;
  
  cout << "Advanced Calculator will evaluate your arithmetic expression using stacks." << endl;
  cout << "   -You can use operators such as +, -, *, /" << endl;
  cout << "   -You can use parentheses." << endl;
  cout << "   -The expression can have negative numbers." << endl;
  cout << "   -The expression can have spaces in it." << endl;
  choice = printMenu();

  //Continue till the user chooses to quit
  while (choice != 2)
  {
    if ( choice == 1 )
    {
      //Ignore any characters left in the input buffer
      cin.ignore();
      cout << "Enter your Expression: ";
      getline(cin, userExpression);
      
      //An error will be displayed if the user inputs spaces (empty stack)
      cout <<"The result is : "<< evaluteExpression(userExpression) << "\n"; 
    }
    //Check if the input is integer
    else if (cin.fail())
    {
      cin.clear();       
      cin.ignore(100, '\n');
      cout << "\nInvalid input. Please enter a number.\n\n";
    }
    else
    {
      cout<<"\nNumber is not correct. Please look at choices and reenter a number\n\n";
      //Ignore 100 characters or till new line 
      cin.ignore(100, '\n');
    }
    choice = printMenu();
  }

  cout<<"\nProgram ended, see you next time!\n\n";
  return 0;
}


//********************Functions Implementation********************//

//print main menu with choices
int printMenu()
{
  {
     int c;
     cout << "\nMain menu:";
     cout << "\n1: Evaluate an expression.";
     cout << "\n2: Quit.\n";
     cout << "\nEnter a number: ";
     cin >> c;
     return c;
  }
}

//which operations should be handle first
int priority(char symbol)
{ 
  if(symbol == '+'||symbol == '-') 
  {
    return 1;
  }
  if(symbol == '*'||symbol == '/') 
  {
    return 2; 
  }
  return 0; 
} 

//arithmetic operations. 
double solveOperation(double x, double y, char symbol)
{
    if (symbol == '+')
        return x + y;
    if (symbol == '-')
        return x - y;
    if (symbol == '*')
        return x * y;
    if (symbol == '/')
    {
        if (y != 0)
            return x / y;
        else
        {
            cerr << "Error: Division by zero." << endl;
            return 0; 
        }
    }
    return 0;
}

//check if a character is an operator
bool isOperator(char symbol)
{
    return (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/');
}

//returns value of expression after evaluation. 
double evaluteExpression(string expression)
{
  Stack<double> numbers;
  Stack<char> operators;
  bool expectOperand = true;
  int i;

  for(i=0; i<expression.length();i++)
  {
    //Ignore spaces
    if(expression[i] == ' ')
    {
      //continue
    }
    // opening parentheses
    else if(expression[i] == '(')
    {
      operators.push(expression[i]);
      expectOperand = true;
    }
    //negative numbers
    else if (isdigit(expression[i]) || (expression[i] == '-' && expectOperand))
    {
      int val = 0;
      int sign = 1;

        if (expression[i] == '-')
        {
            sign = -1;
            i++;
        }

        while (i < expression.length() && (isdigit(expression[i])))
        {
            val = (val * 10) + (expression[i] - '0');
            i++;
        }

        numbers.push(sign * val);
        i--;
        expectOperand = false;
    }
    //closing parentheses
    else if (expression[i] == ')')
    {
      while (!operators.isEmpty() && operators.getTop() != '(')
      {
        double val2 = numbers.getTop();
        numbers.pop();
        double val1 = numbers.getTop();
        numbers.pop();
        char op = operators.getTop();
        operators.pop();
        numbers.push(solveOperation(val1, val2, op));
      }
      if (!operators.isEmpty())
        operators.pop();
      expectOperand = false;
    }
    //operators
    else if (isOperator(expression[i]))
    {
        while (!operators.isEmpty() && priority(operators.getTop()) >= priority(expression[i]))
        {
            double val2 = numbers.getTop();
            numbers.pop();
            double val1 = numbers.getTop();
            numbers.pop();
            char op = operators.getTop();
            operators.pop();
            numbers.push(solveOperation(val1, val2, op));
        }
        operators.push(expression[i]);
        expectOperand = true;
    } 
    //unrecognized symbols
    else
      cout << "Error: Unrecognized symbol" << endl;
  } 
  //remaining operators
  while (!operators.isEmpty())
  {
    double val2 = numbers.getTop();
    numbers.pop();
    double val1 = numbers.getTop();
    numbers.pop();
    char op = operators.getTop();
    operators.pop();
    numbers.push(solveOperation(val1, val2, op));
  }
  return numbers.getTop();
}
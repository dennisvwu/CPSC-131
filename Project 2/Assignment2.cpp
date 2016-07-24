//--------------------------------------------------------------------------------
//			Name :		Dennis Wu and Barry Ibarra
//			Project:	Programming Assignment #2
//			Due:		April 24, 2015
//			Course:		CPSC131
//			Professor:	Dr Abhishek Verma
//
// This program will compute the solution to a postfix expression.
//
// Core code provided by Professor
//--------------------------------------------------------------------------------
#include <iostream>
#include <string>
using namespace std;

void solvePostfix(string postfixExp); //computes the value of arithmetic
									   //expression given in postfix format
/************************************************************
 * Stack to store operands of postfix expression            *
 ************************************************************/
class OperandStack
{
private:
	double * s;  //pointer to 1D dynamic array for storing stack elements
	int capacity,  //stack capacity
		t;  //index of the top element on stack
	void growStack(int newCapacity);  //increases the stack if it is full
						//must be called from the push function if the stack is full
public:
	OperandStack(){ capacity = 0; s = NULL; t = -1; };
	OperandStack(int capacity);
	~OperandStack();
	int size() const;  //return the number of elements in the stack
	bool isFull() const;
	bool isEmpty() const;
	double top() const;  //returns the element at the top of the stack
				 //without removing it from the stack
	void push(double x);
	void pop();
};

 /************************************************************
 * OperandStack is a constructor that allocates a dynamic   *
 * array based on the capacity given                        *
 * Inputs:                                                  *
 *      capacity, stack capacity                            *
 * Return:                                                  *
 *      nothing                                             *
 ************************************************************/
 OperandStack::OperandStack(int capacity)
 {
	 s = new double[capacity];
	 this->capacity = capacity;
	 t = -1;
 }

 /************************************************************
 * ~OperandStack is a destructor that deletes array if      *
 * dynamically allocated                                    *
 * Inputs:                                                  *
 *      none                                                *
 * Return:                                                  *
 *      nothing                                             *
 ************************************************************/
 OperandStack::~OperandStack()
 { delete[] s; }

  /***********************************************************
 * size returns the number of elements in the stack         *
 * Inputs:                                                  *
 *	    none                                                *
 * Return:                                                  *
 *      integer, number of elements                         *
 ***********************************************************/
 int OperandStack::size() const
 { return (t+1); }
 
 /***********************************************************
 * isFull checks if the stack is full                       *
 * Inputs:                                                  *
 *	    none                                                *
 * Return:                                                  *
 *      boolean, true or false                              *
 ***********************************************************/
 bool OperandStack::isFull() const
 { return ((capacity-1) == t); }
 
  /***********************************************************
 * isEmpty checks if the stack is empty                     *
 * Inputs:                                                  *
 *	    none                                                *
 * Return:                                                  *
 *      boolean, true or false                              *
 ***********************************************************/
 bool OperandStack::isEmpty() const
 { return (t == -1); }

  /***********************************************************
 * top returns the element at the top of the stack          *
 * Inputs:                                                  *
 *	    none                                                *
 * Return:                                                  *
 *      double, value of the top item                       *
 ***********************************************************/
 double OperandStack::top() const
 { 
	 if (!isEmpty())
		 return s[t];
 }
 
/************************************************************
* growStack increases the stack capacity if it is full     *
* Inputs:                                                  *
*      newCapacity, new capacity for stack                 *
* Return:                                                  *
*      nothing                                             *
************************************************************/
void OperandStack::growStack(int newCapacity)
{
	double *copyStack = new double[newCapacity];

	for (int i = 0; i < capacity; i++)
		copyStack[i] = s[i];

	capacity = newCapacity;
	delete[] s;
	s = copyStack;
}

/************************************************************
* push will put the element to the front of the stack      *
* Inputs:                                                  *
*      x, element to be pushed into stack                 *
* Return:                                                  *
*      nothing                                             *
************************************************************/
void OperandStack::push(double x)
{
	if (isFull())
		growStack(capacity+5); // increase capacity

	t++;
	s[t] = x;
}

/************************************************************
* pop will remove an element from the stack                *
* Inputs:                                                  *
*      none                                                *
* Return:                                                  *
*      nothing                                             *
************************************************************/
void OperandStack::pop()
{
	if (!isEmpty())
		t--;
}

int main()
{
	string expression;

	bool retry = true;
	char answer;
	
	while (retry)
	{
	  cout << "Enter a postfix expression: ";
	  getline(cin,expression);

	  cout << "Result: ";
	  solvePostfix(expression);
	  
	  cout << "\nDo you want to run again? (y/n)";
	  cin >> answer;
	  
	  if (answer == 'y' || answer == 'Y')
	    retry = true;
	  if (answer == 'n' || answer == 'N')
	    retry = false;
	    
	  cout << endl;
	}

  //cout << "Enter a postfix expression: 8 2 3 + * 4 /" << endl;
  //cout << "Result: ";
  //solvePostfix("8 2 3 + * 4 /");
  //cout << endl;

  //cout << "Enter a postfix expression: 8 2 / 3 4 * +" << endl;
  //cout << "Result: ";
  //solvePostfix("8 2 / 3 4 * +");
  //cout << endl;
 
  //cout << "Enter a postfix expression: 8 5 + 9 7 - /" << endl;
  //cout << "Result: ";
  //solvePostfix("8 5 + 9 7 - /");
  //cout << endl;

  //cout << "Enter a postfix expression: 8 2 * 3 4 +" << endl;
  //cout << "Result: ";
  //solvePostfix("8 2 * 3 4 +");
  //cout << endl;

  //cout << "Enter a postfix expression: 8 2 * + 3 /" << endl;
  //cout << "Result: ";
  //solvePostfix("8 2 * + 3 /");
  //cout << endl;

  system("pause");
  return 0;
}

/************************************************************
* isValid will check if the postfix expression is valid    *
* Inputs:                                                  *
*      solvePostfix, postfix string                        *
* Return:                                                  *
*      True if expression valid, False if invalid          *
************************************************************/
bool isValid(string postfixExp)
{
	int numCount = 0;
	int opCount = 0;
	int length = postfixExp.length();

	if (length >= 2) // check if first is an operator
	{
		if (postfixExp[0] == '+' || postfixExp[0] == '-' ||
			postfixExp[0] == '*' || postfixExp[0] == '/' )
		{ return false; }
	}
		
	for (int i = 0; i < length; ++i) // loop thru length of string
	{
		if (postfixExp[i] == '0' || postfixExp[i] == '1' ||
			postfixExp[i] == '2' || postfixExp[i] == '3' ||
			postfixExp[i] == '4' || postfixExp[i] == '5' ||
			postfixExp[i] == '6' || postfixExp[i] == '7' ||
			postfixExp[i] == '8' || postfixExp[i] == '9')
		{ ++numCount; } // increment number counter

		if (postfixExp[i] == '+' || postfixExp[i] == '-' ||
			postfixExp[i] == '*' || postfixExp[i] == '/')
		{ ++opCount; } // increment operation counter
	}
	return (numCount == (opCount+1));
}

/************************************************************
* solvePostfix solves the postfix expression                *
* Inputs:                                                  *
*      solvePostfix, postfix string                        *
* Return:                                                  *
*      nothing                                             *
************************************************************/
void solvePostfix(string postfixExp)
{
	OperandStack calculate;
	calculate = OperandStack();

	int length = postfixExp.length();
	
	double var1 = 0;
	double var2 = 0;
  
	if (isValid(postfixExp))
	{
		for (int i = 0; i < length; ++i)
		{
			if (postfixExp[i] == '0')
				calculate.push(0);
		    if (postfixExp[i] == '1')
			    calculate.push(1);
		    if (postfixExp[i] == '2')
				calculate.push(2);
		    if (postfixExp[i] == '3')
			    calculate.push(3);
		    if (postfixExp[i] == '4')
			    calculate.push(4);
		    if (postfixExp[i] == '5')
			    calculate.push(5);
		    if (postfixExp[i] == '6')
			    calculate.push(6);
		    if (postfixExp[i] == '7')
			    calculate.push(7);
		    if (postfixExp[i] == '8')
		  	    calculate.push(8);
		    if (postfixExp[i] == '9')
			    calculate.push(9);

			if (postfixExp[i] == '+') // addition
			{
				var1 = calculate.top(); 
				calculate.pop();
				var2 = calculate.top(); 
				calculate.pop();
				calculate.push(var1 + var2); 
			}

			if (postfixExp[i] == '-') // subtraction
			{
				var1 = calculate.top(); 
				calculate.pop();
				var2 = calculate.top(); 
				calculate.pop();
				calculate.push(var2 - var1); 
			}

			if (postfixExp[i] == '*') // multiplication
			{
				var1 = calculate.top(); 
				calculate.pop();
				var2 = calculate.top(); 
				calculate.pop();
				calculate.push(var1 * var2); 
			}

			if (postfixExp[i] == '/') // division
			{
				var1 = calculate.top(); 
				calculate.pop();
				var2 = calculate.top(); 
				calculate.pop();
				calculate.push(var2 / var1); 
			}
	  }
	  cout << calculate.top() << endl; // result
  }
  else
	  cout << "error - malformed expression" << endl;
}


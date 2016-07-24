
//--------------------------------------------------------------------------------
//			Name :		Dennis Wu and Barry Ibarra
//			Project:	Programming Assignment #3
//			Due:		May 5, 2015
//			Course:		CPSC131
//			Professor:	Dr Abhishek Verma
//
// This program sort a to-do list by priority.
//
// Core code provided by Professor
//--------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/************************************************************
* PriorityQueue class to store the task list               *
************************************************************/
class PriorityQueue
{
private:
	/************************************************************
	* Task node class                                          *
	************************************************************/
	class NodeType
	{
	public:
		string task;	//name of the task
		int priority;		// priority of the task
		NodeType * next;  //points to the next task on the queue

		NodeType(string task = "", int priority = -1,
			NodeType * next = NULL)  //default constructor
		{
			this->task = task;  this->priority = priority;
			this->next = next;
		}
	};

public:
	PriorityQueue()
	{  //default constructor: creates an empty queue
		head = NULL; taskCount = 0;
	}
	~PriorityQueue();  //destructor: delete all tasks from the queue

	bool isEmpty() const;  //checks for the queue being empty

	int size() const;  //returns the number of tasks in the queue

	void insert(string taskName, int priority);
	//creates a task and inserts it in order of priority

	void min() const; //prints the task and its priority (the one with the 
	//highest priority)

	void removeMin();  //removes the highest priority task 
	//from the queue

	void inputList();

private:
	NodeType *head;  //head pointer to the list
	int taskCount;  //count of the number of tasks on the list

	void goNext(NodeType * & curr) const; //moves the pointer to point to
	//the next task
};

/************************************************************
* ~PriorityQueue is a destructor that deletes all task     *
* from the queue                                           *
* Inputs:                                                  *
*      none                                                *
* Return:                                                  *
*      nothing                                             *
************************************************************/
PriorityQueue::~PriorityQueue()
{
	if (isEmpty() == false)
	{	
		NodeType * current = head;

		while (current != NULL)
		{
			NodeType * nodeToDelete = current;
			goNext(current);
			delete nodeToDelete;
		}
	
		head = NULL;
		taskCount = 0;
	}
}

/************************************************************
* isEmpty checks for the queue being empty                  *
* Inputs:                                                   *
*      nothing                                              *
* Return:                                                   *
*      True or False                                        *
************************************************************/
bool PriorityQueue::isEmpty() const
{ return (head == NULL); }

/************************************************************
* size returns the number of tasks in the queue             *
* Inputs:                                                   *
*      nothing                                              *
* Return:                                                   *
*      integer, number of tasks                             *
************************************************************/
int PriorityQueue::size() const
{ return taskCount; }

/************************************************************
* insert creates a task and inserts it in order of priority *
* Inputs:                                                   *
*      taskName; name of task                               *
*	   priority; priority number                            *
* Return:                                                   *
*      nothing                                              *
************************************************************/
void PriorityQueue::insert(string taskName, int priority)
{
	NodeType *newnode = new NodeType(taskName, priority);

	newnode->task = taskName;
	newnode->priority = priority;
	newnode->next = NULL;

	NodeType * current = head;
	NodeType * previous = head;

	// check for empty
	if (isEmpty())
	{ head = newnode; }
	else
	{
		if (priority < current->priority)
		{
			head = newnode;
			newnode->next = current;
		}
		else
		{
			int counter = 0;
			while (priority >= current->priority)
			{
				counter++;
				previous = current;

				if (counter == taskCount) // prevent error
					break;

				goNext(current);
			}
			previous->next = newnode;
			newnode->next = current;
		}
	}
	taskCount++;
}

/************************************************************
* min prints the task and its priority                      *
* Inputs:                                                   *
*      nothing                                              *
* Return:                                                   *
*      nothing                                              *
************************************************************/
void PriorityQueue::min() const
{cout << head->priority << " " << head->task << endl; }

/************************************************************
* min removes the highest priority task from the queue      *
* Inputs:                                                   *
*      nothing                                              *
* Return:                                                   *
*      nothing                                              *
************************************************************/
void PriorityQueue::removeMin()
{
	NodeType * current = head;

	if (isEmpty() == false)
	{
		if (taskCount == 1)
		{
			delete head;
			head = NULL;
		}
		else
		{
			head = head->next;
			delete current;
		}
		taskCount--;
	}
}

/************************************************************
* goNext moves the pointer to the next task                 *
* Inputs:                                                   *
*      nothing                                              *
* Return:                                                   *
*      nothing                                              *
************************************************************/
void PriorityQueue::goNext(NodeType * & curr) const
{ curr = curr->next; }

int main()
{
	PriorityQueue test;

	int priority;
	string task;
	
	//===========================
	// Open text file
	//===========================
	fstream myfile ("input.txt");
	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			myfile >> priority;
			getline(myfile, task);
			test.insert(task, priority);
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	//===========================
	// Output
	//===========================
	cout << "Removing all tasks in order of priority and printing.\n";

	while (!test.isEmpty())
	{
		test.min();
		test.removeMin();
	}

	cout << endl;
	system("pause");
	return 0;
}
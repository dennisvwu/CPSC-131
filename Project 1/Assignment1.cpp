//--------------------------------------------------------------------------------
//			Name :		Dennis Wu and Barry Ibarra
//			Project:	Programming Assignment #1
//			Due:		March 24, 2015
//			Course:		CPSC131
//			Professor:	Dr Abhishek Verma
//
// This program will maintain a list of grocery items that a user would like to
// shop. It displays the name and quantity of desired grocery items on a list.
// The desired quantity of items can be updated.
//
// Core code provided by Professor
//--------------------------------------------------------------------------------
#include <iostream>
#include <string>
using namespace std;

/************************************************************
 * Grocery item class                                       *
 ************************************************************/
class ItemType
{
public:
	string name;	//name of the item
	double qty;		// quantity of the item
	ItemType * next,  //points to the next item on the list
			 * prev;  //points to the previous item on the list
			 
	ItemType(string name = NULL, double qty = 0,
				ItemType * next = NULL,
				ItemType * prev = NULL)  //default constructor
	{
		this->name = name;  this->qty = qty;
		this->next = next;  this->prev = prev;
	}
};

/************************************************************
 * Grocery List class implemented as doubly linked list     *
 ************************************************************/
class GroceryList
{
private:
	ItemType *head, *tail;  //head and tail pointers to the list
	int itemCount;  //count of the number of items on the list
	
	void goNext(ItemType * & curr) const;
	void goPrevious(ItemType * & curr) const;  //moves the pointer to point to
												//the previous item

public:
	GroceryList()
	{  //default constructor: creates an empty list
		head = tail = NULL; itemCount = 0; }
	~GroceryList();  //destructor: delete all items on a list

	bool isEmpty() const;  //checks for the list being empty
	int length() const;  //returns the number of items on the list, which is the
						//value for itemCount
	
	void addToFront(string itemName,
					double quantity);  //creates an item and adds to the front
										//of the list
	void addToBack(string itemName,
					double quantity);  //creates an item and adds to the back
										//of the list
	void add(string itemName, double quantity,
				int position);  //creates an item and adds to the list at  specified
							//position items are numbered from left to right
	
	void printForward() const;  //prints list from front to back
	void printBackward() const;  //prints list back to front
	
	void removeFirst();  //removes the first item from the list
	void removeLast();  //removes the last item from the list
	void remove(int position);  //remove an item at the given position on the list
							//items are numbered from left to right
	
	void peek(int position) const;  // function to print item name and
								//quantity at a specified position
	bool lookup(string itemName) const;  // function to look up an
											//item by name
	
	void deal(GroceryList & secondList);  //removes every other item and puts
											//it into the secondList
};

/************************************************************
 * goNext advances the pointer to point to the next item    *
 * on the list.                                             *
 * Inputs:                                                  *
 *      curr, a pointer passed by reference, points to an   *
 *      item on the grocery list                            *
 * Return:                                                  *
 *      nothing                                             *
 ************************************************************/
void GroceryList::goNext(ItemType * & curr) const
{ curr = curr->next; }

/************************************************************
 * goPrevious advances the pointer to point to the previous *
 *item on the list.                                         *
 * Inputs:                                                  *
 *      curr, a pointer passed by reference, points to an   *
 *      item on the grocery list                            *
 * Return:                                                  *
 *      nothing                                             *
 ************************************************************/
void GroceryList::goPrevious(ItemType * & curr) const
{ curr = curr->prev; }

/************************************************************
 * Destructor deletes all items on the list                 *
 * Inputs:                                                  *
 *      none                                                *
 * Return:                                                  *
 *      nothing                                             *
 ************************************************************/
GroceryList::~GroceryList()
{
	ItemType * current = head;

	while (current != NULL)
	{
		ItemType * itemToDelete = current;
		goNext(current);
		delete itemToDelete;
	}

	current = head = tail = NULL;
	itemCount = 0;
}

/************************************************************
 * isEmpty checks for the list being empty, returns true if *
 * there are no items on the list or false otherwise        *
 * Inputs:                                                  *
 *      none                                                *
 * Return:                                                  *
 *      boolean                                             *
 ************************************************************/
 bool GroceryList::isEmpty() const
{ return head==NULL; }

/************************************************************
 * length returns the number of items on the list.          *
 * Inputs:                                                  *
 *      none                                                *
 * Return:                                                  *
 *      integer                                             *
 ************************************************************/
 int GroceryList::length() const
{ return itemCount; }

/************************************************************
 * addToFront adds a new item with name and quantity,       *
 * and add it to the front of the list                      *
 * Inputs:                                                  *
 *     itemName, name of the new item                       *
 *     quantity, number of items                            *
 * Return:                                                  *
 *      nothing                                             *
 ************************************************************/
void GroceryList::addToFront(string itemName, double quantity)
{
	ItemType * item = new ItemType(itemName, quantity);
	item->name = itemName;
	item->qty = quantity;
	
	if (isEmpty())
	{ tail = item; }
	else
	{
	  ItemType * current = head;
	  item->next = current;
	  current->prev = item;
	}
	
	head = item;
	itemCount++;
}

/************************************************************
 * addToBack adds a new item with name and quantity,        *
 * and add it to the back of the list                       *
 * Inputs:                                                  *
 *     itemName, name of the new item                       *
 *     quantity, number of items                            *
 * Return:                                                  *
 *      nothing                                             *
 ************************************************************/
void GroceryList::addToBack(string itemName, double quantity)
{
	ItemType * item = new ItemType(itemName, quantity);
	item->name = itemName;
	item->qty = quantity;
	
	if (isEmpty())
	{ head = item;}
	else
	{
	  ItemType * current = tail;
	  current->next = item;
	  item->prev = current;
	}
	
	tail = item;
	itemCount++;
}

/************************************************************
 * add adds a new item with name and quantity to the        *
 * specified position to the list. A position greater or    *
 * equal to the list length means that the item is placed   *
 * at the end of the list                                   *
 * Inputs:                                                  *
 *     itemName, name of the new item                       *
 *     quantity, number of items							*
 *	   position, position of new item			     		*
 * Return:                                                  *
 *      nothing                                             *
 ************************************************************/
void GroceryList::add(string itemName, double quantity, int position)
{
	ItemType * item = new ItemType(itemName, quantity);
	item->name = itemName;
	item->qty = quantity;
	
	if (isEmpty() || position == 0)
	{ addToFront(itemName, quantity); }

	else if (position >= itemCount)
	{ addToBack(itemName, quantity); }

	else
	{
		ItemType * current = head;

		for (int i = 1; i <= position; ++i)
		{ goNext(current); }
	  
		item->prev = current->prev;
		item->next = current;
		current->prev->next = item;
		current->prev = item;
	}
	
	itemCount++;
}

/************************************************************
 * printForward will print the list of items on the grocery *
 * list along with their quantities from front to back      *
 * Inputs:                                                  *
 *      none                                                *
 * Return:                                                  *
 *      nothing                                             *
 ************************************************************/
 void GroceryList::printForward() const
{
	ItemType * current = head;
	int count = 1;
	
	cout << "------ Grocery List (item:quantity) ------" << endl;
	if(isEmpty()) cout << "You do not have any item.";
	
	while(current != NULL)
	{
		cout << count << ") " << current->name <<": " << current->qty << endl;
		goNext(current);
		count++;
	}

	cout << endl;
}

/*************************************************************
 * printBackward will print the list of items on the grocery *
 * list along with their quantities from back to front       *
 * Inputs:                                                   *
 *      none                                                 *
 * Return:                                                   *
 *      nothing                                              *
 *************************************************************/
 void GroceryList::printBackward() const
{
	ItemType * current = tail;
	int count = itemCount;
	
	cout << "------ Grocery List (item:quantity) ------" << endl;
	if(isEmpty()) cout << "You do not have any item.";

	while(current != NULL && count != 0)
	{
		cout << count << ") " << current->name <<": " << current->qty << endl;
		goPrevious(current);
		count--;
	}

	cout << endl;
}

 /*************************************************************
 * removeFirst will remove the first item on the grocery list *
 * Inputs:                                                    *
 *      none                                                  *
 * Return:                                                    *
 *      nothing                                               *
 *************************************************************/
 void GroceryList::removeFirst()
{
	if (isEmpty()) cout << "You do not have any items to remove.";
	else
	{
		ItemType * current = head;

		if (itemCount == 1)
		{ head = tail = NULL; }
		else
		{
			current->next->prev = NULL;
			goNext(current);
			head = current;
			
			if (itemCount == 2)
			{ tail = current; }

			goPrevious(current);
		}

		delete current;
		current = NULL;

		itemCount--;
	}
}

 /*************************************************************
 * removeLast will remove the last item on the grocery list   *
 * Inputs:                                                    *
 *      none                                                  *
 * Return:                                                    *
 *      nothing                                               *
 *************************************************************/
 void GroceryList::removeLast()
{
	if (isEmpty()) cout << "You do not have any items to remove.";
	else
	{
		ItemType * current = tail;

		if (itemCount == 1)
		{ head = tail = NULL; }
		else
		{
			current->prev->next = NULL;
			goPrevious(current);
			tail = current;
		
			if (itemCount == 2)
			{ head = current; }

			goNext(current);
		}

		delete current;
		current = NULL;
	
		itemCount--;
	}
}

/************************************************************
 * remove removes an item at the given position on the list *
 * Inputs:                                                  *
 *	   position, position of item to remove					*
 * Return:                                                  *
 *      nothing                                             *
 ************************************************************/
 void GroceryList::remove(int position)
 {
   int lastItem = (itemCount-1);
   
	 if (isEmpty() == false && position < itemCount)
	 {
		ItemType * current = head;

		if (position == 0 && itemCount == 1)
		{ head = tail = NULL; }
		else
		{
			if (position == 0)
			{ removeFirst(); }

			else if (position == lastItem)			
			{ removeLast(); }

			else
			{			
				for (int i = 1; i <= position; ++i)			
				{ goNext(current); }
		
				current->prev->next = current->next;
			}
		}

		delete current;
		current = NULL;

		itemCount--;
	 }

 }

 /***********************************************************
 * peek prints item name & quantity at a specified position *
 * Inputs:                                                  *
 *	   position, position of item to print			        *
 * Return:                                                  *
 *      nothing                                             *
 ***********************************************************/
 void GroceryList::peek(int position) const
 {
	 if (position < itemCount && position >= 0)
	 {		 
		 ItemType * current = head;
	
		 for (int i = 1; i <= position; ++i)		
		 { goNext(current); }

		 cout << current->name << ": " << current->qty;
		 cout << endl;
	 }
 }

 /***********************************************************
 * lookup looks up an item by name						    *
 * Inputs:                                                  *
 *	   itemName, name of item for search			        *
 * Return:                                                  *
 *      boolean                                             *
 ***********************************************************/
 bool GroceryList::lookup(string itemName) const
 {
	 ItemType * current = head;

	 while (current != NULL)
	 {
		 if (current->name == itemName)
		 { return true; }
			 
		 goNext(current);
	 }

	 return false;
 }

 /***********************************************************
 * deal removes every other item from original list and     *
 * adds it to the second list.								*
 * Inputs:                                                  *
 *	   GroceryList, original grocery list (Betty)			*
 *     secondList, second grocery list (Nicholas)			*
 * Return:                                                  *
 *      nothing                                             *
 ***********************************************************/
 void GroceryList::deal(GroceryList & secondList)
 {
	 ItemType * current = head;
	 int numSplit = itemCount/2;
	 int next = 1;

	if (itemCount != 1)
	{
		if (itemCount == 2)
		{		 
			goNext(current);
			secondList.addToFront(current->name, current->qty);
			removeLast();
		} 
		else 
		{		
			for (int i = 0; i < (numSplit); ++i)
			{
				goNext(current);
				secondList.addToBack(current->name, current->qty);
				goNext(current);

				remove(i+next);
			}
		}
	}
 }
	
int main()
{
    GroceryList list;

	list.printForward();

	// Testing addToFront function
	cout << "\nAdding an item via addToFront..." << endl;
	list.addToFront("Avocado", 5);
	list.printForward();

	// Testing addToBack function
	cout << "Adding an item via addToBack..." << endl;
	list.addToBack("Lime", 2);
	list.printForward();

	// Testing add function
	cout << "Adding an item via add at position 1..." << endl;
	list.add("Milk", 1, 1);
	list.printForward();

	// Testing printBackward function
	cout << "Print the list backwards via printBackward..." << endl;
	list.printBackward();

	// Populating grocery list
	list.addToBack("Apples", 6);
	list.addToBack("Oatmeal", 3);
	list.addToBack("Pepper", 1);
	list.addToBack("Eggs", 12);
	list.addToBack("Salsa", 1);
	list.addToBack("Quinoa", 1);
	list.printForward();

	// Testing removeFirst function
	cout << "Removing an item via removeFirst..." << endl;
	list.removeFirst();
	list.printForward();

	// Testing removeLast function
	cout << "Removing an item via removeLast..." << endl;
	list.removeLast();
	list.printForward();

	// Testing remove function
	cout << "Removing an item via remove from position 4..." << endl;
	list.remove(4);
	list.printForward();

	// Testing peek function
	list.printForward();
	cout << "Peek item at position 3..." << endl;
	list.peek(3);
	cout << endl;

	// Testing lookup function
	cout << "Looking up Apples..." << endl;
	if (list.lookup("Apples"))
		cout << "Apples found" << endl;
	else
		cout << "Apples NOT found" << endl;

	cout << "\nLooking up Hummus..." << endl;
	if (list.lookup("Hummus"))
		cout << "Hummus found" << endl;
	else
		cout << "Hummus not found" << endl;

	cout << endl;

	// Testing deal function
	GroceryList secondList;

	list.addToBack("Avocado", 5);
	list.addToBack("Pepper", 1);
	list.addToBack("Quinoa", 1);

	cout << "Printing Betty's list..." << endl;
	list.printForward();

	cout << "Print Nicholas's list..." << endl;
	secondList.printForward();
	cout << endl;

	cout << "Calling deal..." << endl;
	list.deal(secondList);

	cout << "Print Betty's list..." << endl;
	list.printForward();

	cout << "Print Nicholas's list..." << endl;
	secondList.printForward();

    // Terminate program
	cout << endl;
	system("pause");
	return 0;
}
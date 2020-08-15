// Samprayash Dahal
// CPSC 301-03
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "person.cpp"
#include "book.cpp"

using namespace std;

void printMenu() {
    cout << "----------Library Book Rental System----------" << endl;
    cout << "1.  Book checkout" << endl;
    cout << "2.  Book return" << endl;
    cout << "3.  View all available books" << endl;
    cout << "4.  View all outstanding rentals" << endl;
    cout << "5.  View outstanding rentals for a cardholder" << endl;
    cout << "6.  Open new library card" << endl;
    cout << "7.  Close library card" << endl;
    cout << "8.  Exit system" << endl;
    cout << "Please enter a choice: ";
}

void booksCheckout(vector<Book *> &myBooks, vector<Person *> &myCardholders)
{ int ind, cardNum, bookNum;
  bool book = false;
  bool card = false;

  cout << "Please enter the card ID: ";
  cin >> cardNum;
  for(int i = 0; i < myCardholders.size(); i++)
  {
	  if(myCardholders[i]->getId()== cardNum
			  && myCardholders[i]->isActive() == true)
	  {		  
		cout << "Cardholder: "
		       	<< myCardholders[i]->fullName() << endl;
		card = true;
		ind = i;
	  }
  }
  if(card == false)
  {
	  cout << "Card ID not found." << endl;
  }

  cout << "Please enter the book ID: ";
  cin >> bookNum;
  for(int i = 0; i < myBooks.size(); i++)
  {
	  if(myBooks[i]-> getId() == bookNum)
	  {
		  cout << "Title: " <<
		  myBooks[i]->getTitle() << endl;
		  book = true;
		  if(myBooks[i]->getPersonPtr() != nullptr)
		  {
			  cout << "Book not available for checkout" << endl;
			  return;
		  }
		  myBooks[i]->setPersonPtr(myCardholders[ind]);
	  }
  }
  if(book == false)
  {
	  cout << "Book ID not found." << endl;
  }
	
}
void bookAvailable(vector<Book *> &myBooks)
{ bool empty = true;
	for(int i = 0; i < myBooks.size(); i++)
	{
		if(myBooks[i]->getPersonPtr() == nullptr)
		{ cout << "Book ID: " << myBooks[i]->getId() << endl;
		  cout << "Title: " << myBooks[i]->getTitle() << endl;
		  cout << "Author: " << myBooks[i]->getAuthor() << endl;
		  cout << "Category: " << myBooks[i]->getCategory() << endl;
		  cout << endl;
		  empty = false;
			
		}	
	}
	if(empty == true)
	{
		cout << "No available books" << endl;
	}

}

void bookRentals(vector<Book *> &myBooks)
{
	bool found = false;
	for(int i = 0; i < myBooks.size(); i++)
	{
		if(myBooks[i]->getPersonPtr() != nullptr)
		{
		  cout << "Book ID: " << myBooks[i]->getId() << endl;
                  cout << "Title: " << myBooks[i]->getTitle() << endl;
                  cout << "Author: " << myBooks[i]->getAuthor() << endl;
    cout << "Cardholder: " << myBooks[i]->getPersonPtr()->fullName() << endl;
    cout << "Card ID: " << myBooks[i]->getPersonPtr()->getId();
    cout << endl;
    found = true;
		}
	}
	if(found == false)
	{
		cout << "No outstanding Rental" << endl;
	}
}

void Rentals(vector<Book *> &myBooks, vector<Person *> &myCardholders)
{ int cardID;
  cout << "Please enter Card ID: ";
  cin >> cardID;
  for(int i =0; i < myCardholders.size(); i++)
  {
  if(myCardholders[i]->getId() == cardID)
  {
	  cout << "Cardholder: " << myCardholders[i]->fullName() << endl;
	  cout << endl;
  }
  }
  for(int i = 0; i < myBooks.size(); i++)
  {
	  if(myBooks[i]->getPersonPtr() != nullptr)
	  {	if(myBooks[i]->getPersonPtr()->getId() == cardID)
		  {
		  cout << "Book ID: " << myBooks[i]->getId() << endl;
                  cout << "Title: " << myBooks[i]->getTitle() << endl;
                  cout << "Author: " << myBooks[i]->getAuthor() << endl;
                  cout << "Category: " << myBooks[i]->getCategory() << endl;
                  cout << endl;


		  }

	  }
  }

}
                              
void returnBook(vector<Book *> &myBooks)
{bool found = false;
 int bookID;
 cout << "Please enter the book id to return book: ";
 cin >> bookID;
 for(int i = 0; i < myBooks.size(); i++)
 {
	 if(myBooks[i]->getId() == bookID)
	{
		cout << "Title: " << myBooks[i]->getTitle() << endl;
		found = true;
		myBooks[i]->setPersonPtr(nullptr);
		cout << "Return Completed." << endl;
	}
 }
 if(found == false)
 {
	 cout << "Book ID was not found." << endl;
	 return;
 }

}
void open(vector<Person *> &myCardholders)
{
	string firstName, lastName;
	int id;
	bool exists = false;
	cout << "Please enter the first name: ";
	cin >> firstName;
	cout << "Please enter the last name: ";
	cin >> lastName;
	string name = firstName + " " + lastName;
	for(int i = 0; i < myCardholders.size(); i++)
	{
		if(name == myCardholders[i]->fullName())
		{
			myCardholders[i]->setActive(true);
			cout << "Card ID " << myCardholders[i]->getId() 
				<< " active " << endl;
			cout << "Cardholder: "
			       	<< myCardholders[i]->fullName() << endl;
			exists = true;
		}
	}
	if(exists = false)
	{
		id = myCardholders[myCardholders.size() - 1]->getId()+1;
	myCardholders.push_back(new Person(id, true, firstName, lastName));
	cout << "Card ID" << myCardholders[myCardholders.size()-1]->getId()
		<< " active" << endl;
	cout << "Cardholder: "
	       	<< myCardholders[myCardholders.size()-1]->fullName() << endl;
	}


}

void close(vector<Book *> &myBooks, vector<Person *> & myCardholders)
{
 bool found = false;
 int ID;
 char input;
 cout << "Please enter the card ID: ";
 cin >> ID;
 for(int i = 0; i < myCardholders.size(); i++)
 {
	 if(ID == myCardholders[i]->getId())
	 {
	  cout << "Cardholders: " << myCardholders[i]->fullName() << endl;
	  if(myCardholders[i]->isActive() == false)
	  {
		  cout << "Card id is already deactivated." << endl;
		  return;
	  }
	  cout << "Are you sure you want to deactivate card? (y/n)";
	  cin >> input;
	  input = tolower(input);
	  if(input == 'y')
	  {
		  for(int k =0; k < myBooks.size(); k++)
		  {
			if(myBooks[k]->getPersonPtr() == myBooks[i]->getPersonPtr())
			{
				myBooks[k]->setPersonPtr(nullptr);
			}	
		  }
		  myCardholders[i]->setActive(false);
		  cout << "Card ID deactivated" << endl;
	  }
	else
	{	cout << " " << endl;
		return;
	}

	 }
 }


}



int main()
{
    vector<Book *> books;
    vector<Person *> cardholders;
    //read book file
    ifstream bFile;
    bFile.open("books.txt");
    int bookID;
    int choice;
    string lines, title, author, category, space;
    while(!bFile.eof())
    {
	    bFile >> bookID;
	    getline(bFile, lines);
	    getline(bFile, title);
	    getline(bFile, author);
	    getline(bFile, category);
	    getline(bFile, space);
	    books.push_back(new Book(bookID, title, author, category));
    }
    bFile.close();
	
    // read person file
   ifstream pFile;
   pFile.open("persons.txt");
   int cardID;
   string status, firstName, lastName, eline;
   bool active;
   while(pFile >> cardID)
   {
	   pFile >> status;
	   pFile >> firstName;
	   pFile >> lastName;
	   getline(pFile, eline);
	   if(status != "Active")
	   {
		   active = false;
	   }
	   else
	   {
		   active = true;
	   }
	   cardholders.push_back(new Person(cardID, active, firstName, lastName));

   }
   pFile.close();


    do
    {
        // If you use cin anywhere, don't forget that you have to handle the <ENTER> key that 
        // the user pressed when entering a menu option. This is still in the input stream.
        printMenu();
        cin >> choice;
        switch(choice)
        {
            case 1:
                // Book checkout
		booksCheckout(books, cardholders);
                break;
	    case 2: 
		//return books
		returnBook(books);
                break;

            case 3:
		//view available books
		bookAvailable(books);
	        break;

            case 4:
		// book rental
             bookRentals(books);
                break;

            case 5:
		Rentals(books, cardholders);

	
                break;

            case 6:
                // Open new library card
		open(cardholders);
                break;

            case 7:
                // Close library card
               close(books, cardholders);
	       	break;
                
            case 8:
                // Must update records in files here before exiting the program
		{     
		ofstream rentals;
	rentals.open("rentals.txt");
		for(int i =0; i < books.size(); i++)
		{
			if(books[i]->getPersonPtr() != nullptr)
			{
				rentals << books[i]->getId() << " "
				       << books[i]->getPersonPtr()->getId()
			       << endl;	       
			}
		}
		rentals.close();
		ofstream persons;
		persons.open("persons.txt");
		for(int i =0; i < cardholders.size(); i++)
		{
			if(cardholders[i]->isActive() == true)
			{
				persons << cardholders[i]->getId()
					<< " Active " << cardholders[i]->fullName()<< endl;
			}
			else
			{
				persons<< cardholders[i]->getId() << "Inactive " << cardholders[i]->fullName() << endl;
			}
		}
		persons.close();
	}
	       	break;


            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 8);
      return 0;
}

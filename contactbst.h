#ifndef ContactBST_H
#define ContactBST_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "myvector.h"
#include "contact.h"

using namespace std;

//Node Class: The idea is each node has contactVectors which store duplicate Contacts, under the same 'key'. This way, we cannot have duplicate nodes, but one node containing duplicates using a vector.
class Node
{
    private:
        string key;                         //Each node has a key: (Ex: 'John Smith')
        MyVector<Contact*> contactVector;   //Each node has a Vector to store duplicate Contacts under the same key
        Node* left;                         //Left Child of Node
        Node* right;                        //Right Child of Node
        Node* parent;                       //Parent of Node
    
    public:
        //Constructor: Adds contact data to the end of the contactVector.
        Node(string key, Contact *data): key(key), left(nullptr), right(nullptr), parent(nullptr)
            {contactVector.push_back(data); }
        
        //Getter: Returns the key of the Node.
        string getKey() {return this->key; }
        
        //Getter: Returns the entire contactVector (returns all the contacts inside).
        MyVector<Contact*> getData() {return this->contactVector; }
        
        //Prints all the contacts in the contactVector
        void print()
        {
            cout << contactVector.size() << " record(s) found:" << endl;
            for(int i = 0; i < contactVector.size(); i++)
            {
                Contact *ct = contactVector.at(i);
                cout << " " << i+1 << ". " << ct->fname<<", " << ct->lname<<", " << ct->email << ", " << ct->primaryPhone << ", " << ct->city << ", " << ct->country << ", " << ct->isFav << endl;
            }
        }
        friend class ContactBST;
};

//=============================================================================
class ContactBST
{
    private:
        Node* root;
    private:
        Node* findMin(Node* ptr);                                    //Needed for remove method
    public:
        ContactBST();                                                //Constructor
        ~ContactBST();                                               //Destructor
        Node* getRoot();                                             //Returns the root of the Tree
        void add(Node* ptr, string key, Contact *data);              //Add key into tree/subtree with root ptr
        void update(Node* ptr, string key);                          //Edit the node with key
        void remove(Node* ptr,string key);                           //Delete a node with key from the tree/subtree with root
        Node* searchFor(Node* ptr,string key);                       //Find and returns the node with key
        bool markFav(string key);                                    //Mark a contact as favorite
        bool unmarkFav(string key);                                  //Unmark a contact as favorite
        void printASC(Node* ptr);                                    //Recursive method that prints the data at nodes in an ascending order
        void printDES(Node* ptr);                                    //Recursive method that prints the data at nodes in a descending order
        void printFav(Node* ptr);                                    //Print the favorite data at nodes in an ascending order
        int importCSV(string path);                                  //Load all the contacts from the CSV file to the BST
        int exportCSV(Node* ptr, ofstream &outFile, string path);    //Export all the contacts from the BST to a CSV file in an ascending order
};

#endif

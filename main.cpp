//=================================================================================
// Aditya Pandhare : Data Structures Assignment 2
// Description  : Starter Code for Contact Management System using BST Tree in C++
//=================================================================================
#include <iostream>
#include <cstdlib>
#include <sstream>
#include "myvector.h"
#include "contact.h"
#include "contactbst.h"
using namespace std;

//==========================================================
//Function that displays a list of all the commands:
void listCommands()
{
    cout << "----------------------------------" << endl;
    cout << "import <path>      :Import contacts from a CSV file" << endl
         << "export <path>      :Export contacts to a CSV file" << endl
         << "add                :Add a new contact" << endl
         << "edit <key>         :Update a contact's details" << endl
         << "remove <key>       :Delete a contact" << endl
         << "searchFor <key>    :Search for a contact" << endl
         << "markFav <key>      :Mark as favourite" << endl
         << "unmarkFav <key>    :Unmark as favourite" << endl
         << "printASC           :Print contacts in ascending order" << endl
         << "printDES           :Print contacts in descending order" << endl
         << "printFav           :Print all favourite contacts" << endl
         << "help               :Display the available commands" << endl
         << "exit               :Exit the program" << endl;
}

//==========================================================
//Main Function:
int main()
{
    ContactBST CBST;
    listCommands();
    string user_input;
    string command;
    string parameter;
    string fname, lname, email, phone, city, country, fav;
    bool isfav;
    
     do {
         cout << endl;
         cout << ">";
         getline(cin, user_input);
    
         stringstream sstr(user_input);
         getline(sstr, command, ' '); //Parses userinput into command.
         getline(sstr, parameter); //Parses userinput into another parameter (file path or keys)

        Node* root = CBST.getRoot();
         
        //Conditional statements, if the user types a specific command, it should call the necessary methods. If they don't enter the correct command, then it is invalid. 
        if(command == "import") {
            cout << CBST.importCSV(parameter) << " contact(s) imported." << endl;; }
             
        else if(command == "export") {
            //Creates an ofstream and passes it to the exportCSV() function in order to use for recursion.
            ofstream os(parameter);
            if(os.fail()) {
                cout << "File " << parameter << "could not be created." << endl;
                return -1;
            }
            cout << CBST.exportCSV(root, os, parameter) << " contact(s) exported." << endl;
            
            os.close(); //Close the ofstream file. 
        }
             
        else if(command == "add" or command == "a") {
            //Print statements to ask the user to input the details of the contact they wish to add.
            cout << "Please enter the details of the contact: " << endl;
            cout << "First Name: ";     getline(cin, fname);
            cout << "Last Name: ";      getline(cin, lname);
            cout << "Email: ";          getline(cin, email);
            cout << "Phone#: ";         getline(cin, phone);
            cout << "City: ";           getline(cin, city);
            cout << "Country: ";        getline(cin, country);

            cout << "Do you want to add the contact in your favourite (y/n): ";
            cin >> fav;
            while(fav != "y" and fav != "n") {
                cout << "Invalid Input! Please select either (y/n) to add to favourite contacts: ";
                cin >> fav;
            }

            if(fav == "y") {isfav = 1; }
            else {isfav = 0; }
            
            //Generates the contact and adds it to the BST
            Contact *new_Contact = new Contact(fname, lname, email, phone, city, country, isfav);
            string key = fname + " " + lname;
            CBST.add(root, key, new_Contact);
            cout << "Contact successfully added to the System!" << endl;
        }
             
        else if(command == "edit" or command == "e") {CBST.update(root, parameter); }
             
        else if(command == "remove" or command == "r") {
            if(root == NULL) { cout << "Contact System is empty! Cannot remove any contact!" << endl; }
            else {
                CBST.remove(root, parameter);
                cout << "Contact successfully removed!" << endl; }
        }
             
        else if(command == "searchFor" or command == "s") {CBST.searchFor(root, parameter); }
             
        else if(command == "markFav" or command == "markf") {CBST.markFav(parameter); }
             
        else if(command == "unmarkFav" or command == "unmarkf") {CBST.unmarkFav(parameter); }
            
        else if(command == "printASC" or command == "pa") {CBST.printASC(root);}
             
        else if(command == "printDES" or command == "pd") {CBST.printDES(root);}
             
        else if(command == "printFav" or command == "pf") {CBST.printFav(root);}
             
        else if(command == "help") {listCommands(); }
             
        else if(command == "exit")  {break; }
         
        else
            cout << "Invalid Input!" << endl;
        
        fflush(stdin);
    }
    while(true);
    
    return 0;
}

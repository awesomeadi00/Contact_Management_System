#include "contactbst.h"
#include "contact.h"
#include "myvector.h"

//=============================================================================
//Constructor: Sets root to NULL (empty tree)
ContactBST::ContactBST() {
    root = NULL;
}

//=============================================================================
//Destructor: Clears memory
ContactBST::~ContactBST() {
    delete root;
}

//=============================================================================
//GetRoot: Returns the root of the entire Contact BST
Node* ContactBST::getRoot() {
    return root;
}

//=============================================================================
//Add: Adds Contact 'data' to a particular 'key' into tree/subtree with root ptr (when function is called from main, ptr == root)
void ContactBST::add(Node* ptr, string key, Contact *data) {
    
    //Case 1: When entire BST is empty:
    if(root == NULL) {
        root = new Node(key, data);
    }
    
    //Case 2: When key is less than ptr->key, if the left of ptr is NULL, insert node and push back on vector. Otherwise, recursively call the function towards the left side of the tree.
    else if(key < ptr->key) {
        if(ptr->left == NULL) {
            ptr->left = new Node(key, data);
            ptr->left->parent = ptr;
        }
                
        else {
            add(ptr->left, key, data);
            
        }
    }
    
    //Case 3: When key is greater than ptr->key, if the right of ptr is NULL, insert node and push back on vector. Otherwise, recursively call the function towards the right side of the tree.
    else if(key > ptr->key) {
        if(ptr->right == NULL) {
            ptr->right = new Node(key, data);
            ptr->right->parent = ptr;
        }
        
        else {
            add(ptr->right, key, data);
        }
    }
    
    //Case 4: When the key is the same as the ptr->key, then we push back the Contact data on the contactVector of the node.
    else if(key == ptr->key) {
        ptr->contactVector.push_back(data);
    }
}

//=============================================================================
//Update: This will edit the Contact details of the node with the key.
void ContactBST::update(Node* ptr, string key) {
    
    //Search for the key in the BST and make ptr point to it.
    ptr = searchFor(ptr, key);
    
    //If there is no node, simply return.
    if(ptr == NULL) {
        return;
    }
    
    //Prints out all the records of the key the user wants to update with an input.
    int contact, option;
    cout << endl;
    cout << "Please select the record you want to edit: ";
    cin >> contact;
    while(contact > ptr->contactVector.size() or contact < 0 or contact == 0) {
        cout << "Invalid! Please select the record you want to edit: ";
        cin >> contact;
    }
        
    string edit, input;
        
    do {
        //Asks the user to input which field they wish to edit and what edits they wish to implement.
        cout << "Which field do you want to edit? 1) First Name, 2) Last Name, 3) Email, 4) Phone#, 5) City, or 6) Country: ";
        cin >> option;
        while(option > 6 or option < 0 or option == 0) {
            cout << "Invalid! Please select a valid option! " << endl;
            cout <<  "1) First Name, 2) Last Name, 3) Email, 4) Phone#, 5) City, or 6) Country: ";
            cin >> option;
        }
            
        string fields[6] = {"First Name", "Last Name", "Email", "Phone#", "City", "Country"};
        cout << "Please enter a new " << fields[option-1] << ": ";
        cin >> input;
        
        //If the user inputted a particular field to edit, that field will change.
        //If the field is their First or Last name, naturally the key would change, hence a new node would be created.
        if(option == 1 or option == 2) {
            if(option == 1) {
                ptr->contactVector.at(contact-1)->fname = input;
            }
                
            else
                ptr->contactVector.at(contact-1)->lname = input;
                
            string newKey = ptr->contactVector.at(contact-1)->fname+" "+ptr->contactVector.at(contact-1)->lname;
            Contact *new_data = ptr->contactVector.at(contact-1);
            
            //If the vector is greater than or equal to two, no need to delete the node, simply erase the contact in the Vector. Else remove the node. Then at the end, create a new node with the new Key.
            if(ptr->contactVector.size() >= 2) {
                ptr->contactVector.erase(contact-1);
            }
            else
                remove(ptr, key);
            
            add(root, newKey, new_data);
        }
            
        else if(option == 3) {
            ptr->contactVector.at(contact-1)->email = input;
        }
            
        else if(option == 4) {
            ptr->contactVector.at(contact-1)->primaryPhone = input;
        }
            
        else if(option == 5) {
            ptr->contactVector.at(contact-1)->city = input;
        }
            
        else if(option == 6) {
            ptr->contactVector.at(contact-1)->country = input;
        }
        
        //Asks the user if they wish to edit another field.
        cout << "Do you want to edit another field (y/n): ";
        cin >> edit;
        
        while(edit != "y" and edit != "n") {
            cout << "Invalid Input!, Please select either (y/n) if you wish to edit another field: ";
            cin >> edit;
        }
    }
    while(edit != "n");
        
    cout << "The contact record has successfully been updated!" << endl;
}


//=============================================================================
//Remove: This will delete a node from the tree/subtree that's rooted at ptr (when called in the main, ptr is root)
void ContactBST::remove(Node* ptr, string key) {

    //If the tree is empty (starting from the main root):
    if(root == NULL) {
        cout << "Contact System is empty! Cannot remove any contact!" << endl;
    }
    
    //Traversing the BST to find the key. If they key is to the left, it traverses left. If it's to the right it traverses right, if it doesn't exist, then it will print out an error.
    
    else if(key < ptr->key) {
        remove(ptr->left, key);
    }
        
    else if(key > ptr->key) {
        remove(ptr->right, key);
    }
    
    //If the key is found, then several removal cases will occur:
    else if(key == ptr->key) {
        //Case A: Removing an element in the contactVector which has a size greater than or equal to 2:
        if(ptr->contactVector.size() >= 2) {
            int contact;
            ptr->print();
            cout << "Please select the record you want to delete: ";
            cin >> contact;
            while(contact > ptr->contactVector.size() or contact < 0 or contact == 0) {
                cout << "Invalid! Please select the record you want to delete: ";
                cin >> contact;
            }
            ptr->contactVector.erase(contact-1);
        }
        
        //Case B: Removing an element in the contactVector which has only one element -> erase the element and delete the node from BST.
        else {
            ptr->contactVector.erase(0);
                
            //Case 1: If the node is an external node.
            if(ptr->left == NULL and ptr->right == NULL) { //External nodes have no children
                if(ptr == root) {
                    delete root;
                    root = NULL;
                }
            
                else if(ptr->parent->left == ptr) {
                    ptr->parent->left = NULL;
                    delete ptr;
                }
                        
                else if(ptr->parent->right == ptr) {
                    ptr->parent->right = NULL;
                    delete ptr;
                }
            }
                    
            //Case 2a: If the node is an internal node (left is empty and right is not)
            else if(ptr->left == NULL and ptr->right != NULL) {
                if(ptr == root) {
                    root = ptr->right;
                    delete ptr;
                }
                        
                else if(ptr->parent->left == ptr) {
                    ptr->right->parent = ptr->parent;
                    ptr->parent->left = ptr->right;
                    delete ptr;
                }
                        
                    else if(ptr->parent->right == ptr) {
                        ptr->right->parent = ptr->parent;
                        ptr->parent->right = ptr->right;
                        delete ptr;
                    }
            }
                    
            //Case 2b: If the node is an internal node (left not empty and right is empty)
            else if(ptr->left != NULL and ptr->right == NULL) {
                if(ptr == root) {
                    root = ptr->left;
                    delete ptr;
                }
                        
                else if(ptr->parent->left == ptr) {
                    ptr->left->parent = ptr->parent;
                    ptr->parent->left = ptr->left;
                    delete ptr;
                }
                        
                else if(ptr->parent->right == ptr) {
                    ptr->left->parent = ptr->parent;
                    ptr->parent->right = ptr->left;
                    delete ptr;
                }
            }
                    
            //Case 3: If the node is an internal node, with two children.
            else {
                Node *temp = findMin(ptr->right);
                ptr->key = temp->key;
                remove(temp, temp->key);
            }
        }
    }
}

//=============================================================================
//SearchFor: Find and return the node with the key.
Node* ContactBST::searchFor(Node *ptr, string key)
{
    //Case 1: This is the base case where if ptr == NULL, it means that the key does not exist in the tree.
    if(ptr == NULL) {
        cout << "The key " << key << " is not in the Contact System!" << endl;
        return ptr;
    }
    
    //Case 2: If the key is to the left side of the tree, it recurses by calling the function to the left child of ptr.
    else if(key < ptr->key) {
        return searchFor(ptr->left, key);
    }
    
    //Case 3: If the key is to the right side of the tree, it recurses by calling the function to the right child of ptr.
    else if(key > ptr->key) {
        return searchFor(ptr->right, key);
    }
    
    //Case 4: If the key is at ptr, it means the key is found, hence we can print out the contactVector.
    else if(key == ptr->key) {
        ptr->print();
        return ptr;
    }
    
    else
        throw runtime_error("No Key in the BST!");
}

//=============================================================================
//MarkFav: Mark a contact as favourite.
bool ContactBST::markFav(string key) {
    Node* ptr = searchFor(root, key); //Will search for the node with 'key'.
    
    //If the key doesn't exist then then the function will end with false.
    if(ptr == NULL) {
        return false;
    }
    
    //If the vector size is greater than or equal to 2, it will ask the viewer which contact to mark as favourite.
    int contact;
    if(ptr->contactVector.size() >= 2) {
        cout << "Please select the record you want to mark as favourite: ";
        cin >> contact;
        while(contact > ptr->contactVector.size() or contact < 0 or contact == 0) {
            cout << "Invalid! Please select the record you want to mark as favourite: ";
            cin >> contact;
        }
        
        if(ptr->contactVector.at(contact-1)->isFav == 0) {
            ptr->contactVector.at(contact-1)->isFav = 1;
            cout << ptr->contactVector.at(contact-1)->fname << " " <<  ptr->contactVector.at(contact-1)->lname << " (" <<  ptr->contactVector.at(contact-1)->email << ") has been successfully marked as favourite!" << endl;
        }
    }
    
    //Else if there is only one contact in the vector, it will automatically set the contact to favourite as there is only one.
    else if(ptr->contactVector.size() == 1) {
        if(ptr->contactVector.at(0)->isFav == 0) {
            ptr->contactVector.at(0)->isFav = 1;
            cout << ptr->contactVector.at(0)->fname << " " <<  ptr->contactVector.at(0)->lname << " (" <<  ptr->contactVector.at(0)->email
            << ") has been successfully marked as favourite!" << endl;
        }
        
        else
            cout << "This contact is already marked as favourite!" << endl;
    }
    
    
    
    return true;
}

//=============================================================================
//UnmarkFav: Unmark a contact as favourite.
bool ContactBST::unmarkFav(string key) {
    Node* ptr = searchFor(root, key); //Will search for the node with 'key'.
    
    //If the key doesn't exist then then the function will end with false.
    if(ptr == NULL) {
        return false;
    }
    
    //If the vector size is greater than or equal to 2, it will ask the viewer which contact to unmark as favourite.
    int contact;
    if(ptr->contactVector.size() >= 2) {
        cout << "Please select the record you want to unmark as favourite: ";
        cin >> contact;
        while(contact > ptr->contactVector.size() or contact < 0 or contact == 0) {
            cout << "Invalid! Please select the record you want to unmark as favourite: ";
            cin >> contact;
        }
        
        if(ptr->contactVector.at(contact-1)->isFav == 1) {
            ptr->contactVector.at(contact-1)->isFav = 0;
            cout << ptr->contactVector.at(contact-1)->fname << " " <<  ptr->contactVector.at(contact-1)->lname << " " <<  ptr->contactVector.at(contact-1)->email << " has been successfully unmarked as favourite!" << endl;
        }
    }
    
    //Else if there is only one contact in the vector, it will automatically unmark the favourite for the as there is only one.
    else if(ptr->contactVector.size() == 1) {
        if(ptr->contactVector.at(0)->isFav == 1) {
            ptr->contactVector.at(0)->isFav = 0;
            cout << ptr->contactVector.at(0)->fname << " " <<  ptr->contactVector.at(0)->lname << " (" <<  ptr->contactVector.at(0)->email
            << ") has been successfully unmarked as favourite!" << endl;
        }
        
        else
            cout << "This contact is already not a favourite!" << endl;
    }
    
    return true;
}

//=============================================================================
//Print Ascending: Recursive method that prints the data at nodes in ascending order (In-order traversal)
void ContactBST::printASC(Node* ptr) {
    
    //If the root is NULL, it means the BST is empty and there are no contacts in the system.
    if(root == NULL) {
        cout << "No Contacts in the System!" << endl;
        return;
    }
    
    //Base case for recursion.
    if(ptr == NULL) {
        return;
    }
    
    //We essentially do an In-order traversal and print the vector when we visit the node:
    printASC(ptr->left);
    for(int i = 0; i < ptr->contactVector.size(); i++)
    {
        Contact *ct = ptr->contactVector.at(i);
        cout << ct->fname<<", " << ct->lname<<", " << ct->email << ", " << ct->primaryPhone << ", " << ct->city << ", " << ct->country << ", " << ct->isFav << endl;
    }
    printASC(ptr->right);
}

//=============================================================================
//Print Descending: Recursive method that prints the data at nodes in descending order (Reverse In-order traversal)
void ContactBST::printDES(Node* ptr) {
    
    //If the root is NULL, it means the BST is empty and there are no contacts in the system.
    if(root == NULL) {
        cout << "No Contacts in the System!" << endl;
        return;
    }
    
    //Base case for recursion.
    if(ptr == NULL) {
        return;
    }
    
    //We essentially do a Reverse In-order traversal and print the vector when we visit the node:
    printDES(ptr->right);
    for(int i = 0; i < ptr->contactVector.size(); i++)
    {
        Contact *ct = ptr->contactVector.at(i);
        cout << ct->fname<<", " << ct->lname<<", " << ct->email << ", " << ct->primaryPhone << ", " << ct->city << ", " << ct->country << ", " << ct->isFav << endl;
    }
    printDES(ptr->left);
}

//=============================================================================
//PrintFav: Print the favourite data at nodes in an ascending order.
void ContactBST::printFav(Node* ptr) {
    
    //If the root is NULL, it means the BST is empty and there are no contacts in the system.
    if(root == NULL) {
        cout << "No Contacts in the System!" << endl;
        return;
    }
    
    //Base case for recursion.
    if(ptr == NULL) {
        return;
    }
    
    //Search every node in the BST using In-Order traversal and checks every contact in each vector in the node. O(n^2) runtime
    printFav(ptr->left);
    
    //Search every contact in the vector. If the contact in the vector has isFav == 1, then print it out.
    for(int i = 0; i < ptr->contactVector.size(); i++) {
        if(ptr->contactVector.at(i)->isFav == 1) {
            Contact *ct = ptr->contactVector.at(i);
            cout << ct->fname << ", " << ct->lname << ", " << ct->email << ", " << ct->primaryPhone << ", " << ct->city << ", " << ct->country << ", " << ct->isFav << endl;
        }
    }
    
    printFav(ptr->right);
}

//=============================================================================
//ImportCSV: Loads all the contacts from the CSV file into the BST
int ContactBST::importCSV(string path) {
        
    //Open an ifstream and if it fails then return -1.
    ifstream inFile(path);
    if(inFile.fail()) {
        cout << "File " << path << " could not be opened." << endl;
        return -1;
    }

    string contact, fname, lname, email, phone, city, country, fav, word;
    bool isfav;
    
    //While it's not the end of the file, it will read each contact line as a string, and pass it into a stream. Then it will get each word from the string (through a delimiter: ,) and store it into the necessary variables.
    int contacts(0);
    while(!inFile.eof()) {
        inFile >> contact;
        stringstream sstr(contact);
        
        getline(sstr, word, ',');
        fname = word;
        getline(sstr, word, ',');
        lname = word;
        getline(sstr, word, ',');
        email = word;
        getline(sstr, word, ',');
        phone = word;
        getline(sstr, word, ',');
        city = word;
        getline(sstr, word, ',');
        country = word;
        getline(sstr, word, ',');
        fav = word;
        
        if(fav == "1") {isfav = 1; }
        else {isfav = 0; }
        
        //A new contact will be created with the approiate key.
        Contact *data = new Contact(fname, lname, email, phone, city, country, isfav);
        add(root, fname+" "+lname, data);
        contacts++; //Contacts is incremented each time a node is added
    }
    
    //File closed.
    inFile.close();
    return contacts; //Returns the number of contacts.
}

//=============================================================================
//ExportCSV: Export all the contacts from the BST rooted at ptr to a CSV file in an ascending order using recursion.
int ContactBST::exportCSV(Node* ptr, ofstream &outFile, string path) {
    
    int contacts(0);
    if(root == NULL) {
        outFile << "No Contacts in the System!";
        return -1;
    }
    
    //Using In-order traversal recursion to export all the contacts to the ofstream (created in the main)
    //If there is a node to the left, recurse left and increment the contacts.
    if(ptr->left != NULL) {
        contacts += exportCSV(ptr->left, outFile, path);
    }

    //Exports (writes) all the contacts in the vector of the node to the CSV File.
    for(int i = 0; i < ptr->contactVector.size(); i++) {
        Contact *ct = ptr->contactVector.at(i);
        outFile << ct->fname << "," << ct->lname << "," << ct->email << "," << ct->primaryPhone << "," << ct->city << "," << ct->country << "," << ct->isFav << endl;
        contacts++; //Increments the number of contacts.
    }
    
    //If there is a node to the right, recurse right and increment the contacts.
    if(ptr->right != NULL) {
        contacts += exportCSV(ptr->right, outFile, path);
    }
    
    return contacts; //Returns the number of contacts. 
}

//=============================================================================
Node* ContactBST::findMin(Node *ptr) {
    
    //Checks if the root is NULL (BST is empty, then return NULL)
    if(root == NULL) {
        return ptr;
    }
    
    //Iteratively moves to the left most node with a left-child pointing to NULL - minimum
    while(ptr->left != NULL) {
        ptr = ptr->left;
    }
    return ptr;
}
//=============================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Item {
private:

    int ID;
    int room;
    string nm;
    double wht;
    double lnht;
    double hgt;

public:
    Item()
    {ID=0;}
    Item(int id,string n,double w, double h, double l) : ID(id), nm(n), wht(w), lnht(l), hgt(h)
    {}
Item(const Item* obj) { ID = obj->ID; nm = obj->nm; wht = obj->wht; lnht = obj->lnht; hgt = obj->hgt;}

    void display() 
    {
        cout<<"\n****************************************\n";
        cout<<" Printing....\n\n";
        cout << "Item ID: " << ID << endl;
        cout << "Item Name: " << nm << endl;
        cout << "Item Weight: " << wht << endl;
        cout << "Item lenght: " << lnht << endl;
        cout << "Item height: " << hgt << endl;
        cout<<"\n****************************************\n";
    }

    int getID() 
    {
        return ID;
    }

    string getName() 
    {
        return nm;
    }

    double getWeight()
    {
        return wht;
    }
};

class StackVan
{
private:

    int maxSize; //size of stack vector
    vector<Item*> stackItems; //stack vector
    int top; //top of stack
    double weightMax = 1000;
    double currentWht;
    int genid =1000;

public:
//--------------------------------------------------------------

StackVan() : maxSize(250), currentWht(0), top(-1) //constructor
{
    stackItems.reserve(250); //size the vector
}
//--------------------------------------------------------------
void push(int id, string n, double w, double h, double l) // put item on top
{
    if (isFull())
    {
        cout << "!Error! The Van Can not hold any more items!" << endl;
        return;
    }
    // Check if adding the item will exceed van's capacity
    if (currentWht + w < weightMax) 
    {
        stackItems[top+1] = new Item(id, n, w, h, l);
// add item to end of vector
        top++; // increment top
    }
    else
    {
        cout << "!Error!\n The Van Has Reached its Weight Capacity!" << endl;
        return;
    }
    // Update current capacity
    currentWht += w;
}

void pushi(Item& it) // put item on top
{
    double w = it.getWeight();
    if (isFull())
    {
        cout << "!Error! The Van Can not hold any more items!" << endl;
        return;
    }
    // Check if adding the item will exceed van's capacity
    if (currentWht + w < weightMax) 
    {
        stackItems.push_back(new Item(it)); // add item to end of vector
        top++; // increment top
    }
    else
    {
        cout << "!Error!\n The Van Has Reached its Weight Capacity!" << endl;
        return;
    }
    // Update current capacity
    currentWht += w;
}

//--------------------------------------------------------------
void pop() // take item from top of stack
{
    if (isEmpty())
    {
        cout << "Stack is empty. Cannot delete more items." << endl;
        return;
    }
    stackItems[top]->display();
    currentWht-= stackItems[top]->getWeight();
    top -= 1;
}

//--------------------------------------------------------------
void peek() //peek at top of stack
{ 
    stackItems[top]->display();
}
//--------------------------------------------------------------
void peekAll()
{
    for (int i=top;i>=0;i--)
    {
        stackItems[i]->display();
    }
}
//--------------------------------------------------------------
bool isEmpty() //true if stack is empty
{ 
    return (top == -1); 
}
//--------------------------------------------------------------
bool isFull()
{
    return (top == maxSize - 1); // stack is full when top is equal to the last index
}
void popspecificitem(int id) {
    // Create a temporary stack to store the items
    vector<Item*> tempStack;
    // Search for the item with the specific ID in the stack vector
    bool found = false;
    for (int i = top; i >= 0; i--) {
        if (stackItems[i]->getID() == id) {
            // If the item with the specific ID is found, pop it from the vector
            stackItems[i]->display();
            currentWht -= stackItems[i]->getWeight();
            top -= 1;
            found = true;
            break;
        }
        else {
            // If the item with the specific ID is not found, push the item onto the temporary stack
            tempStack.push_back(stackItems[i]);
            currentWht -= stackItems[i]->getWeight();
            top -= 1;
        }
    }
    // If the item with the specific ID is not found, push all the items from the temporary stack back onto the vector in the same order they were in before
    if (!found) {
        for (int i = tempStack.size() - 1; i >= 0; i--) {
            stackItems.push_back(tempStack[i]);
            currentWht += tempStack[i]->getWeight();
            top += 1;
        }
        cout << "Item with ID " << id << " was not found in the van." << endl;
    }
    // If the item with the specific ID is found, push all the items from the temporary stack back onto the vector in the same order they were in before the item with the specific ID was popped
    else {
        for (int i = tempStack.size() - 1; i >= 0; i--) {
            stackItems[top+1]=tempStack[i];
            currentWht += tempStack[i]->getWeight();
            top += 1;
        }
    }
}



int gettop()
{
   int got = top;
    return got; 
}
int getgid(){
    int gid = genid;
    genid++;
    return gid;
}
void showMenu()
{
    cout<<"Welcome to CMC Inc. Van Service... \n\n";
    cout<<"Moving Service Menu"<<endl;
    cout<<"1.Add an Item to the Truck"<<endl;
    cout<<"2.Remove an Item from the list(Removes from the back)"<<endl;
    cout<<"3.Remove a Specific Item Based on ID"<<endl;
    cout<<"4.Calculate optimal order to load in truck"<<endl;
    cout<<"5.Display Final List of Items in the Van"<<endl;
    cout<<"6.Quit Program"<<endl;
    cout<<"Choice :";
}


};
int main()
{
    StackVan truck; // initialize van with a maximum capacity of 3600
    int choice;
    truck.showMenu();
    cin >> choice;
    cout << "-----------------------------------------------------------" << endl;
    while(choice != 6)
        {
        switch(choice)
        {
            case 1:
                {
                string nm;
                int ID;
                double wht;
                double lnht;
                double hgt;
                ID = truck.getgid() +1;

                cout<<"\n*********************************************\n";  
                cout<<"New Item Generating...\n";
                cout<<"Please Enter The Name of Item: " ;
                cin>>nm;
                cout<<"Please Enter the Weight of the Item: ";
                cin>>wht;
                cout<<"Please Enter the Length of the Item: ";
                cin>>lnht;
                cout<<"Please Enter the height of the Item: ";
                cin>>hgt;
                truck.push(ID, nm, wht, hgt,lnht);
                break;
                }
            case 2: 
                {
                cout<<"\n*********************************************\n";
                truck.pop();
                break;
                }
            case 3:
                {
                int ID;
                cout<<"\n*********************************************\n"; 
                cout<<"Please Enter the Item ID wished to be removed: ";
                cin>>ID;
                truck.popspecificitem(ID) ;
                break;
                }
            case 4: 
                {
                cout<<"\n*********************************************\n";  
                break;
                }
            case 5: 
                {
                cout<<"\n*********************************************\n";
                truck.peekAll();
                break;
                }
            default:
                {
                cout<<"\n*********************************************\n";
                cout << "Not an Choice" << endl;
                break;
                }
        }
        truck.showMenu();
        cin >> choice;
    }
    cout << "You have Exited the Moving Service, have a Great Day!";

    

    cout<<"Goodbye Have an amazing Day";
    return 0;
}

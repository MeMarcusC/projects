#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Item {
private:

    int ID;
    //int room;
    string nm;
    double wht;
    double lnht;
    double hgt;

public:
    Item(int id,string n,double w, double h, double l) : ID(id), nm(n), wht(w), lnht(l), hgt(h)
    {}
    Item(const Item& obj) { ID = obj.ID; nm = obj.nm; wht = obj.wht; lnht = obj.lnht; hgt = obj.hgt;}

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
        stackItems[++top] = new Item(id, n, w, h, l); // increment top
    }
    else
    {
        cout << "!Error!\n The Van Has Reached its Weight Capacity!" << endl;
        return;
    }
      // Sort the vector using quicksort algorithm
       // quicksort(0, top);
        
        // Update current capacity
        currentWht += w;
}
void pushi(Item it) // put item on top
{
    if (isFull())
    {
        cout << "!Error! The Van Can not hold any more items!" << endl;
        return;
    }
    // Check if adding the item will exceed van's capacity
    if (currentWht + w < weightMax) 
    {
        stackItems[++top] = new Item(it); // increment top
    }
    else
    {
        cout << "!Error!\n The Van Has Reached its Weight Capacity!" << endl;
        return;
    }
      // Sort the vector using quicksort algorithm
       // quicksort(0, top);
        
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
Item* ret()
{
    Item send();
    send = stackItems[top];
    top--;
    return send;
}
//--------------------------------------------------------------
char peek() //peek at top of stack
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
void popspecificitem(int ID) 
{
    StackVan TempSt();
    if (isEmpty()) 
    {
        cout << "Van is currently empty." << endl;
        return;
    }
    // Check if the item exists in the van
    bool found = false;
    for (int i = 0; i <= top; i++) 
    {
        if (stackItems[i]->getID() == ID) 
        {
            found = true;
            // Remove the item from the vector and update the current capacity
            stackItems.pop();
            break;
        }
        else 
        {
            TempSt.pushi(stackItems[i]);
        }
    }

    if (!found) 
    {
        cout << "Item with ID " << ID << " is not in the van." << endl;
    }
    else 
    {
        stackItems.push(TempSt.ret);
    }
}
int showMenu()
{
    cout<<"Welcome to CMC Inc. Van Service... \n\n";
    cout<<"Moving Service Menu"<<endl;
    cout<<"1.Add an Item to the Truck"<<endl;
    cout<<"2.Remove an Item from the list(Removes from the back)"<<endl;
    cout<<"3.Remove a Specific Item Based on ID"<<endl;
    cout<<"4.Calculate optimal order to load in truck"<<endl;
    cout<<"5.Display Final List of Items in the Van"<<endl;
    cout<<"6.Search By Rooms"<<endl;
    cout<<"7.Quit Program"<<endl;
    cout<<"Choice :";
}
void Menu()
{
    int choice;
            showMenu();
            cin >> choice;
            cout << "-----------------------------------------------------------" << endl;
    
            while(choice != 7)
            {
                switch(choice)
                {
                    case 1:
                    {
                        cout<<"\n*********************************************\n";
                        
                        break;
                    }
                    case 2: 
                    {
                        cout<<"\n*********************************************\n";
                        
                        break;
                    }
                    case 3:
                    {
                        cout<<"\n*********************************************\n";
                        
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
                        
                        break;
                    }
                    case 6: 
                    {
                        cout<<"\n*********************************************\n";
                        
                        break;
                    }
                    default:
                    {
                        cout<<"\n*********************************************\n";
                        cout << "Not an Choice" << endl;
                        break;
                    }
                }
                showMenu();
                cin >> choice;
                
            }
            cout << "You have Exited the Moving Service, have a Great Day!";
}

};
int main()
{
    StackVan truck(); // initialize van with a maximum capacity of 3600
    int choice;
    choice = truck.showMenu():
    

    cout<<"Goodbye Have an amazing Day";
    return 0;
}

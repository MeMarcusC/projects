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
    int MH = 25;
    int MW = 15;
    int maxSize; //size of stack vector
    vector<Item*> stackItems; //stack vector
    int top; //top of stack
    double weightMax = 1000;
    double currentWht;
    int genid =1000;

    void quicksort(int low, int high) {
        if (low < high) {
            // Partition the vector and get the pivot index
            int pivotIndex = partition(low, high);
            // Recursively call quicksort on the sub-vectors on either side of the pivot
            quicksort(low, pivotIndex - 1);
            quicksort(pivotIndex + 1, high);
        }
    }

    int partition(int low, int high) {
        // Use the weight of the last item as the pivot
        double pivot = stackItems[high]->getWeight();
        // Set the pivot index to the beginning of the vector
        int pivotIndex = low;
        // Loop through the vector from the beginning to the end
        for (int i = low; i < high; i++) {
            // If the weight of the current item is less than or equal to the pivot, swap it with the item at the pivot index
            if (stackItems[i]->getWeight() >= pivot) {
                swap(stackItems[i], stackItems[pivotIndex]);
                // Increment the pivot index
                pivotIndex++;
            }
        }
        // Swap the pivot item with the item at the pivot index
        swap(stackItems[high], stackItems[pivotIndex]);
        // Return the pivot index
        return pivotIndex;
    }


public:
//--------------------------------------------------------------

StackVan() : maxSize(250), currentWht(0), top(-1) //constructor
{
    stackItems.reserve(250); //size the vector
}
//--------------------------------------------------------------
void push(int id, string n, double w, double h, double l) // put item on top
{
    cout<<"\n*********************************************\n";  
    if (isFull())
    {
        cout << "!Error! The Van Can not hold any more items!\n";
        genid--;
        return;
    }
    // Check if adding the item will exceed van's capacity
    if (currentWht + w > weightMax)
    {
        cout << "     !Error!\nThe Van Has Reached its Weight Capacity!\n" ;
        genid--;
        return;
    }
    else if (h > MH)
    {
        cout << "     !Error!\nThe Items' Height is too big for the van!\n....(Please size down the item to fit (15x25ft)...\n";
        genid--;
        return;
    }
    else if (l > MW)
    {
        cout << "     !Error!\nThe Items' Length is too big for the van!\n....(Please size down the item to fit (15x25ft)...\n";
        genid--;
        return;
    }
    else if (currentWht + w < weightMax && h <= MH && l <= MW)
    {
        stackItems[top+1] = new Item(id, n, w, h, l);
// add item to end of vector
        top++; // increment top
    }
    else
    {
        cout << "     !Error!\nThe Van Has Reached its Weight Capacity!" << endl;
        genid--;
        return;
    }
    // Update current capacity
    currentWht += w;
    cout<<"\n*********************************************\n";  
}
 void sortItems() {
        quicksort(0, top);
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
        cout << "     !Error!\nThe Van Has Reached its Weight Capacity!" << endl;
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
    cout<<"\n*********************************************\n";  
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
    truck.push("Sofa", "50", "4", "3" )
    truck.push("Lamp", "3", "0.5", "1" )
    truck.push("Box", "10", "5", "5" )
    truck.push("Chair", "5", "3", "4" )
    truck.push("Table", "20", "7", "5" )
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
                cout<<"Please Enter the Length of the Item(ft): ";
                cin>>lnht;
                cout<<"Please Enter the height of the Item(ft): ";
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
                cout<<"Sorting Items...\n"; 
                truck.sortItems();
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

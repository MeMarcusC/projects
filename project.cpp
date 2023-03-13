#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Item {
private:
    int ID;
    string name;
    double weight;
    bool fragile;

public:
    Item(int id, string n, double w, bool f) : ID(id), name(n), weight(w), fragile(f) {}

    void displayItem() 
    {
        cout << "Item ID: " << ID << endl;
        cout << "Item Name: " << name << endl;
        cout << "Item Weight: " << weight << endl;
        cout << "Fragile: " << (fragile ? "True" : "No") << endl;
        cout << endl;
    }

    int getID() 
    {
        return ID;
    }

    string getName() 
    {
        return name;
    }

    double getWeight()
    {
        return weight;
    }

    bool isFragile()
    {
        return fragile;
    }
};

class Van {
private:
    int maxCapacity = 3600; // maximum weight capacity of the van
    vector<Item*>stackVect; // stack of items to be moved
    double currentCapacity = 0; // current weight of the items in the van
    int top=-1; //top of stack
    
    void quicksort(int low, int high) 
   {
        if (low < high) 
        {
            int pivot = partition(low, high);
            quicksort(low, pivot-1);
            quicksort(pivot+1, high);
        }
    }
    
    int partition(int low, int high) 
    {
        double pivot = stackVect[low]->getWeight(); // use weight of first item as pivot
        int i = high + 1;
        for (int j = high; j > low; j--) 
        {
            if (stackVect[j]->getWeight() < pivot) // modified condition here
            {
                i--;
                swap(stackVect[i], stackVect[j]);
            }
        }
        swap(stackVect[i-1], stackVect[low]);
        return i-1;
    }
public:
Van(int maxCap) : maxCapacity(maxCap), currentCapacity(0), top(-1) {
    stackVect = vector<Item*>(maxCapacity);
    }


  void pushitem(int ID, string name, double weight, bool fragile) 
  {
        // Check if van is full
        if (isFull()) 
        {
            cout << "Van is full." << endl;
            return;
        }
        // Check if adding the item will exceed van's capacity
        if (currentCapacity + weight > maxCapacity) 
        {
            cout << "Item cannot be added to van as it exceeds the van's capacity." << endl;
            return;
        }
        // Create new item object and add it to the vector
        stackVect[++top] = new Item(ID, name, weight, fragile);
        
        // Sort the vector using quicksort algorithm
        quicksort(0, top);
        
        // Update current capacity
        currentCapacity += weight;
    }
    
   void popitem()
    {
     if (isEmpty()) 
     {
        cout << "Van is currently empty." << endl;
        return;
    }
    delete stackVect[top--];
    currentCapacity -= stackVect[top]->getWeight();
    }

    
    void popspecificitem(int ID) 
    {
        if (isEmpty()) 
         {
            cout << "Van is currently empty." << endl;
            return;
         }
    // Check if the item exists in the van
    bool found = false;
    for (int i = 0; i <= top; i++) 
    {
        if (stackVect[i]->getID() == ID) 
        {
            found = true;
            // Remove the item from the vector and update the current capacity
            currentCapacity -= stackVect[i]->getWeight();
            delete stackVect[i];
            // Shift the remaining items in the vector to fill the gap
            for (int j = i; j < top; j++) 
            {
                stackVect[j] = stackVect[j+1];
            }
            top--;
            break;
        }
    }
    if (!found) 
    {
        cout << "Item with ID " << ID << " is not in the van." << endl;
    }
    }
    void peek()
    {
       for (int i=top;i>=0;i--)
            {
                stackVect[i]->displayItem();
            }
    }

bool isEmpty() 
    {
        return (top == -1);
    }

    bool isFull() 
    {
        return (currentCapacity >= maxCapacity);
    }

};
int main()
{
    Van truck(3600); // initialize van with a maximum capacity of 3600
    int choice;
    int ID;
    string name;
    double weight;
    bool fragile;
    
    cout<<"Welcome to 2 Men and a Truck Moving Service "<<endl;
    cout<<endl;
    cout<<"Moving Service Menu"<<endl;
    cout<<"1.Add an Item to the Truck"<<endl;
    cout<<"2.Remove an Item from the list(Removes from the back)"<<endl;
    cout<<"3.Remove a Specific Item Based on ID"<<endl;
    cout<<"4.Calculate optimal order to load in truck"<<endl;
    cout<<"5.Display Final List of Items in the Van"<<endl;
    cout<<"6.Quit Program"<<endl;
    cout<<"Choice :";
    cin>>choice;
    while (choice!=6)
    {
        if (choice==1)
        {
            cout << endl;
            cout << "Item ID: ";
            cin >> ID;
            cout << "Item Name: ";
            cin >> name;
            cout << "Item Weight: ";
            cin >> weight;
            cout << "Fragile? (1.Yes or 0.No) ";
            cin >> fragile;
            truck.pushitem(ID, name, weight,fragile);
        }
        else if (choice==2)
        {
              truck.popitem();
        }
        else if (choice==3)
        {
            truck.peek();
        }
    cout<<"Moving Service Menu"<<endl;
    cout<<"1.Add an Item to the Truck"<<endl;
    cout<<"2.Remove an Item from the list(Removes from the back)"<<endl;
    cout<<"3.Remove a Specific Item Based on ID"<<endl;
    cout<<"4.Calculate optimal order to load in truck"<<endl;
    cout<<"5.Display Final List of Items in the Van"<<endl;
    cout<<"6.Quit Program"<<endl;
    cout<<"Choice :";
    cin>>choice;
    }
    cout<<"Goodbye Have an amazing Day";
    return 0;
}
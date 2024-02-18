#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include<ostream>
#include<istream>
#include <sstream>
#include <string>

using namespace std;
struct Product
{
    string strid;
    string name;
    string strprice;
    string category;
    int id;
    double price;
    Product* next;
    //convert to int
    int convertToInt()
    {
        id = stoi(strid);
        return id;
    }
    double convertToDouble()
    {
        price = stof(strprice);
        return price;
    }

    
};

typedef Product product;



product *hptr;//head
product *cptr;//current
product *nptr;//tail


void menu();
void read();
void display();
void update(int x);
Product* search(int x);
void deleteProduct(int x);






//variable names
/*string strid;
string name;
string strprice;
string category;*/



    


//read file data
void read() {
    hptr = nptr = nullptr;
    const string inFileName{ "product_data.txt" }; // Specify the file name

    ifstream inFile(inFileName);
    if (inFile.fail()) {
        cout << "\nFile " << quoted(inFileName) << " did not open" << endl;
        exit(1);
    }

    while (true) {
        cptr = new product;
        cptr->next = nullptr;

        // Read data from each category
        getline(inFile, cptr->strid, ',');
        getline(inFile, cptr->name, ',');
        getline(inFile, cptr->strprice, ',');
        getline(inFile, cptr->category);

        cptr->strid.erase(remove_if(cptr->strid.begin(), cptr->strid.end(), ::isspace), cptr->strid.end());
        //cptr->name.erase(remove_if(cptr->name.begin(), cptr->name.end(), ::isspace), cptr->name.end());
        cptr->strprice.erase(remove_if(cptr->strprice.begin(), cptr->strprice.end(), ::isspace), cptr->strprice.end());
        cptr->category.erase(remove_if(cptr->category.begin(), cptr->category.end(), ::isspace), cptr->category.end());
        
        
        if (inFile.fail()) {
            delete cptr; // Don't need it
            break;
        }

        // Insert into the linked list
        if (hptr == nullptr) {
            // First item in the list. Point hptr at it
            hptr = cptr;
        } else {
            nptr->next = cptr;
        }
        nptr = cptr;
        cptr->convertToDouble();
        cptr->convertToInt();
    }

    cout << "data loaded!" << endl;
}

void display()
{
    Product* ptr;
    ptr = hptr;
    
    //const string inFileName{ "product_data.txt" };

    //ifstream inFile(inFileName);

    
    while (ptr != nullptr)
    {   //ptr->convertToDouble();
        //ptr->convertToInt();
        cout
                    << "\n ID: " << ptr->id
                    << "\n Name: " << ptr->name
                    << "\n Price: " << ptr->price
                    << "\n Category: " << ptr->category << "\n\n";
        
        ptr = ptr->next;
    }
    
    
}

void insert() {
    cptr = new product;
    cptr->next = nullptr;

    cout << "Enter product ID: ";
    cin >> cptr->id;
    cout << "Enter product name: ";
    cin.ignore(); // Clear newline from previous input
    getline(cin, cptr->name);
    cout << "Enter product Price: ";
    cin >> cptr->price;
    cout << "Enter product category: ";
    cin.ignore();
    getline(cin, cptr->category);

    
    
    // Insert into the linked list
    if (hptr == nullptr) {
        // First item in the list. Point hptr at it
        hptr = cptr;
    } else {
        nptr->next = cptr;
    }
    nptr = cptr;

    
}


Product* search(int x)
{
    

    Product* temp = hptr;
    string found = "search query found!";
    string notFound = "search query not found!";
    
     // Initialize current
    while (temp != nullptr) {
        if (temp->id != x)
            temp = temp->next;
        else
        {
            
            cout
                    << found << endl
                    << "\n ID: " << temp->id
                    << "\n Name: " << temp->name
                    << "\n Price: " << temp->price
                    << "\n Category: " << temp->category << "\n\n";
                    
            return temp;
        }
    }
    cout<<notFound<<endl;
    temp = nullptr;
    return temp;
}


void BubbleSort()
{
    
    int count = 0, i;
    Product *start = hptr;
    Product *curr = NULL;
    Product *prev = NULL;
    Product *temp = NULL;


    
    while(start != NULL) { //grab count
        count++;
        start = start->next;
    }
    
    
        
        
        // Assuming 'prev' is the node before 'current'
    
    
    for(i = 0; i<count; ++i) { //for every element in the list

        curr = prev = hptr; //set curr and prev at the start node

        while (curr->next != NULL) { //for the rest of the elements in the list
            if (curr->price > curr->next->price) { //compare curr and curr->next

                temp = curr->next; //store the next one in the temporary pointer
                curr->next = curr->next->next;//move the one after that to that position(it's stored in temp so it isn't lost)
                temp->next = curr;//move the current to be after our temp value, essentially swapping them

                //setup pointers for prev and possibly head
                if(curr == hptr) //this is the case of the first element swapping to preserve the head pointer
                    hptr = prev = temp;
                else //setup trail correctly
                    prev->next = temp;
                curr = temp; //update curr to be temp finalizing the position change
            }
            //on the the next
            prev = curr;
            curr = curr->next;
        }
    }
    
} 

void ReverseBubbleSort()
{
    
    int count = 0, i;
    Product *start = hptr;
    Product *curr = NULL;
    Product *prev = NULL;
    Product *temp = NULL;


    
    while(start != NULL) { //grab count
        count++;
        start = start->next;
    }
    
    
        
        
    // Assuming 'prev' is the node before 'current'
    
    
    for(i = 0; i<count; ++i) { //for every element in the list

        curr = prev = hptr; //set curr and prev at the start node

        while (curr->next != NULL) { //for the rest of the elements in the list
            if (curr->price < curr->next->price) { //compare curr and curr->next

                temp = curr->next; //store the next one in the temporary pointer
                curr->next = curr->next->next;//move the one after that to that position(it's stored in temp so it isn't lost)
                temp->next = curr;//move the current to be after our temp value, essentially swapping them

                //setup pointers for prev and possibly head
                if(curr == hptr) //this is the case of the first element swapping to preserve the head pointer
                    hptr = prev = temp;
                else //setup trail correctly
                    prev->next = temp;
                curr = temp; //update curr to be temp finalizing the position change
            }
            //on the the next
            prev = curr;
            curr = curr->next;
        }
    }
    
}

void update(int x)
{
    //update a node/product in the code
    //how do I do this? collect the info given in a search for said node

    Product* temp = search(x);
    cout << "Enter new ID: ";
    cin >> temp->id;
    cout << "Enter new product name: ";
    cin.ignore(); // Clear newline from previous input
    getline(cin, temp->name);
    cout << "Enter new product Price: ";
    cin >> temp->price;
    cout << "Enter new product category: ";
    cin.ignore();
    getline(cin, temp->category);
    //store it in a temp node
    cout
                    
                    << "\n ID: " << temp->id
                    << "\n Name: " << temp->name
                    << "\n Price: " << temp->price
                    << "\n Category: " << temp->category << "\n\n";


    
}

void deleteProduct(int x)
{
    
    Product* temp = search(x);
    if(temp == NULL)
    {
        printf("Product not found.\n");
        return;
    }
    if(temp == hptr)
    {
        Product* oldHead = hptr;
        hptr = temp->next;
        free(oldHead);
    }
    else
    {
        Product* prev = hptr;
        while(prev != NULL && prev->next != temp)
        {
            prev = prev->next;
        }
        if(prev != NULL)
        {
            cout<<"deleting"<< endl;
            prev->next = temp->next;
            free(temp);
        }
    }

    
}


void displayMenu()
{
    int choice;
    std::chrono::time_point<chrono::system_clock> start;
    std::chrono::time_point<chrono::system_clock> end;
    cout << 
                "Please select an option between 0,1,2,3,4,5,6:\n "
                "\n0. Load Data\n"
                "1. Display products\n"
                "2. Search for product\n"
                "3. Sort Products\n"
                "4. Delete Product\n"
                "5. Insert Product\n"
                "6. Update Product" << endl;

    cin >> choice;
    
    switch(choice)
    {
    case 0:
        read();
        displayMenu();
        break;
    case 1:
        display();
        displayMenu();
        break;
    case 2:
        int x;
        cout<<"enter product ID of the product you're searching for: "<< endl;
        cin >> x;
        search(x);
        displayMenu();
        break;
    case 3:

        
        start = chrono::system_clock::now();
        BubbleSort();
        end = chrono::system_clock::now();
        auto duration = (std::chrono::duration_cast<chrono::nanoseconds>(end - start));
        std::cout << "Time taken to sort: " << duration.count() << " nanoseconds. \n" << std::endl;
        displayMenu();
        break;
    case 4:
        int y;
        cout<<"enter product ID of the product you want to delete: "<< endl;
        cin >> y;
        deleteProduct(y);
        displayMenu();
        break;
    case 5:
        insert();
        displayMenu();
        break;
    case 6:
        int z;
        cout<<"enter product ID of the product you want to update: "<< endl;
        cin >> z;
        update(z);
        displayMenu();
        break;
    case 7:
        ReverseBubbleSort();
        displayMenu();
        break;
    default: break;
    }
    
}

int main()
{
    
    
    read();
    cout << "Welcome to the shopping cart!\n";
    displayMenu();
    
    return 0;
    
    //display();
    //search(82777);
    
    
    
    
    
    
    //display();
    //deleteProduct(82777);
    //update(82777);
    //display();
    //search(82777);
    
    //insert();
    //display();
    
    
    
}
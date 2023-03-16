/*
References
    (1) Data structure slide chapter 28(page7), chapter29(page3, page5, page8)
    (2) Blog: https://blockdmask.tistory.com/333(stoi() function)
              https://novlog.tistory.com/entry/C-%EC%9E%85%EB%A0%A5-%ED%95%A8%EC%88%98-%EC%A0%95%EB%A6%AC-cin-getline-feat-cinignore?category=885399(cin.ignore(), getline())
*/

#include <iostream>
#include <string>
#include <istream>

#define MAX_SIZE 31// Size + 1
using namespace std;

class element
{

public:
    string name;   // Name
    int id;        // ID
    string school; // School
    element();
    element(string new_name, int new_id, string new_school);
};
element::element()
{
}

element::element(string new_name, int new_id, string new_school)
{
    name = new_name;
    id = new_id;
    school = new_school;
}

class min_heap
{
private:
    int size;

public:
    min_heap();
    void INSERT(element arr[], element new_element); // insert new element
    element MINIMUM(element arr[]);                  // return element with smallest key
    element EXTRACT_MIN(element arr[]);              // remove and return element with smallest key
    void DECREASE_KEY(element arr[], int x, int k);  // decrease value of element x's key to k

    bool fullcheck();                         // check heap is full
    bool emptycheck();                        // check heap is empty
    int getSize();                            // return size
    element getElement(element arr[], int i); // return indes(i) of element array
    void adjust(element arr[], int root);     // heapify the tree from the root
};

min_heap::min_heap()
{
    size = 0;
}

void min_heap::INSERT(element arr[], element new_element)
{

    size++;
    int k = size;

    while ((k != 1) && (new_element.id < arr[k / 2].id))
    {
        // If the added element has a lower key value than the parent, replace the value of the parent with child.
        arr[k] = arr[k / 2];
        k /= 2;
    }

    // k is the location of the new element after the operation is finished
    arr[k] = new_element;
}

element min_heap::MINIMUM(element arr[])
{
    return arr[1];
}

element min_heap::EXTRACT_MIN(element arr[])
{
    element t; // last element
    element last;
    int parent, child;

    if (!emptycheck())
    {

        parent = 1;
        child = 2;
        t = MINIMUM(arr);
        last = arr[size];
        size--;

        while (child <= size)
        {
            if ((child < size) && arr[child].id > arr[child + 1].id)
            {            // compare the left and right element
                child++; // select right element
            }
            if (last.id <= arr[child].id)
                break; // Break if it's small compared to the value of the end element

            arr[parent] = arr[child];
            parent = child;
            child *= 2;
        }
        // Put the last element in parent.
        arr[parent] = last;
    }
    return t;
}

void min_heap::DECREASE_KEY(element arr[], int x, int k)
{

    arr[x].id = k;

    for (int i = size / 2; i >= 1; i--)
    { // heapify
        adjust(arr, i);
    }
}

bool min_heap::fullcheck()
{
    if (size >= MAX_SIZE - 1)
    {
        return true;
    }
    return false;
}
bool min_heap::emptycheck()
{
    if (size < 1)
    {
        return true;
    }
    return false;
}
int min_heap::getSize()
{
    return size;
}

element min_heap::getElement(element arr[], int i)
{
    return arr[i];
}

void min_heap::adjust(element arr[], int root)
{

    int key = arr[root].id; // root ID
    int child = 2 * root;
    element tmp = arr[root];

    while (child <= size)
    {
        if ((child < size) && (arr[child].id > arr[child + 1].id))
        { // Child is smaller than size and compared left and right element
            child++;
        }
        if (key < arr[child].id)
            break;
        else
        {
            arr[child / 2] = arr[child];
            child *= 2;
        }
    }
    arr[child / 2] = tmp;
}

string countNum(string input)
{
    /*A function that tells you how many numbers in a string
    If the number of numbers is 4, return the string. If not return false*/
    int count = 0;
    string tmp = "";

    for (int i = 0; i < input.size(); i++)
    {
        if (input.at(i) >= 48 && input.at(i) <= 57)
        { // If the char is num
            count++;
            tmp += input.at(i);
        }
    }

    if (count == 4)
        return tmp;
    return "false";
}

bool checkAllNum(string input)
{
    /*Function to determine if input is all numeric
    If the first element is 0, if there are letters between the numbers, return false
    */

    if (input.at(0) == 48)
        return false;

    for (int i = 1; i < 4; i++)
    {
        if (input.at(i) < 48 || input.at(i) > 57)
            return false;
    }

    return true;
}

string checkId(string input)
{
    /*
    Check the id is formatted correctly and return the string

    Correct case
        - if the input has 4-digit number including other char.
            ex)12_45 -> 1245,  12nfdj57 -> 1257
    Wrong case
        - if the input length is over or less than 4
        - if the number start with 0
    */
    int size = input.size();

    if (size < 4)
    {

        cout << "Type ID Again!!!" << endl
             << endl;
        return "false";
    }

    else if (size == 4)
    {

        if (checkAllNum(input))
        {

            return input;
        }
        else
        {
            cout << "Type ID Again!!!" << endl
                 << endl;
            return "false";
        }
    }

    else
    {

        if (checkAllNum(countNum(input)))
        {

            if (countNum(input) == "false")
            {
                cout << "Type ID Again!!!" << endl
                     << endl;
                return "false";
            }
            else
                return countNum(input); // If the input size is over 4 and it has only 4 digit number, return the digit number
        }
        else
        {
            cout << "Type ID Again!!!" << endl
                 << endl;
            return "false";
        }
    }
}

int main()
{
    char input; // Input menu

    string name_tmp;   // Temporary name
    int id_tmp;        // Temporary ID
    string school_tmp; // Temporary school

    min_heap students;
    element min_queue[MAX_SIZE]; // array of element

    do
    {
        cout << "*********** MENU ****************" << endl;
        cout << "I : Insert new element into queue." << endl;
        cout << "D : Delete element with smallest key from queue" << endl;
        cout << "C : Decrease key of element in queue." << endl;
        cout << "P : Print out all elements in queue. " << endl;
        cout << "Q : Quit" << endl
             << endl;
        cout << "Choose menu: ";
        cin >> input;
        cin.ignore();

        if (input == 'I')
        {
            string id_first;

            if (!students.fullcheck())
            {

                cout << "Enter name of element: ";
                cin >> name_tmp;
                cin.ignore();

                do
                { // check if it is correct form
                    cout << "Enter id of element: ";
                    getline(cin, id_first); // Receive id as string first
                } while (checkId(id_first) == "false");

                id_tmp = stoi(checkId(id_first)); // type case string to int

                cout << "Enter school of element: ";
                cin >> school_tmp;
                cin.ignore();

                students.INSERT(min_queue, element(name_tmp, id_tmp, school_tmp));
                cout << "New element [" << name_tmp << ", " << id_tmp << ", " << school_tmp << "] is inserted." << endl
                     << endl;
            }

            else
            {
                cout << "Heap is Full" << endl
                     << endl;
            }
        }

        else if (input == 'D')
        {
            if (!students.emptycheck())
            {
                element tmp = students.EXTRACT_MIN(min_queue);
                cout << "[" << tmp.name << ", " << tmp.id << ", " << tmp.school << "]"
                     << " is deleted." << endl
                     << endl;
            }
            else
            {
                cout << "Heap is Empty" << endl
                     << endl;
            }
        }

        else if (input == 'C')
        {
            int size = students.getSize();
            int index_element, change_value;
            bool check_id = true;
            string input_id;

            if (size >= 1)
            {
                do
                { 
                    cout << "Enter index of element: ";
                    cin >> index_element;
                    cin.ignore();

                } while (index_element > size);

                if (min_queue[index_element].id == 1000)
                { // if ID is 1000, it cannot decrease key
                    cout << "It is smallest ID" << endl
                         << endl;
                }
                else
                {

                    do
                    { // Update by making sure it is smaller than the current ID and meets the conditions

                        if (check_id == false)
                            cout << "Type ID Again!!!" << endl
                                 << endl;

                        cout << "Enter id of element(1000~" << min_queue[index_element].id - 1 << ", 4 digit): ";
                        getline(cin, input_id);
                        check_id = false;
                    } while (checkId(input_id) == "false" || (stoi(checkId(input_id)) > min_queue[index_element].id));

                    change_value = stoi(checkId(input_id));
                    cout << endl
                         << endl;
                    students.DECREASE_KEY(min_queue, index_element, change_value);
                }
            }

            else
            {
                cout << "Heap is Empty!!" << endl
                     << endl;
            }
        }

        else if (input == 'P')
        {
            if (students.getSize() >= 1)
            {
                for (int i = 1; i <= students.getSize(); i++)
                {
                    element tmp = students.getElement(min_queue, i);
                    cout << i << " = [" << tmp.name << ", " << tmp.id << ", " << tmp.school << "]  " << endl
                         << endl;
                }
            }
            else
            {
                cout << "Heap is Empty!!" << endl
                     << endl;
            }
        }
        else if (input == 'Q')
        {
            cout << "Thank you, Bye!";
        }

        else
        {
            cout << "Choose Menu Again!!" << endl
                 << endl;
        }

    } while (input != 'Q');

    return 0;
}
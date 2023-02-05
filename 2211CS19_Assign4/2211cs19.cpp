/*
Name: Krishna Kant Verma
Roll No: 2211CS19
Computer System Lab - 2
Assignment No: 4
Indian Institute of Technology Patna
*/

// Including Master header file which includes all the files
#include <bits/stdc++.h>
using namespace std;

// creating class Node to store the Creates the nodes of the doubly linked list
class Node
{
    // public members : datapart , nextPtr and prevPtr
public:
    string data;
    Node *next;
    Node *prev;
};

// creating Circular Doubly Linked List
class CircularDoublyList
{
    // public members : headPtr , tailPtr ,count of node and Sign of Number (-1: for negative , 1:positive)
public:
    Node *head;
    Node *tail;
    int count = 0;
    int sign = 1;

    // Calling Constructor to Create Circular Doubly Linked List
    CircularDoublyList() : head(nullptr), tail(nullptr) {}

    // a method of class which reverse the Linked List because i have taversing the list in reverse
    void reverseList(Node *start)
    {
        // if start == tail just return from here
        if (start == tail)
        {
            return;
        }
        // creating two temp pointers to reverse the links
        Node *t1, *t2, *t3;
        t1 = start;
        t3 = start;
        t2 = t1->next;
        t1->next = NULL;
        t1->prev = t2;
        // iterate on t2 ans wapping the links
        while (t2 != start)
        {
            t2->prev = t2->next;
            t2->next = t1;
            t1 = t2;
            t2 = t2->prev;
        }
        t3->next = t1;
        t1->prev = t3;
        start = t1;
        head = start;
        tail = t3;
    }
    // this is a method of class which add the First Special Node as per question which handles meta data : count of nodes and sign
    void addFirstSpecialNode(Node *itr, int sign)
    {
        // creating node
        Node *newNode = new Node();
        newNode->data = to_string(count);
        // if negative handling
        if (sign == -1)
        {
            newNode->data = "-" + to_string(count);
        }
        // attching the links
        newNode->next = head;
        newNode->prev = tail;
        head->prev = newNode;
        tail->next = newNode;
        head = newNode;
    }

    // a method which is used to Insert Node into the Circular DLL
    void Insert(string s)
    {
        // if s[0] == - change sign
        if (s[0] == '-')
        {
            sign = -1;
            s = s.substr(1);
        }

        Node *itr = head;

        // splitting the strings into atmost 5 digits and creating CLL for same
        int len = s.length();
        int i = len - 1;
        int size = 5;
        while (i >= 0)
        {
            int j = 0;
            string substring = "";
            while (j < size && i >= 0)
            {
                string tempString = "";
                tempString += s[i];
                substring = tempString + substring;
                i--;
                j++;
            }

            // attaching the node to CDLL , adjusting links
            Node *newNode = new Node();
            newNode->data = substring;
            // if we are adding first ptr
            if (itr == NULL)
            {
                newNode->prev = NULL;
                newNode->next = NULL;
                head = tail = newNode;
                count++;
                itr = newNode;
            }
            // otherwise add to prev node
            else
            {
                itr->next = newNode;
                newNode->prev = itr;
                newNode->next = head;
                head->prev = newNode;
                tail = newNode;
                itr = newNode;
                count++;
            }
        }
        // reversing List to original order
        reverseList(head);
        // adding the meta data Node to CDLl
        addFirstSpecialNode(head, sign);
    }

    // a method used to Print the Final Result after the addition of two numbers
    void PrintingFinalResult()
    {
        cout << "***Printing Final Result***" << endl;
        if (sign == -1)
        {
            cout << "-";
        }
        Node *current = head;
        // iterating over  the list
        while (current != tail)
        {
            if (current != head)
                cout << current->data;
            current = current->next;
        }
        cout << tail->data << endl;
    }
    // a method used to Print the Linked List
    void Print()
    {
        Node *current = head;
        // iterating over list and printing
        while (current != tail)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << tail->data << endl;
    }
};
// ****End of the Class***

// a Function used to handle the leading zeroes in List of First Node
void handleLeadingZeroes(CircularDoublyList &l3)
{
    int leadZeroNeg = 0;
    while (l3.head->next && l3.head->next->data[leadZeroNeg] == '0' && leadZeroNeg <= 5)
    {
        leadZeroNeg++;
    };
    if (l3.head->next && l3.head->next->data[0] == '0')
    {
        l3.head->next->data = l3.head->next->data.substr(leadZeroNeg, 5 - leadZeroNeg);
    }
}

// a Functiont that takes tail Pointers of two numbers and add them (if any number is negative)
void addTwoCDLLsNeg(Node *number1, Node *number2, CircularDoublyList &result)
{
    Node *head1 = number1->next;
    Node *head2 = number2->next;

    string computation = "";
    int borrow = 0;
    // iterating over List and adding the numbers
    while (number1 != head1 && number2 != head2)
    {
        int num1 = stoi(number1->data);
        int num2 = stoi(number2->data);
        // computing individual result
        int temp = num1 - num2 + borrow;
        if (temp < 0)
        {
            temp = 100000 + temp;
            borrow = -1;
        }
        else
        {
            borrow = 0;
        }
        string tempRes = to_string(temp);
        if (tempRes.size() != 5)
        {
            int cnt = 5 - tempRes.size();
            while (cnt--)
            {
                tempRes = "0" + tempRes;
            }
        }
        computation = tempRes + computation;
        // move to prev node
        number1 = number1->prev;
        number2 = number2->prev;
    }
    // if number1 still exists
    while (number1 != head1)
    {
        int num1 = stoi(number1->data);
        // int temp = num1 + carry;
        int temp = num1 + borrow;
        if (temp < 0)
        {
            temp = 100000 + temp;
            borrow = -1;
        }
        else
        {
            borrow = 0;
        }
        string tempRes = to_string(temp);
        computation = tempRes + computation;
        number1 = number1->prev;
    }
    // if number2 still exits
    while (number2 != head2)
    {
        int num2 = stoi(number2->data);
        // int temp = num2 + carry;
        int temp = num2 + borrow;
        if (temp < 0)
        {
            temp = 100000 + temp;
            borrow = -1;
        }
        else
        {
            borrow = 0;
        }
        string tempRes = to_string(temp);
        computation = tempRes + computation;
        number2 = number2->prev;
    }
    // handling leading zeroes
    int idx = 0;
    while (computation[idx] == '0')
    {
        idx++;
    }
    computation = computation.substr(idx);
    // insert into new Ans List
    result.Insert(computation);
}
// a function that add two number list(if both are positive or both are negative)
void addTwoCDLLs(Node *number1, Node *number2, CircularDoublyList &result)
{
    Node *head1 = number1->next;
    Node *head2 = number2->next;

    string computation = "";
    int carry = 0;
    // start both from tail Pointers
    while (number1 != head1 && number2 != head2)
    {
        int num1 = stoi(number1->data);
        int num2 = stoi(number2->data);
        int temp = num1 + num2 + carry;
        string tempRes = to_string(temp);
        // doing computation of individual node
        tempRes.size() > 5 ? carry = (temp / 100000) % 100000 : carry = 0;
        if (tempRes.size() > 5)
        {
            tempRes = tempRes.substr(1, 5);
        }
        if (tempRes.size() != 5)
        {
            int cnt = 5 - tempRes.size();
            while (cnt--)
            {
                tempRes = "0" + tempRes;
            }
        }
        computation = tempRes + computation;
        number1 = number1->prev;
        number2 = number2->prev;
    }
    // if number 1 still exists
    while (number1 != head1)
    {
        int num1 = stoi(number1->data);
        int temp = num1 + carry;
        string tempRes = to_string(temp);
        tempRes.size() > 5 ? carry = (temp / 100000) % 100000 : carry = 0;
        if (tempRes.size() > 5)
        {
            tempRes = tempRes.substr(1, 5);
        }
        computation = tempRes + computation;
        number1 = number1->prev;
    }
    // if number 2 still exists
    while (number2 != head2)
    {
        int num2 = stoi(number2->data);
        int temp = num2 + carry;
        string tempRes = to_string(temp);
        tempRes.size() > 5 ? carry = (temp / 100000) % 100000 : carry = 0;
        if (tempRes.size() > 5)
        {
            tempRes = tempRes.substr(1, 5);
        }
        computation = tempRes + computation;
        number2 = number2->prev;
    }
    // if carry exists handling too
    if (carry > 0)
    {
        computation = to_string(carry) + computation;
    }

    result.Insert(computation);
}

// a fuction used to check invalidty of number
bool invalid(string num)
{
    int i = 0;
    if (num[i] == '-')
    {
        i++;
    }
    for (; i < num.size(); i++)
    {
        if (num[i] >= '0' && num[i] <= '9')
        {
            continue;
        }
        else
        {
            return true;
        }
    }
    return false;
}

int main()
{
    // creating three CDLL (for num1 , num2 , result)
    CircularDoublyList l1, l2, l3;
    string num1, num2;
    cout << "Enter Numbers Without Leading Zeroes: " << endl;
    cout << "Enter First Number: " << endl;
    cin >> num1;
    cout << "Enter Second Number: " << endl;
    cin >> num2;

    if (invalid(num1) or invalid(num2))
    {
        cout << "Wrong Input Provided" << endl;
        return 0;
    }
    // inserting into list1
    l1.Insert(num1);
    // inserting into list2
    l2.Insert(num2);
    // printing List 1
    cout << "Printing List 1: " << endl;
    l1.Print();
    // printing List 2
    cout << "Printing List 2: " << endl;
    l2.Print();
    // initializing both to NULL
    l3.head = NULL;
    l3.tail = NULL;
    // if both are positive or negative
    if (l1.sign * l2.sign == 1)
    {
        if (l1.sign == -1 and l2.sign == -1)
        {
            l3.sign = -1;
        }
        // adding the list
        addTwoCDLLs(l1.tail, l2.tail, l3);
    }
    else
    {
        // if any one negative
        if (l1.sign == -1)
        {
            num1 = num1.substr(1);
        }
        else
        {
            num2 = num2.substr(1);
        }
        // if number is same
        if (num1 == num2)
        {
            l3.Insert("0");
            cout << "Printing Result List:" << endl;
            l3.Print();
            cout << "***Printing Final Result***" << endl;
            cout << 0 << endl;
            cout << "Program Executed Successfully" << endl;
            return 0;
        }
        // handling the bigger and ssmaller number and calling it respectively
        if (num1.size() > num2.size())
        {
            l3.sign = l1.sign;
            addTwoCDLLsNeg(l1.tail, l2.tail, l3);
        }
        else if (num1.size() < num2.size())
        {
            l3.sign = l2.sign;
            addTwoCDLLsNeg(l2.tail, l1.tail, l3);
        }
        else
        {
            if (num1 > num2)
            {
                l3.sign = l1.sign;
                addTwoCDLLsNeg(l1.tail, l2.tail, l3);
            }
            else
            {
                l3.sign = l2.sign;
                addTwoCDLLsNeg(l2.tail, l1.tail, l3);
            }
        }
    }
    // handling Leading zeroes in Final Ans
    handleLeadingZeroes(l3);
    // Printing Final List
    cout << "Printing Result List:" << endl;
    l3.Print();
    // Printing Final Result
    l3.PrintingFinalResult();
    cout << "Program Executed Successfully" << endl;
    return 0;
}
// thank you so much
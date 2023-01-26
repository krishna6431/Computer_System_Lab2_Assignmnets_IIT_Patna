/*
Name: Krishna Kant Verma
Roll No: 2211CS19
Computer System Lab - 2
Assignment No: 3
Indian Institute of Technology Patna

*/

// this is all required header file
// header file for handling io methods
#include <iostream>
// header file to use set Data Structure
#include <set>

// here we are using namespace as standard
using namespace std;

// creating a blueprint for Nodes  Representing balls as LinekdList
class ballListNode
{
public:
    // stores value in node
    int value;
    // pointer to point to next Node
    ballListNode *next;
};

// creating a blueprint for Circular Singly List to connect All Balls Nodes in Circular Fashion
class ballsCLL
{
private:
    // pointer pointing to head
    ballListNode *head;
    // pointer pointing to tail
    ballListNode *backPtr;
    // storing size of the circular linked list
    int size;

public:
    // circular Linked list constrcutor to
    ballsCLL()
    {
        // assiging NULL
        head = nullptr;
        backPtr = nullptr;
        size = 0;
    }

    // a function that takes a number as parameter and convert respective value to their ordinal value in string Format
    string requiredOrdinalNumber(int num)
    {
        // Suffix variable stores ans
        string suffix;
        // extracting first and second digit
        int firstPos = num % 10;
        int secondPos = num % 100;

        // checking first Position digit
        switch (firstPos)
        {
        case 1:
            if (secondPos != 11)
            {
                suffix = "st";
            }
            else
            {
                suffix = "th";
            }
            break;
        case 2:
            if (secondPos != 12)
            {
                suffix = "nd";
            }
            else
            {
                suffix = "th";
            }
            break;
        case 3:
            if (secondPos != 13)
            {
                suffix = "rd";
            }
            else
            {
                suffix = "th";
            }
            break;
        default:
            suffix = "th";
        }
        // return final ans as string
        return to_string(num) + suffix;
    }
    // a function that takes input and inserting that node into circular linked list of the respective CLL object
    void insertIntoCircularSinglyList(int data)
    {
        // creating new Node
        ballListNode *newballListNode = new ballListNode();
        newballListNode->value = data;

        // adjusting head and back pointer to maintain CLL

        // base case when head is NULL
        if (head == nullptr)
        {
            head = newballListNode;
            backPtr = newballListNode;
            newballListNode->next = head;
        }
        // other cases when head not NULL
        else
        {
            backPtr->next = newballListNode;
            backPtr = newballListNode;
            newballListNode->next = head;
        }
        // incrementing size of CLL
        size++;
    }

    // a function that prints all the nodes of the respectice object on which it is called
    void printBallsList()
    {
        set<int> sorted;
        // assiginig iterator to head
        ballListNode *itr = head;

        // checking while itr != back Pointer
        while (itr != backPtr)
        {
            sorted.insert(itr->value);
            itr = itr->next;
        }
        // printing backPtr Value
        sorted.insert(backPtr->value);
        int count = sorted.size();
        for (auto x : sorted)
        {
            // checking whether it is last element (maintaing "." and ",")
            if ((count--) > 1)
            {
                cout << x << ", ";
            }
            else
            {
                cout << x << ".";
            }
        }
        cout << endl;
    }

    // a function that takes CLL object and k and Showing all the Steps
    void explainSteps(ballsCLL &balls, int k)
    {

        // creating two pointer to point one on head and other on back pointer
        ballListNode *currentPtr = head;
        ballListNode *prevPtr = backPtr;

        // maintaining two variable count and stepcount to show stepsCount
        int count = 1;
        int stepCounter = 1;

        // Running Loop till CLL has only one Element
        while (size > 1)
        {
            // if count == k then we have to delete that node
            if (count == k)
            {
                cout << "Step " << stepCounter++ << ": ";
                // getting ordinal no (3 as 3rd)
                cout << requiredOrdinalNumber(k) << " Ball is Removed; ";
                // adjusting backPtr to head of next
                backPtr->next = head->next;
                // incrementing head
                head = head->next;
                // reassign count as 1
                count = 1;
                // decrementing count
                size--;
                cout << "The remaining balls are: ";
                // printing the remaining balls after stepcounter steps
                balls.printBallsList();
                cout << "\n";
                // we have to show count start only for k-1 step
                if (size != 1)
                {

                    cout << "The count will start from " << requiredOrdinalNumber(head->value) << " ball." << endl;
                    cout << "\n";
                }
            }
            // otherWise just adjust head and backptr
            else
            {

                backPtr = head;
                head = head->next;
                count++;
            }
        }
        cout << endl;
    }
};

// a function that only computes the answer of the problem in recursive fashion
/*This code defines a function called "answer" that takes in two parameters: "noOfBalls" and "kPos". It uses a recursive approach to calculate a new value, which is returned by the function.

The function first checks if the number of balls (noOfBalls) is equal to 1. If it is, the function returns 1. If it is not, the function returns the result of the following calculation: (answer(noOfBalls - 1, kPos) + kPos - 1) % noOfBalls + 1. This calculation uses the recursive call of the function (answer(noOfBalls - 1, kPos)) as one of its inputs, and it also uses the value of kPos as an input. The calculation then uses the modulus operator (%), which gives the remainder of the division of the left-hand side by noOfBalls. The final result is incremented by 1.

It's not clear without more context what the code is trying to accomplish, but it appears to be an algorithm for solving a problem that involves counting balls and positions.*/
int answer(int noOfBalls, int kPos)
{
    if (noOfBalls == 1)
        return 1;
    else
        return (answer(noOfBalls - 1, kPos) + kPos - 1) % noOfBalls + 1;
}

// Main Function Starts Here
int main()

{
    // taking input n and k
    int n, k;
    cout << "Enter The Value of N: " << endl;
    cin >> n;
    cout << "Enter the Value of K: " << endl;
    cin >> k;
    cout << endl;

    // creating a circular linked list of balls
    ballsCLL balls;

    // adding nodes to the circular linked list
    for (int i = 1; i <= n; i++)
    {
        balls.insertIntoCircularSinglyList(i);
    }
    // calculating the answer
    int ans = answer(n, k);
    cout << "Given n = " << n << " and k = " << k << ", the safe position is " << ans << "." << endl;
    cout << "\n";
    cout << "Steps Are As Follows: " << endl;
    cout << "\n";
    // calling explainSteps Funtion to explain the code
    balls.explainSteps(balls, k);
    return 0;
}
// thank you so much

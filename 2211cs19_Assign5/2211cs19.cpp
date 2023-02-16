/**
 * @file 2211cs19.cpp
 * @brief This file contains the code for the problem of Assignment 5
 * @details This is a program to sort two linked lists using recursion and merge them into a single sorted linked list
 * @author [Krishna Kant Verma][2211cs19]
 * @see mergeSortLinkedListRecursive() function
 * @see sortedLinkedListMergeRecursive() function
 * @see findMiddle() function
 * @see createLinkedList() function
 * @see getLists() function
 * @see printList() function
 * @see main() function
 * @organisation [Indian Institute of Technology, Patna][https://www.iitp.ac.in/]
 * @date 2023-2-06
* /


/**
 * @brief C++ includes
 * */

#include <bits/stdc++.h>

/**
 * @brief using namespace as standard library
 */

using namespace std;

/**
 * @brief class for creating Linked List Node
 * @details contains two feilds data and nextPtr
 *
 */

class LinkedListNode
{
public:
    long long data;
    LinkedListNode *next;

    LinkedListNode(long long data)
    {
        this->data = data;
        this->next = NULL;
    }
};

/**
 * @brief function to merge two sorted linked lists
 * @details function to merge two sorted linked lists using recursion
 * @param first first linked list
 * @param second second linked list
 * @returns head of the merged linked list
 */
LinkedListNode *sortedLinkedListMergeRecursive(LinkedListNode *first, LinkedListNode *second)
{
    /**
     * @brief  first linked list is empty then return second linked list
     */
    if (first == NULL)
    {
        return second;
    }
    /**
     * @brief second linked list is empty then return first linked list
     */
    if (second == NULL)
    {
        return first;
    }
    /**
     *
     * @brief if first linked list data is less than or equal to second linked list data then first linked list data is stored in result and result->next is assigned to the result of the recursive call of sortedLinkedListMergeRecursive(first->next, second) and same is done for the second case
     */
    LinkedListNode *result = NULL;
    if (first->data <= second->data)
    {
        result = first;
        result->next = sortedLinkedListMergeRecursive(first->next, second);
    }
    else
    {
        result = second;
        result->next = sortedLinkedListMergeRecursive(first, second->next);
    }
    return result;
}

/**
 * @brief function to find middle of the linked list
 * @details function to find middle of the linked list using two pointers(fast and slow) moving at different speeds, fast moves two steps at a time and slow moves one step at a time
 * @param head head of the linked list
 * @returns middle of the linked list
 */
LinkedListNode *findMiddle(LinkedListNode *head)
{
    /**
     * @brief if head is NULL then return NULL
     */
    LinkedListNode *slow = head;
    LinkedListNode *fast = head->next;
    /**
     * @brief if fast is not NULL then move fast and slow by one and two steps respectively
     */
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
    return slow;
}

/**
 * @brief function to sort linked list using merge sort
 * @details function to sort linked list using merge sort using recursion, Splitting the linked list into two halves, sorting the two halves and merging them recursively.
 * @param head head of the linked list
 * @returns head of the sorted linked list
 */

LinkedListNode *mergeSortLinkedListRecursive(LinkedListNode *head)
{
    /**
     * @brief if head is NULL or head->next is NULL then return head
     */

    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    /**
     * @brief find middle of the linked list
     */

    LinkedListNode *slow = findMiddle(head);
    LinkedListNode *second = slow->next;
    slow->next = NULL;

    /**
     * @brief sort the two halves of the linked list recursively
     */

    LinkedListNode *first = mergeSortLinkedListRecursive(head);
    second = mergeSortLinkedListRecursive(second);

    /**
     * @brief merge the two sorted linked lists recursively
     */

    return sortedLinkedListMergeRecursive(first, second);
}

/**
 * @brief function to create linked list
 * @details function to create linked list by inserting elements at the end of the linked list and the data that is inserting into linked list can't me more the 10^18
 * @param head head of the linked list
 * @param data data to be inserted
 * @returns head of the linked list
 */

LinkedListNode *createLinkedList(LinkedListNode *&head, int data)
{
    /**
     * @brief if head is NULL then create a new node and assign it to head
     */
    LinkedListNode *newNode = new LinkedListNode(data);
    if (head == NULL)
    {
        head = newNode;
        return head;
    }
    /**
     * @brief if head is not NULL then traverse the linked list till the end and insert the new node at the end of the linked list
     */
    LinkedListNode *itr = head;
    while (itr->next != NULL)
    {
        itr = itr->next;
    }
    itr->next = newNode;
    /**
     * @brief return head of the linked list
     */
    return head;
}

/**
 * @brief function to get two linked lists from the input
 *  @details function to get two linked lists from the input, the input is in the form of string and the two linked lists are separated by # and the elements of the linked list are separated by ,. separate the two linked lists and store them in the firstList and secondList respectively
 * @param input input string
 * @param firstList first linked list
 * @param secondList second linked list
 * @returns void
 */
void getLists(string input, string &firstList, string &secondList)
{
    /**
     * @brief separate the two linked lists and store them in the firstList and secondList respectively
     */

    int i = 0;
    while (input[i] != '#')
    {
        firstList += input[i];
        i++;
    }
    i += 2;

    /**
     * @brief separate the two linked lists and store them in the firstList and secondList respectively
     */

    while (input[i] != '#')
    {
        secondList += input[i];
        i++;
    }
}

/**
 * @brief function to print the linked list
 * @details function to print the linked list, the elements of the linked list are separated by , and the linked list is enclosed in []
 * @param head head of the linked list
 * @returns void
 */

void printList(LinkedListNode *head)
{
    /**
     * @brief traverse the linked list and print the elements of the linked list separated by , and enclosed in []
     */

    LinkedListNode *itr = head;
    cout << "[";
    while (itr != NULL)
    {
        if (itr->next == NULL)
        {
            cout << itr->data;
        }
        else
        {
            cout << itr->data << ",";
        }
        itr = itr->next;
    }
    cout << "]" << endl;
}

/**
 * @brief main function
 * @details main function to test the above functions and to get the input from the user and print the output to the console.
 * @param void
 * @returns 0 on exit

*/
int main()
{
    /**
     * @brief get the input from the user
     */
    cout << "Enter Input(Format: number1,number2,#,number3,number4,#):";
    string input;
    cin >> input;
    string firstList = "";
    string secondList = "";

    /**
     * @brief separate the two linked lists and store them in the firstList and secondList respectively
     */

    getLists(input, firstList, secondList);

    /**
     * @brief create the two linked lists from the firstList and secondList respectively
     */

    LinkedListNode *head1 = NULL;
    LinkedListNode *head2 = NULL;
    string temp = "";

    /**
     * @brief create the two linked lists from the firstList and secondList respectively
     */

    for (int i = 0; i < firstList.length(); i++)
    {
        if (firstList[i] == ',')
        {
            int data = stoll(temp);
            createLinkedList(head1, data);
            temp = "";
            continue;
        }
        temp += firstList[i];
    }
    temp = "";

    for (int i = 0; i < secondList.length(); i++)
    {
        if (secondList[i] == ',')
        {
            int data = stoll(temp);
            createLinkedList(head2, data);
            temp = "";
            continue;
        }
        temp += secondList[i];
    }
    /**
     * @brief print the input linked lists
     */
    cout << "\n";
    cout << "Input List A: ";
    printList(head1);
    cout << "Input List B: ";
    printList(head2);

    /**
     * @brief sort the two linked lists and merge them
     */

    head1 = mergeSortLinkedListRecursive(head1);
    head2 = mergeSortLinkedListRecursive(head2);

    /**
     * @brief print the sorted linked lists
     */

    cout << "Sorted List A: ";
    printList(head1);
    cout << "Sorted List B: ";
    printList(head2);
    cout << "Merged Sorted List A: ";

    /**
     * @brief merge the two sorted linked lists
     */

    head1 = sortedLinkedListMergeRecursive(head1, head2);

    /**
     * @brief print the merged sorted linked list
     */

    printList(head1);
    return 0;
}
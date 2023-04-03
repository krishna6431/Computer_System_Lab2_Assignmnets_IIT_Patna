/// @author Krishna Kant Verma
/// @brief Program to Construct Binary Tree From File
// Assignment 7

/// @headerfile iostream for all input related issue
#include <iostream>
/// @brief using namespace as standard
using namespace std;

/**
 * @brief Structure to Create Node of the Tree
 * @details It has 5 member data
 * data : data
 * leftPtr : Pointer to Left Child
 * rightPtr : Pointer to Right Child
 * hasLeftChild : whether node has left child
 * hasRightChild : whether node has right child
 */

struct TreeNode
{
    int data;
    int hasLeftChild;
    int hasRightChild;
    TreeNode *leftPtr;
    TreeNode *rightPtr;

    /// @brief Constructor to Initialize value
    /// @param val
    /// @param l
    /// @param r
    TreeNode(int val, int l, int r)
        : data(val), leftPtr(nullptr), rightPtr(nullptr), hasRightChild(r), hasLeftChild(l)
    {
    }
};

/**
 * @brief Structure to Create Node For Queue
 * @details It has 2 member data
 * address : contains address for TreeNode
 * next : Pointer to next of QueueNode
 */

struct ListNode
{
    TreeNode *address;
    ListNode *next;

    /// @brief  COnstructor to Initialize values
    /// @param address
    /// @param next
    ListNode(TreeNode *address, ListNode *next)
    {
        this->address = address;
        this->next = next;
    }
};

/**
 * @brief Structure to Create Queue
 * @details It has 2 data member and 3 methods
 * Front : pointing front of queue
 * rear : pointing rear of queue
 */
struct Queue
{
    /// @brief front and rear pointer
    ListNode *front = NULL;
    ListNode *rear = NULL;

    /// @brief checks whether queue is empty
    /// @return True / False (queue empty / queue not empty)
    bool isEmpty()
    {
        if (front == NULL && rear == NULL)
            return true;
        else
            return false;
    }

    /// @brief method used to push treenode into queue
    /// @param TreeNode
    void enQueue(TreeNode *TreeNode)
    {
        ListNode *newTreeNode = new ListNode(TreeNode, NULL);

        ///@brief if pushing first node
        if (front == NULL)
        {
            front = newTreeNode;
            rear = newTreeNode;
        }
        else
        {
            rear->next = newTreeNode;
            rear = newTreeNode;
        }
    }

    /// @brief method used to pop Node from queue
    /// @return Pointer to the Node which is Popped from Queue
    TreeNode *deQueue()
    {
        TreeNode *returnTreeNode = NULL;

        /// @brief is queue is empty()
        if (isEmpty())
            cout << "Queue is empty\n";
        else
        {
            if (front == rear)
            {
                returnTreeNode = front->address;
                front = rear = NULL;
            }
            else
            {
                returnTreeNode = front->address;
                front = front->next;
            }
        }
        /// @return Node which is popped
        return returnTreeNode;
    }
};

/// @brief Function to construct Binary Tree From the file
/// @return root Node of the Tree
TreeNode *constructBinaryTreeFromFile()
{
    /// @brief taking input root Node (First Node of the Tree)
    int data, hasLeftChild, hasRightChild;
    cin >> data >> hasLeftChild >> hasRightChild;
    TreeNode *root = new TreeNode(data, hasLeftChild, hasRightChild);

    ///@brief inserting it to queue
    Queue q;
    q.enQueue(root);

    ///@brief run till queue is not empty()
    while (!q.isEmpty())
    {
        ///@brief getting node from the queue
        TreeNode *curr = q.deQueue();
        cout << curr->data << " " << curr->hasLeftChild << " " << curr->hasRightChild << endl;

        /// @brief if current node has left child
        if (curr->hasLeftChild)
        {
            cin >> data >> hasLeftChild >> hasRightChild;
            TreeNode *newTreeNode = new TreeNode(data, hasLeftChild, hasRightChild);
            curr->leftPtr = newTreeNode;
            q.enQueue(newTreeNode);
        }
        // @brief if current node has rightchild
        if (curr->hasRightChild)
        {
            cin >> data >> hasLeftChild >> hasRightChild;
            TreeNode *newTreeNode = new TreeNode(data, hasLeftChild, hasRightChild);
            curr->rightPtr = newTreeNode;
            q.enQueue(newTreeNode);
        }
    }
    // returning root of the Tree
    return root;
}

/// @brief function to compute height of the tree
/// @param  TreeNode the root of the tree
/// @return height of of the tree
int height(TreeNode *root)
{
    if (root == NULL)
        return 0;
    // finding left height
    int lh = height(root->leftPtr);
    // finding right height
    int rh = height(root->rightPtr);
    if (lh >= rh)
        return 1 + lh;
    else
        return 1 + rh;
}

/// @brief function to tilt binary tree
void makeTiltedBinaryTree(TreeNode *root)
{
    if (root == NULL)
        return;

    // recursivly call on both left and right of tree
    makeTiltedBinaryTree(root->leftPtr);
    makeTiltedBinaryTree(root->rightPtr);
    // compute height of left and right subtree
    int lh = height(root->leftPtr);
    int rh = height(root->rightPtr);
    // if condition satisfied swap pointers
    if (rh > lh)
    {
        TreeNode *temp = root->rightPtr;
        root->rightPtr = root->leftPtr;
        root->leftPtr = temp;
    }
}

/// @brief Function to print PreOrder
/// @param root
void preOrder(TreeNode *root)
{
    if (root == NULL)
        return;
    cout << root->data << " ";
    preOrder(root->leftPtr);
    preOrder(root->rightPtr);
}

/// @brief Function to Print inorder
/// @param root
void inOrder(TreeNode *root)
{
    if (root == NULL)
        return;
    inOrder(root->leftPtr);
    cout << root->data << " ";
    inOrder(root->rightPtr);
}

/// @brief function to print postorder
/// @param root
void postOrder(TreeNode *root)
{
    if (root == NULL)
        return;
    postOrder(root->leftPtr);
    postOrder(root->rightPtr);
    cout << root->data << " ";
}

int main()
{
    freopen("ip.txt", "r", stdin);
    freopen("op.txt", "w", stdout);
    cout << "Input Tree" << endl;
    cout << "*************" << endl;
    TreeNode *root = constructBinaryTreeFromFile();
    cout << "*************" << endl;
    if (root)
    {
        cout << "Binary tree constructed successfully!" << endl;
        cout << "\n";
        cout << "Printing preOrder Traversal" << endl;
        preOrder(root);
        cout << endl;
        cout << "\n";
        cout << "Printing inOrder Traversal" << endl;
        inOrder(root);
        cout << "\n";
        cout << endl;
        cout << "Printing postOrder Traversal" << endl;
        postOrder(root);
        cout << endl;
        cout << endl;
        cout << "Tilting Binary Tree" << endl;
        makeTiltedBinaryTree(root);
        cout << endl;
        cout << "Printing preOrder Traversal" << endl;
        preOrder(root);
        cout << endl;
        cout << "\n";
        cout << "Printing inOrder Traversal" << endl;
        inOrder(root);
        cout << "\n";
        cout << endl;
        cout << "Printing postOrder Traversal" << endl;
        postOrder(root);
        cout << endl;
    }
    else
    {
        cout << "Failed to construct binary tree." << endl;
    }
    return 0;
}

/**
The time complexity of this program mainly depends on the number of nodes in the binary tree.

The constructBinaryTreeFromFile() function has a time complexity of O(n), where n is the number of nodes in the binary tree. This is because the function reads the values of each node and enqueues them in a queue. Each node is enqueued once and dequeued once, so the total number of enqueue and dequeue operations is 2n, which gives a time complexity of O(n).

The time complexity of the preOrder(), inOrder(), and postOrder() functions is also O(n) since each node is visited only once.

In addition to the time complexity, there is also space complexity to consider. The space complexity of this program is O(n) since we are using a queue to construct the tree and the size of the queue is proportional to the number of nodes in the binary tree.

OverAll Asymptotic Analysis = O(N)
Space Complexity = O(N)
 */

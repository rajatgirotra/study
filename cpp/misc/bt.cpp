#include "bt.h"
#include <iostream>
#include <queue>
#include <limits>
using std::cout;
using std::endl;
using std::queue;

node* build123()
{
    node* root = new node(2);
    root->left = new node(1);
    root->right = new node(3);
    root->left->parent = root->right->parent = root;
    return root;
}

//iterative version - Find a node in a BST.
bool lookup(node* root, int item, node** nodePtr)
{
    bool bFound = false;
    while(root != 0)
    {
        if(root->data == item)
        {
            bFound = true;
            *nodePtr = root;
            break;
        }
        root = ((root->data > item) ? (root->left) : (root->right));
    }
    return bFound;
}

//recursive version. insert a node in a BST.
node* insert(node* root, int item)
{
    if(root == 0)
        return (new node(item));
    else if(item > root->data)
    {
        root->right = insert(root->right, item);
        root->right->parent = root;
    }
    else
    {
        root->left = insert(root->left, item);
        root->left->parent = root;
    }
    return root;
}

int size(node* root)
{
    if(root == 0)
        return 0;
    else
    {
        return (size(root->left) + 1 + size(root->right));
    }
}

//no of nodes along the largest path from root to any leaf.
int maxDepth(node* root)
{
    if(root == 0)
        return 0;
    else
    {
        int lDepth = maxDepth(root->left); 
        int rDepth = maxDepth(root->right); 
        return ((lDepth>rDepth) ? (lDepth + 1) : (rDepth + 1));
    }
}
    
int minDepth(node* root)
{
    if(root == 0)
        return 0;
    else
    {
        int lDepth = minDepth(root->left); 
        int rDepth = minDepth(root->right); 
        return ((lDepth>rDepth) ? (rDepth + 1) : (lDepth + 1));
    }
}

int height(node* root)
{
    if(root == 0)
        return -1;
    else
    {
        int lHeight = height(root->left);
        int rHeight = height(root->right);
        return ((lHeight > rHeight) ? (lHeight + 1) : (rHeight + 1));
    }
}

bool minValue(node* root, int& min)
{
    if(root == 0)
    {
        return false;
    }
    while(root->left != 0)
        root = root->left;
    min = root->data;
    return true;
}

int minValue(node* root)
{
    if(root == 0)
    {
        return -1;
    }
    while(root->left != 0)
        root = root->left;
    return root->data;
}

int maxValue(node* root)
{
    if(root == 0)
    {
        return -1;
    }
    while(root->right != 0)
        root = root->right;
    return root->data;
}

void inOrder(node* root)
{
    if(root != 0)
    {
        inOrder(root->left);
        cout << root->data << "   ";
        inOrder(root->right);
    }
}

void preOrder(node* root)
{
    if(root != 0)
    {
        cout << root->data << "  ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(node* root)
{
    if(root != 0)
    {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->data << "  ";
    }
}

void levelOrder(node* root)
{
    if(root == 0)
        return;
    std::queue<node*> nodeQ;
    nodeQ.push(root);
    while(!nodeQ.empty())
    {
        node* tmp = nodeQ.front();
        nodeQ.pop();
        cout << tmp->data << "  ";
        if(tmp->left)
            nodeQ.push(tmp->left);
        if(tmp->right)
            nodeQ.push(tmp->right);
    }
    cout << endl;
}

void mirror(node* root)
{
    if(root == 0)
        return;
    else
    {
        mirror(root->left);
        mirror(root->right);
        node* tmp = root->left;
        root->left = root->right;
        root->right = tmp;
        //Parent will not change, so no need to change the parent pointer.
    }
}

void doubleTree(node* root)
{
    if(root == 0)
        return;
    else
    {
        doubleTree(root->left);
        doubleTree(root->right);
        node* newNode = new node(root->data);
        newNode->left = root->left;
        if(newNode->left != 0)
            newNode->left->parent = newNode;
        root->left = newNode;
        root->left->parent = root;
    }
}

void print(int arr[], int length)
{
    cout << "Path: "; 
    for(int i = 0; i < length; ++i)
        cout << arr[i] << "  "; 
    cout << endl;
}

void printPathsRecursive(node* root, int arr[], int length)
{
    if(root == 0)
        return;
    arr[length++] = root->data;

    if(root->left == 0 && root->right == 0)
    {
        print(arr, length);
    }
    else
    {
        printPathsRecursive(root->left, arr, length);
        printPathsRecursive(root->right, arr, length);
    }
}
    

void printPaths(node* root)
{
    int arr[100];
    printPathsRecursive(root, arr, 0);
}

bool hasPathSum(node* root, int sum)
{
    if(root == 0)
        return (sum == 0);
    else
    {
        int subSum = sum - root->data;
        return ((hasPathSum(root->left, subSum)) || (hasPathSum(root->right, subSum)));
    }
}

bool sameTree(node* a, node* b)
{
    if( (a == 0) && (b == 0))
        return true;
    else if( (a!=0) && (b!=0))
    {
        return ( (a->data == b->data) &&
                 sameTree(a->left, b->left) &&
                 sameTree(a->right, b->right) );
    }
    else
        return false;
}

int countTrees(int numKeys)
{
    if(numKeys <= 1)
        return 1;
    else
    {
        int sum = 0, left, right;
        for(int currentRoot = 1; currentRoot <= numKeys; ++currentRoot)
        {
            left = countTrees(currentRoot - 1);
            right = countTrees(numKeys - currentRoot);
            sum += (left * right);
        }
        return sum;
    }
}
 

bool isBSTHelper(node* root, int lb, int ub)
{
    if(root == 0)
        return true;
    if( (root->data >= lb) && (root->data <= ub))
    {
        return ( (isBSTHelper(root->left, lb, root->data)) &&
                 (isBSTHelper(root->right, root->data + 1, ub)) );
    }
    else
        return false;
}

bool isBST(node* root)
{
    if (root == 0)
        return false;
    else
        return isBSTHelper(root, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
}

bool isBalanced(node* root)
{
    return ((maxDepth(root) - minDepth(root)) <= 1);
}

node* minValueNode(node* root)
{
    if(root == 0)
        return 0;
    while(root->left != 0)
        root = root->left;
    return root;
}

node* successor(node* root, int data)
{
    //First check if we have data in our BT. and get a pointer to that node.
    node* nodePtr = 0;
    if(lookup(root, data, &nodePtr) == false)
    {
        cout << "No node found with value: " << data << endl;
        return nodePtr;
    }

    //ok to get the successor get the minimum value from the right sub tree.
    if(nodePtr->right != 0)
        return minValueNode(nodePtr->right);
    else
    {
        node* parent = nodePtr->parent;
        while( (parent != 0) && (parent->right == nodePtr))
        {
            nodePtr = parent;
            parent = nodePtr->parent;
        }
        return parent;
    }
}

node* deleteNode(node* root, int data, int* deletedItem)
{
    node* z;
    if(lookup(root, data, &z) == 0)
    {
        cout << "Node with value " << data << " not found." << endl;
        return 0;
    }
    // Does this node have 2 two children.
    node* y;
    if((z->left == 0)  || (z->right == 0))
        y = z;
    else
        y = successor(z, z->data);

    node* x = 0;
    if(y->left != 0)
        x = y->left;
    else
        x = y->right;

    if(x != 0)
        x->parent = y->parent;

    if(y->parent == 0)
    {
        root = x; //new root;
    }
    else if(y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x ;

    if( y != z )
    {  
        *deletedItem = z->data;
        z->data = y->data;
    }
    else
        *deletedItem = y->data;

    delete y;
    return root;
}

    
    


#include "bt.h"
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    node* root = build123();
    inOrder(root);
    cout << endl;

    node* nodePtr;
    cout << "lookup(3): " << boolalpha << lookup(root, 3, &nodePtr) << endl;
    root = insert(root, 5);
    preOrder(root);
    cout << endl;

    cout << "Size: " << size(root) << endl;
    cout << "MaxDepth: " << maxDepth(root) << endl;
    int item;
    minValue(root, item);
    cout << "Minvalue: " << item << endl;

    cout << "Level Order: " ;
    levelOrder(root);

    cout << "Height: " << height(root) << endl;
    cout << "MinDepth: " << minDepth(root) << endl;

    cout << "Mirroring" << endl;
    mirror(root);
    cout << "Inorder: " << endl;
    inOrder(root);
    cout << endl;
    cout << "isBalanced(): " << isBalanced(root) << endl;
    cout << "DoubleTreeing" << endl;
    doubleTree(root);
    cout << "Preorder: " << endl;
    preOrder(root);
    cout << endl;
    cout << "isBalanced(): " << isBalanced(root) << endl;

    cout << "Printing all paths: \n";
    printPaths(root);

    cout << "hasPathSum(20): " << boolalpha << hasPathSum(root, 20) << endl;

    node* a = build123();
    node* b = build123();
    //b = insert(b, 10);
    cout << "sameTree(a, b): " << boolalpha << sameTree(a, b) << endl;

    cout << "countTrees(3): " << countTrees(3) << endl;

    node* x = insert((node*)0, 5);
    x->left = new node(6);
    cout << "isBST(nullTree): " << boolalpha << isBST(x) << endl;

    node* suc = insert((node*)0, 100);
    suc = insert(suc, 50);
    suc = insert(suc, 30);
    suc = insert(suc, 70);
    suc = insert(suc, 200);
    nodePtr = successor(suc, 1000);
    if(!nodePtr)
        cout << "value 1000 not found" << endl;
    nodePtr = successor(suc, 50);
    if(nodePtr)
        cout << "sucessor value of 50 is: " << nodePtr->data << endl;
    nodePtr = successor(suc, 200);
    if(!nodePtr)
        cout << "value 200 does not have a successor" << endl;
    nodePtr = successor(suc, 70);
    if(nodePtr)
        cout << "sucessor value of 70 is: " << nodePtr->data << endl;

    node* nodeTest = insert((node*)0, 15);
    nodeTest = insert(nodeTest, 5);
    nodeTest = insert(nodeTest, 3);
    nodeTest = insert(nodeTest, 12);
    nodeTest = insert(nodeTest, 10);
    nodeTest = insert(nodeTest, 6);
    nodeTest = insert(nodeTest, 7);
    nodeTest = insert(nodeTest, 13);
    nodeTest = insert(nodeTest, 16);
    nodeTest = insert(nodeTest, 20);
    nodeTest = insert(nodeTest, 18);
    nodeTest = insert(nodeTest, 23);
    inOrder(nodeTest);
    cout << endl;

    int deletedItem;
    // Node with no children.
    nodeTest = deleteNode(nodeTest, 13, &deletedItem);
    cout << "Node with value: " << deletedItem << " deleted" << endl;
    //Node with 1 child
    nodeTest = deleteNode(nodeTest, 16, &deletedItem);
    cout << "Node with value: " << deletedItem << " deleted" << endl;
    //Node with 2 children
    nodeTest = deleteNode(nodeTest, 5, &deletedItem);
    cout << "Node with value: " << deletedItem << " deleted" << endl;
    inOrder(nodeTest);
    cout << endl;

    return 0;
}

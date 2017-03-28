#ifndef _BT_H_
#define _BT_H_ 

struct node
{
    int data;
    node* left;
    node* right;
    node* parent;

    node(const int& pData) : data(pData), left(0), right(0), parent(0)
    {}
};

//API's

node* build123();
bool lookup(node* root, int item, node** nodePtr);
node* insert(node* root, int item);
int size(node* root); //number of nodes in the tree
int maxDepth(node* root); //no of nodes along the largest path from root to any leaf.
int minDepth(node* root); //no of nodes along the smallest path from root to any leaf.
int height(node* root);
bool minValue(node* root, int& item);

void printPaths(node* root);
bool hasPathSum(node* root, int sum);

void inOrder(node* root);
void preOrder(node* root);
void postOrder(node* root);
void levelOrder(node* root);

void mirror(node* root);
void doubleTree(node* root);

bool sameTree(node* a, node* b);

int countTrees(int numKeys);

bool isBST(node* root);
bool isBalanced(node* root);

node* successor(node* root, int data);

//Return the new root, and the value deleted is in the last parameter.
node* deleteNode(node* root, int data, int*);

#endif // _BT_H_

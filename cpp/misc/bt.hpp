#ifndef _BT_HPP_
#define _BT_HPP_ 1

#include <algorithm>
#include <boost/noncopyable.hpp>
#include <iostream>
#include <deque>
#include <string>

using std::ostream;
using std::deque;
using std::string;

template <typename T, typename KeyCompare = std::less<T> >
class BinaryTree : boost::noncopyable
{
    public:
        typedef T value_type;
        struct node
        {
            typedef node node_type;
            value_type value;
            node_type* parent;
            node_type* left_child;
            node_type* right_child;

            node(const T& pData);
        };

        //Function to create a new node.
        static node* createNode(const T& pData = T());

        //Binary tree root.
        node* _root;

        //helper classes
        void inOrderHelper(const node*) const;
        void preOrderHelper(const node*) const;
        void postOrderHelper(const node*) const;
        node* insertRecursiveHelper(node* head, const T& pData);
        size_t sizeHelper(const node*) const;
        size_t maxDepthHelper(const node*) const;
        int heightHelper(const node*) const;
        bool hasPathSumHelper(const node*, const T& sum) const;
        void printPathsHelper(const T array[], const size_t& length) const;
        void findPaths(const node*, T array[], size_t length) const;
        void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<node*>& nodesQueue, ostream& out) const;
        void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<node*>& nodesQueue, ostream& out) const;
        void printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<node*>& nodesQueue, ostream& out) const;
        string toString(const T&) const;
        void mirrorTreeHelper(node*);
        void doubleTreeHelper(node*);
        bool isBalanced(const node* nodePtr, int& lrHeight) const;
    public:
        BinaryTree();
        virtual ~BinaryTree();

        //is tree empty
        bool isEmpty() const {return (_root == nullptr); }

        //insert a node in the tree iteratively.
        void insertIterative(const T& pData);
        //insert a node in the tree recursively.
        void insertRecursive(const T& pData);

        //print in-order
        void printInOrder() const;
        //print pre-order
        void printPreOrder() const;
        //print post-order
        void printPostOrder() const;

        //build123
        void build123();
        //return the number of nodes in the tree;
        size_t size() const;
        //maxinum number of nodes down from the root to the farthest leaf.
        size_t maxDepth() const;
        // min value in the tree: this will be the value of the left most node.
        T minValue() const;
        //height of the tree.
        int height() const;
        //has Path Sum
        bool hasPathSum(const T& sum) const;
        //print all paths from root to leaves
        void printPaths() const;
        //pretty print
        void prettyPrint(int level, int indentSpace, ostream& out) const;
        //mirror
        void mirrorTree();
        //double
        void doubleTree();
        //lookup a value in the Binary tree and return a pointer to it.
        const node* lookup(const T& value) const;
        //Tree successor
        bool treeSuccessor(const T& value, T& successorValue, node*& successorNode) const;
        //delete node
        bool deleteNode(const T& value);
        //is balanced??
        bool isBalanced() const;
};

#endif // _BT_HPP_

/* Let now write a lock free stack implementation.
 * We'll implement this using a linked list. You ask Why. Try creating a fixed size array and using it as a stack.
 * You'll realise that you'll run into data races. So we use a linked list.
 */

#include <iostream>
#include <atomic>
#include <thread>
#include <exception>
#include <random>
#include <chrono>
using namespace std;

template <typename T>
class Stack
{
    private:
        struct Node
        {
            T data;
            Node* next;

            Node(const T& pData) : data(pData), next(nullptr)
            {};
        };

        static Node* createNode(const T& pData);

        std::atomic<Node*> head;

   public:
       Stack();

       void push(const T& pData);
 
       T pop();

       int getCount() const
       {
           int count = 0;
           Node* poTmp = head.load();
           while(poTmp != nullptr)
           {
               ++count;
		poTmp = poTmp->next;
           }
           return count;
       }

};

template <typename T>
inline
Stack<T>::Stack() : head(nullptr)
{
}

template <typename T>
inline
void Stack<T>::push(const T& pData)
{
    //Create a new node first
    Node* newNode = createNode(pData);
    //Repeatedly try to insert unless you hit success.
    Node* poHead {};
    do
    {
        poHead = head.load(memory_order_acquire);
        newNode->next = poHead;
        std::this_thread::yield();
    } while(head.compare_exchange_strong(poHead, newNode, memory_order_release) == false);
}

template <typename T>
inline
T Stack<T>::pop()
{
    Node* topNode {};
    Node* newHead {};
    do 
    {
        topNode = head.load(memory_order_acquire);
        if(topNode == nullptr)
            throw std::underflow_error("Stack Empty\n");
        newHead = topNode->next;
        std::this_thread::yield();
    } while(head.compare_exchange_strong(topNode, newHead, memory_order_release) == false);
    return topNode->data;
}

template <typename T>
inline
typename Stack<T>::Node* Stack<T>::createNode(const T& pData)
{
    return (new Node(pData));
}

Stack<int> intStack;

void fillThread()
{
    std::default_random_engine generator (std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(1, 100);

    for(int i = 0; i < 1000000; ++i)
        intStack.push(distribution(generator));
}

void emptyThread()
{
    for(int i = 0; i < 1000000; ++i)
    {
        try {
            intStack.pop();
        }
        catch(const std::underflow_error& e)
        {
            cout << e.what();
        }
    }
}
    
        
int main()
{
    std::thread ft1(fillThread);
    std::thread ft2(fillThread);

    std::thread et1(emptyThread);
    std::thread et2(emptyThread);

    ft1.join(); ft2.join();
    et1.join(); et2.join();

    cout << "count: " << intStack.getCount() << endl;
    return 0;
}

/*
 * Stack Empty will be printed as many times as the number of entries remaining in the stack.
 * i.e. same as what getCount returns
 */

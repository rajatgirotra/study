Lets write high level Objects and API

InputOrder
   orderid;
   price; // 6.4 fixed point representation
   volume; // size
   side; // BUY/SELL
   participantId;


Order object in Limit Order Book
   orderid;
   price;
   volume;
   side;
   int entryTime;
   Order* next;
   Order* prev;
   Limit* parentLimit; // pointer to the LimitPrice of for this order.
  

Limit
   int limitprice; // 6.4 
   int size;
   int totalVolume; 
   Limit* parent;
   Limit* leftChild;
   Limit* rightChild;
   Order* headOrder;
   Order* tailOrder;

Book:
   Limit* buyTree;
   Limit* sellTree;
   Limit* lowestSell;
   Limit* highestBuy;

The idea is to have a balanced binary tree (BST/RBTree) of Limit Objects sorted by LimitPrice, where each node itself is a doubly linked list of Order Objects.  i.e. an std::map<int, std::deque<Order>> should be good. std::map is based on RBTree and deque is based on doubly linked list.

We can have an std::unordered_map<int, Order*> which gives us a mapping of OrderId to Orders. With these data structures, we can have the following run time complexities.
and an unordered_map<int, Limit>

AddOrder --> O(lg M) for first order at Limit, O(1) for all others.
CancelOrder --> O(1)
Execute --> O(1)
GetVolumeAtLimit --> O(1)
GetBestBid/Offer (BBO) --> O(1)

So we will start off by writing an InputOrder class which will have
orderid
product
size
volume
side
participantid

Next we will create a Order class, which will have
orderid
size
volume
side
entrytime
PriceLevel reference (either pointer or reference)

Create an enum for Side - Buy or Sell

Next we will create a PriceLevelManager class which will manage the LimitPrice data structure above.
template <typename T, typename U>
class PriceLevelManager; 
type T will define the implementation of creating price levels, iterating through them, adding/deleting/modifying orders at price level.
type U will have information like the price level, the deque of Orders at this price level, the total size and volume at this price level.


Create a Book class which will have a template parameter T which could be a simple type Bid or Ask, to designate if the Book is a buy or sell book.

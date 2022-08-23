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

The template parameter U above in PriceLevelManager should be a simple class (let say PriceLevel) with
1) total size (count of orders)
2) total volume (volume of orders)
3) std::deque<Orders>
API
getSize()
getVolume()
addOrder()
removeOrder()
iterator over the orders.
this particular price point

the template parameter T in PriceLevelManager is used to move through the price levels.
We can have a simple class which wraps a map<int64_t (priceLevel), sp<PriceLevel>
or a class which uses veb data structure for better performance.
API()
1) insert(priceLevel)
2) remove(priceLevel)
3) successor(priceLevel)
4) predecessor(priceLevel)
5) find(priceLevel)
6) minPrice()
7) maxPrice()

PriceLevelManager will have template parameters T and U and API would be like
addBucket()
removeBucket()
minPrice()
maxPrice()
findBucket()
prevBucket()
nextBucket()
iterator class. --> for buy book, must iterate in increasing order, for sell bucket must iterate in decreasing order.
Basically the operations in the iterator class like ++, ++(postfix), --, --(postfix), * (dereference), must be templated for Buy and Sell types.
The equal function doesnt need to be templated.
The ctor of this iterator must set the initial price to minPrice() for sellbook, and maxPrice() for buybook.
begin() and end() for iterators


LOB:
a) addOrder
b) removeOrder
c) volumeForPricePoint()
d) besBid()
e) bestOffer()
f) bids_begin(), end()
g) ask_begin(), end()
h) iterator class
i) isBookCrossed()
j) matchOrders()
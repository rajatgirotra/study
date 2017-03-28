The code for OrderManager is in the problem1 directory.
The main classes are

1) OrderManager.cpp - To send orders to the exchange.
2) OrderProcessor.cpp - To process callbacks received by OrderManager
3) Order.cpp - Maintains the orderID and the order state.
4) OrderStateMachine.cpp - Based on BOOST MSM. Includes a transition table and is responsible for Order state transitions.


Testing: For testing a MockExchange implementation is provided in the test folder.
-------

There are two ways you can test it.

1) Automatically using google test.
To compile & run using google test, do:

[rajatgirotra@osboxes problem1]$ echo $GTEST_DIR 
/home/rajatgirotra/tools/gtest-1.7.0
[rajatgirotra@osboxes problem1]$ g++ -pthread --std=c++11 -I /home/rajatgirotra/tools/boost_1_57_0/include -I ${GTEST_DIR}/include test/MockExchange.cpp test/test.cpp *.cpp -L ${GTEST_DIR}/lib -lgtest
[rajatgirotra@osboxes problem1]$ ./a.out 


2) Manually using command line interface - Uses the same MockExchange implementation.
To test manually do:

[rajatgirotra@osboxes problem1]$ g++ -pthread --std=c++11 -I /home/rajatgirotra/tools/boost_1_57_0/include  test/MockExchange.cpp test/main.cpp *.cpp
[rajatgirotra@osboxes problem1]$ ./a.out 


**********   OrderManager    **************
1) Create New Order
2) Amend order     
3) Cancel order    
4) View order state

Choose your option (1-4), Control+C to exit: 1
Security: IBM
Price: 1
Volume: 1
Buy/Sell (0 for Buy, 1 for Sell): 0
onOrderInsert called for orderId: 111111, ErrorCode: 0
OrderId 111111 inserted. state is ACTIVE.


**********   OrderManager    **************
1) Create New Order
2) Amend order     
3) Cancel order    
4) View order state

Choose your option (1-4), Control+C to exit: 3
OrderId: 111111
onOrderCancel called for orderId: 111111, ErrorCode: 0
Changed order id 111111 state to CANCELLED


**********   OrderManager    **************
1) Create New Order
2) Amend order     
3) Cancel order    
4) View order state

Choose your option (1-4), Control+C to exit: 4
OrderId: 111111
Orderid 111111, State is CANCELLED
^C


#include "MockExchange.hpp"
#include "../OrderManager.hpp"
#include <chrono>
#include <thread>
#include <iostream>

using exchange::MockExchange;
using namespace order_manager;
using std::cout;
using std::cin;
using std::endl;

void sendNewOrder(const std::shared_ptr<OrderManager>& omPtr)
{
    std::string securityId;
    double price;
    double volume;
    int buySell;
    Side side;
    cout << "Security: "; cin >> securityId;
    cout << "Price: "; cin >> price;
    cout << "Volume: "; cin >> volume;
    cout << "Buy/Sell (0 for Buy, 1 for Sell): "; cin >> buySell;
    if((buySell != 0) && (buySell != 1))
    {
        cout <<"Invalid side..\n";
        return;
    }

    side = (buySell == 0 ? Side::BUY : Side::SELL);
    omPtr->insertOrder(securityId, price, volume, side);
}

void amendOrder(const std::shared_ptr<OrderManager>& omPtr)
{
    int orderId; double newVolume;
    cout << "OrderId: "; cin >> orderId;
    cout << "NewVolume: "; cin >> newVolume;
    omPtr->amendOrder(orderId, newVolume);
}

void cancelOrder(const std::shared_ptr<OrderManager>& omPtr)
{
    int orderId;
    cout << "OrderId: "; cin >> orderId;
    omPtr->cancelOrder(orderId);
}

Order::State getOrderState(const std::shared_ptr<OrderManager>& omPtr)
{
    int orderId;
    cout << "OrderId: "; cin >> orderId;
    return omPtr->getOrderState(orderId);
}

int main()
{
    //Create a mock exchange object.
    MockExchange me;

    //Create our orderManager 
    std::shared_ptr<OrderManager> omPtr = OrderManager::create(me);

    //Lets present our MENU now.

    int option;
    do
    {
        cout << "\n\n**********   OrderManager    **************\n"
             << "1) Create New Order\n"
             << "2) Amend order     \n"
             << "3) Cancel order    \n"
             << "4) View order state\n"
             << "\nChoose your option (1-4), Control+C to exit: ";
        cin >> option;

        switch(option)
        {
            case 1: sendNewOrder(omPtr); break;
            case 2: amendOrder(omPtr); break;
            case 3: cancelOrder(omPtr); break;
            case 4: getOrderState(omPtr); break;
            default: "Invalid Option. Quiting.. "; return -1;
        }
        
        //Pause a while so as not to garble output to cout.
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }while(true);

    return 0;
}


#ifndef _ENUMS_HPP_INCLUDED_
#define _ENUMS_HPP_INCLUDED_

enum class Side
{
    BUY,
    SELL
};

enum class ErrorCode
{
    //No Error
    OK,
    //Limit reached on the number of orders for this security
    TOO_MANY_ORDERS,
    //Unknown security
    UNKNOWN_SECURITY,
    //orderId unknown
    UNKNOWN_ORDER,
    //Invalid arguments
    INVALID_ARGUMENTS
};

#endif // _ENUMS_HPP_INCLUDED_

#ifndef _ORDER_EVENTS_HPP_INCLUDED_
#define _ORDER_EVENTS_HPP_INCLUDED_

namespace order_manager
{
    //Events that trigger change of Order state.
    struct order_inserted {};
    struct order_amended {};
    struct order_cancelled {};
};

#endif // _ORDER_EVENTS_HPP_INCLUDED_

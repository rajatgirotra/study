#ifndef _ORDER_STATE_MACHINE_HPP_INCLUDED_
#define _ORDER_STATE_MACHINE_HPP_INCLUDED_

#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/back/state_machine.hpp>
#include <boost/mpl/vector.hpp>
#include "OrderEvents.hpp"
#include <memory>
#include <iostream>

namespace msm = boost::msm;
namespace mpl = boost::mpl;

using std::cerr;
using std::endl;

#define CREATE_NEW_STATE(_STATE_NAME_) \
struct _STATE_NAME_ : public msm::front::state<>\
{\
    template <typename Event, typename FSM>\
    void on_entry(const Event& event, const FSM& fsm)\
    {}\
    \
    template <typename Event, typename FSM>\
    void on_exit(const Event& event, const FSM& fsm)\
    {}\
};



namespace order_manager {
    class Order;
    struct OrderStateMachine_ : public msm::front::state_machine_def<OrderStateMachine_>
    {
            //A pointer to the Order this state machine is handling
            const Order* m_parent;

            //Ctor & Dtor
            OrderStateMachine_(const Order* poOrder);
            ~OrderStateMachine_();

            template<typename Event, typename FSM>
            void on_entry(const Event& event, const FSM& fsm){} 
            template<typename Event, typename FSM>
            void on_exit(const Event& event, const FSM& fsm){}

            //State definitions
            CREATE_NEW_STATE(Active) //This state is activated after order ACK is received from IExchange.
            CREATE_NEW_STATE(Amended)
            CREATE_NEW_STATE(Cancelled)

            //Initial state
            typedef Active initial_state;

            //actions/guards
            void onAmend(const order_amended&);
            void onCancel(const order_cancelled&);

            //Transition table
            struct transition_table : public mpl::vector <
          //------------- Start----------- Event---------------- Target--------------- Action---------------------------- Guard-----------------
          a_row<      Active,           order_amended,           Amended,      &OrderStateMachine_::onAmend                                    >,
          a_row<      Active,           order_cancelled,         Cancelled,    &OrderStateMachine_::onCancel                                   >,
          //------------- Start----------- Event---------------- Target--------------- Action---------------------------- Guard-----------------
          a_irow<     Amended,         order_amended,                         &OrderStateMachine_::onAmend                                     >,
          a_row<      Amended,         order_cancelled,          Cancelled,   &OrderStateMachine_::onCancel                                    >
          > {}; //end of transition_table

          //Catch all for all other transitions
          template <typename Event, typename FSM>
          void no_transition(const Event& event, const FSM& fsm, int state)
          {
              cerr << "Invalid command.  No Transition defined from state " << state << " on event: " << typeid(event).name();
          }

    };

    //Define the backend
    typedef msm::back::state_machine<OrderStateMachine_> OrderStateMachine;
}// end of namespace order_manager

#endif // _ORDER_STATE_MACHINE_HPP_INCLUDED_

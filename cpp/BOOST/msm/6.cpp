/*
 * This is similar to 5.cpp. The new thing is that we demonstrate an interrupt state.
 * An interrupt is just like terminal state in the sense that once it is entered, no further events will be processed.
 * The exception is only events that actually ends the interrupt. So any transition which starts at the interrupt state
 * and ends the interrupt state will be accepted and from then on, the state machine will be usable.
 */

#include <iostream>
#include <string>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/back/state_machine.hpp>

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace std;

namespace {

   //Start with the various events
   //An event is a class in MSM.
   struct open_close {};
   struct cd_detected {
       const string cdName; //This is a complex event with data.
       cd_detected(const string& arg) : cdName(arg)
       {}
   };
   struct stop {};
   struct play {};
   struct end_pause{};
   struct pause {};
   struct NextSong{};
   struct PreviousSong{};
   struct error_found {};
   struct end_error {};

   //Now define your state machine class.
   struct player_ : public msm::front::state_machine_def<player_> {

       //A state machine also has its own entry and exit behaviors.
       template <typename Event, typename FSM>
       void on_entry(const Event& event, const FSM& fsm)  {
           cout << "entering: Player" << endl;
       };

       template <typename Event, typename FSM>
       void on_exit(const Event& event, const FSM& fsm)  {
           cout << "exiting: Player" << endl;
       };

       //Now comes each state of your FSM.
       struct Empty : public msm::front::state<> {
           template <typename Event, typename FSM>
           void on_entry(const Event& event, const FSM& fsm)  {
               cout << "entering: Empty" << endl;
           }

           template <typename Event, typename FSM>
           void on_exit(const Event& event, const FSM& fsm)  {
               cout << "exiting: Empty" << endl;
           }
       };

       struct Open : public msm::front::state<> {
           template <typename Event, typename FSM>
           void on_entry(const Event& event, const FSM& fsm)  {
               cout << "entering: Open" << endl;
           }

           template <typename Event, typename FSM>
           void on_exit(const Event& event, const FSM& fsm)  {
               cout << "exiting: Open" << endl;
           }
       };

       struct Stopped : public msm::front::state<> {
           template <typename Event, typename FSM>
           void on_entry(const Event& event, const FSM& fsm)  {
               cout << "entering: Stopped" << endl;
           }

           template <typename Event, typename FSM>
           void on_exit(const Event& event, const FSM& fsm)  {
               cout << "exiting: Stopped" << endl;
           }
       };

       struct Paused : msm::front::state<> {
          //State not defining any entry/exit behavior.
       };

       //Now define the Submachine. ie. a state which is a state machine in itself.
       struct playing_ : public msm::front::state_machine_def<playing_> {

           //A state machine also has its own entry and exit behaviors.
           template <typename Event, typename FSM>
           void on_entry(const Event& event, const FSM& fsm)  {
               cout << "entering submachine: Playing" << endl;
           };

           template <typename Event, typename FSM>
           void on_exit(const Event& event, const FSM& fsm)  {
               cout << "exiting submachine: Playing" << endl;
           };

           //states.
           struct Song1 : public msm::front::state<> {
                template <typename Event, typename FSM>
                void on_entry(const Event& event, const FSM& fsm)  {
                    cout << "Starting: First Song" << endl;
                }

                template <typename Event, typename FSM>
                void on_exit(const Event& event, const FSM& fsm)  {
                    cout << "Finishing: First Song" << endl;
               }
          };

           struct Song2 : public msm::front::state<> {
                template <typename Event, typename FSM>
                void on_entry(const Event& event, const FSM& fsm)  {
                    cout << "Starting: Second Song" << endl;
                }

                template <typename Event, typename FSM>
                void on_exit(const Event& event, const FSM& fsm)  {
                    cout << "Finishing: Second Song" << endl;
               }
          };

           struct Song3 : public msm::front::state<> {
                template <typename Event, typename FSM>
                void on_entry(const Event& event, const FSM& fsm)  {
                    cout << "Starting: Third Song" << endl;
                }

                template <typename Event, typename FSM>
                void on_exit(const Event& event, const FSM& fsm)  {
                    cout << "Finishing: Third Song" << endl;
               }
          };

          //Now you have defined all states. Now define the initial state.
          typedef Song1 initial_state;

          //actions and guards
          void start_next_song(const NextSong& event) { cout << "Playing::start_next_song\n"; }
          void previous_next_song(const PreviousSong& event) { cout << "Playing::previous_next_song\n"; }

          //Now the transition table.
          struct transition_table : mpl::vector4 <
                   //------------- Start------------------ Event---------------- Target------------------ Action------------------------ Guard---------------------
              a_row <             Song1,                 NextSong,               Song2,             &playing_::start_next_song                                   >,
              a_row <             Song2,                 NextSong,               Song3,             &playing_::start_next_song                                   >,
              a_row <             Song2,                 PreviousSong,           Song1,             &playing_::previous_next_song                                >,
              a_row <             Song3,                 PreviousSong,           Song2,             &playing_::previous_next_song                                >
                   //-----------------------------------------------------------------------------------------------------------------------------------------------
              >
         { };

          //Override the default No Transition Response.
          template <typename Event, typename FSM>
          void no_transition(const Event& event, const FSM& fsm, int state) {
             cout << "No Transition defined from state " << state << "  on event: " << typeid(event).name() << endl;
          }
       };

       //States for the new Region.
       struct AllOk : public msm::front::state<> {
           template <typename Event, typename FSM>
           void on_entry(const Event& event, const FSM& fsm)  {
                cout << "entering: AllOk" << endl;
            }

           template <typename Event, typename FSM>
           void on_exit(const Event& event, const FSM& fsm)  {
               cout << "exiting: AllOk" << endl;
           }
       };

       struct ErrorMode : public msm::front::interrupt_state<end_error> {
           template <typename Event, typename FSM>
           void on_entry(const Event& event, const FSM& fsm)  {
                cout << "entering: ErrorMode" << endl;
            }

           template <typename Event, typename FSM>
           void on_exit(const Event& event, const FSM& fsm)  {
               cout << "exiting: ErrorMode" << endl;
           }
       };

       //Define the backend
       typedef msm::back::state_machine<playing_> Playing;

       //Initial state for the main state machine
       typedef mpl::vector<Empty,AllOk> initial_state;

       //actions/guards
       void open_drawer(const open_close& event) { cout << "player::open_drawer\n"; }
       void close_drawer(const open_close& event) { cout << "player::close_drawer\n"; }
       void store_cd_info(const cd_detected& event) { cout << "player::store_cd_info\n"; }
       void stopped_again(const stop& event) { cout << "player::stopped_again\n"; }
       void stop_and_open(const open_close& event) { cout << "player::stop_and_open\n"; }
       void stop_playback(const stop& event) { cout << "player::stop_playback\n"; }
       void start_playback(const play& event) { cout << "player::start_playback\n"; }
       void pause_playback(const pause& event) { cout << "player::pause_playback\n"; }
       void resume_playback(const end_pause& event) { cout << "player::resume_playback\n"; }
       void report_error(const error_found& event) { cout << "Exception:: State machine Error\n"; }
       void recover_from_error(const end_error& event) { cout << "Cool: recovering from error\n"; }

      //Now the transition table.
      struct transition_table : mpl::vector<
               //------------- Start------------------ Event---------------- Target------------------ Action------------------------ Guard---------------------
          a_row <             Stopped,                 play,                 Playing,            &player_::start_playback                                    >,
          a_row <             Stopped,               open_close,             Open,               &player_::open_drawer                                       >,
          a_row <             Stopped,                 stop,                 Stopped,            &player_::stopped_again                                     >,
               //-----------------------------------------------------------------------------------------------------------------------------------------------
          a_row <             Open,                  open_close,             Empty,              &player_::close_drawer                                      >,
               //-----------------------------------------------------------------------------------------------------------------------------------------------
          a_row <             Empty,                 open_close,             Open,               &player_::open_drawer                                       >,
          a_row <             Empty,                 cd_detected,            Stopped,            &player_::store_cd_info                                     >,
               //-----------------------------------------------------------------------------------------------------------------------------------------------
          a_row <             Playing,                 stop,                 Stopped,            &player_::stop_playback                                     >,
          a_row <             Playing,                 pause,                Paused,             &player_::pause_playback                                    >,
          a_row <             Playing,               open_close,             Open,               &player_::stop_and_open                                     >,
               //-----------------------------------------------------------------------------------------------------------------------------------------------
          a_row <             Paused,                end_pause,              Playing,            &player_::resume_playback                                   >,
          a_row <             Paused,                  stop,                 Stopped,            &player_::stop_playback                                     >,
          a_row <             Paused,                open_close,             Open,               &player_::stop_and_open                                     >,
               //-----------------------------------------------------------------------------------------------------------------------------------------------
          a_row <             AllOk,                error_found,             ErrorMode,          &player_::report_error                                      >,
               //-----------------------------------------------------------------------------------------------------------------------------------------------
          a_row <             ErrorMode,            end_error,               AllOk,              &player_::recover_from_error                                >
               //-----------------------------------------------------------------------------------------------------------------------------------------------
          >
      { };

       //Override the default No Transition Response.
       template <typename Event, typename FSM>
       void no_transition(const Event& event, FSM& fsm, int state) {
          cout << "No Transition defined from state " << state << "  on event: " << typeid(event).name() << endl;
          if(state < 5)
              fsm.process_event(error_found());
       }
   };

   //Define the backend
   typedef msm::back::state_machine<player_> player;

   //State names for testing
   static string state_names[] = { "Stopped", "Open", "Empty", "Playing", "Paused" , "AllOk", "ErrorMode" };

   //Print state function
   void pstate(const player& p) { // The back end player object. Note you could have used the front end object here as argument and then downcast to back end object.
       int i = 0;
       for(i = 0; i < player::nr_regions::value; ++i) // Note we have multiple regions now. So we'll print the active state from each region.
           cout << " -> " << state_names[p.current_state()[i]] << endl;
   }

   void test() {
      //Always use the back end object for triggering transitions.
      player p;

      //Start the state machine.
      p.start(); //Will triiger on_entry() for state machine and the initial state both.

     p.process_event(open_close()); pstate(p);
     //No transition defined from Empty with stop() event, this should take the state machine into an interrupt state.
     p.process_event(play()); pstate(p);

     //This event will not be processed.
     p.process_event(open_close());
     p.process_event(open_close());

     //This event should be processed.
     p.process_event(end_error());

     //Now the state machine should resume
     p.process_event(open_close());
     cout << "Stop the FSM engine now" << endl;
     p.stop(); //Will triiger on_exit() for state machine and the current state both.

  }
}

int main() {
    test();
    return 0;
}

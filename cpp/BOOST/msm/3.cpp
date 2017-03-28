/* My First state machine. An example from boost website on state machine in a CD player. */
// The state machine is shown in figure: CompositeTutorial.jpg.

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

           void on_entry(const open_close&, const msm::back::state_machine<player_>& fsm) {
               cout << "Rajat Rajat Blah Blah" << endl;
               //return "Hello World";
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
       //Define the backend
       typedef msm::back::state_machine<playing_> Playing;

       //Initial state for the main state machine
       typedef Empty initial_state;

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

      //Now the transition table.
      struct transition_table : mpl::vector<
               //------------- Start------------------ Event---------------- Target------------------ Action------------------------ Guard---------------------
          a_row <             Stopped,                 play,                 Playing,            &player_::start_playback                                    >,
          a_row <             Stopped,               open_close,             Open,               &player_::open_drawer                                       >,
          a_row <             Stopped,                 stop,                 Stopped,            &player_::stopped_again                                     >,
               //-----------------------------------------------------------------------------------------------------------------------------------------------
          a_row <             Open,                  open_close,              Empty,             &player_::close_drawer                                      >,
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
          a_row <             Paused,                open_close,             Open,               &player_::stop_and_open                                     >
               //-----------------------------------------------------------------------------------------------------------------------------------------------
          >
      { };

       //Override the default No Transition Response.
       template <typename Event, typename FSM>
       void no_transition(const Event& event, const FSM& fsm, int state) {
          cout << "No Transition defined from state " << state << "  on event: " << typeid(event).name() << endl;
       }

       public:
           int id;
           player_(const int& pId) : id(pId) {};
   };
   //Define the backend
   typedef msm::back::state_machine<player_> player;

   //State names for testing
   static string state_names[] = { "Stopped", "Open", "Empty", "Playing", "Paused" };

   //Print state function
   void pstate(const player& p) { // The back end player object. Note you could have used the front end object here as argument and then downcast to back end object.
       cout << " -> " << state_names[p.current_state()[0]] << endl;
   }

   void test() {
      //Always use the back end object for triggering transitions. 
      player p(10); 

      //Start the state machine.
      p.start(); //Will triiger on_entry() for state machine and the initial state both.

     p.process_event(open_close()); pstate(p);
     #if 0
     p.process_event(open_close()); pstate(p);
     p.process_event(cd_detected("Punjabi Songs")); pstate(p);
     p.process_event(play()); pstate(p);

     p.process_event(NextSong()); pstate(p);
     p.process_event(NextSong()); pstate(p);
     p.process_event(PreviousSong()); pstate(p);

     p.process_event(pause()); pstate(p);

     p.process_event(end_pause()); pstate(p);
     p.process_event(pause()); pstate(p);
     p.process_event(stop()); pstate(p);
     p.process_event(stop()); pstate(p);

     p.process_event(play()); pstate(p);

     //No transition defined from Empty with stop() event.
     p.process_event(cd_detected("ABC")); pstate(p);

     #endif
     cout << "Stop the FSM engine now" << endl;
     p.stop(); //Will triiger on_exit() for state machine and the current state both.
     cout << "Restart FSM engine" << endl;
     //p.start(); //When you restart an FSM, it will begin in the state in which you left it last.

  }
}

int main() {
    test();
    return 0;
}



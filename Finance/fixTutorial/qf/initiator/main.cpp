#include "InitiatorApp.hpp"
#include <quickfix/SessionSettings.h>
#include <quickfix/FileStore.h>
#include <quickfix/FileLog.h>
#include <quickfix/SocketInitiator.h>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{

    //Did we get the session settings file?
    if(argc < 2)
    {
        cout << "Usage:\n\tinitiatorApp <sessionSettingsFile>\n";
        return 1;
    }

    string sessionSettingsFile(argv[1]);
    try
    {
        //Read SessionSettings
        FIX::SessionSettings ss(sessionSettingsFile);
        myfix::InitiatorApp myApp; //my acceptor class.

        //Create MessageStoreFactory
        FIX::FileStoreFactory fileStoreFactory(ss);
        //Create LogFactory
        FIX::FileLogFactory fileLogFactory(ss);

        //Create the SocketAcceptor
        FIX::SocketInitiator initiator(myApp, fileStoreFactory, ss, fileLogFactory);
        initiator.start(); //Will return immediately
        initiator.stop();
    } catch(const FIX::ConfigError& ce)
    {
        cerr << "Caught Exception: " << ce.what() << endl;
    }
}



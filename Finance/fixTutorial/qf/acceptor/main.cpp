#include "AcceptorApp.hpp"
#include <quickfix/SessionSettings.h>
#include <quickfix/FileStore.h>
#include <quickfix/FileLog.h>
#include <quickfix/SocketAcceptor.h>
#include <string>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;
using namespace boost::posix_time;

int main(int argc, char* argv[])
{

    //Did we get the session settings file?
    if(argc < 2)
    {
        cout << "Usage:\n\tacceptorApp <sessionSettingsFile>\n";
        return 1;
    }

    string sessionSettingsFile(argv[1]);
    try
    {
        //Read SessionSettings
        FIX::SessionSettings ss(sessionSettingsFile);
        myfix::AcceptorApp myApp; //my acceptor class.

        //Create MessageStoreFactory
        FIX::FileStoreFactory fileStoreFactory(ss);
        //Create LogFactory
        FIX::FileLogFactory fileLogFactory(ss);

        //Create the SocketAcceptor
        FIX::SocketAcceptor acceptor(myApp, fileStoreFactory, ss, fileLogFactory);
        acceptor.start(); //Will return immediately
        boost::this_thread::sleep(minutes(20));
        acceptor.stop();
    } catch(const FIX::ConfigError& ce)
    {
        cerr << "Caught Exception: " << ce.what() << endl;
    }
}



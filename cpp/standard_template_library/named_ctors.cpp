#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class ConnectionOptions
{
private:
   struct
   {
      string hostname;
      string hostaddr;
      string port;
      string interface;
   } value;

   struct
   {
      bool bHostName;
      bool bHostAddr;
      bool bPort;
      bool bInterface;
   } present;

public:
   ConnectionOptions()
   {
      present.bHostName = present.bHostAddr = present.bPort = present.bInterface = false;
   }

   ConnectionOptions& hostname(const string& hostname)
   {
      value.hostname = hostname;
      present.bHostName = true;
      return *this;
   }
   ConnectionOptions& hostaddr(const string& hostaddr)
   {
      value.hostaddr = hostaddr;
      present.bHostAddr = true;
      return *this;
   }
   ConnectionOptions& port(const string& port)
   {
      value.port = port;
      present.bPort = true;
      return *this;
   }
   ConnectionOptions& interface(const string& interface)
   {
      value.interface = interface;
      present.bInterface = true;
      return *this;
   } 
   bool isHostNameSet()  { return present.bHostName;  }
   bool isHostAddrSet()  { return present.bHostAddr;  }
   bool isPortSet()      { return present.bPort;      }
   bool isInterfaceSet() { return present.bInterface; }

   const string& hostname()  { return value.hostname;  }
   const string& hostaddr()  { return value.hostaddr;  }
   const string& port()      { return value.port;      }
   const string& interface() { return value.interface; }
};

class ConnectIt
{
public:
   ConnectIt(ConnectionOptions& opt);
};

ConnectIt::ConnectIt(ConnectionOptions& opt)
{
   if(opt.isHostNameSet() && opt.isHostAddrSet())
   {
       cout << "Please specify only one of hostname or hostaddr.. not both.\n";
       exit(1);
   }
   if(opt.isHostNameSet())
      cout<<"HostName  = "<<opt.hostname()<<endl;

   if(opt.isHostAddrSet())
      cout<<"HostAddr  = "<<opt.hostaddr()<<endl;

   if(opt.isPortSet())
      cout<<"Port      = "<<opt.port()<<endl;

   if(opt.isInterfaceSet())
      cout<<"Interface = "<<opt.interface()<<endl;
}

int main()
{
   ConnectIt(ConnectionOptions()
                      .hostaddr("192.168.44.153")
                      .hostname("ABCD")
                      .port("8080"));
   
   cout<<endl;

   ConnectIt(ConnectionOptions()
                      .hostname("CentOS 4.8 32 bit")
                      .interface("eth0"));
   return 0;
}



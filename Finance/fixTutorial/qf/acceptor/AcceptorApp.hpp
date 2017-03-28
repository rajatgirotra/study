#ifndef _ACCEPTORAPP_INCLUDED_
#define _ACCEPTORAPP_INCLUDED_

#include <quickfix/Application.h>

namespace myfix
{
    class AcceptorApp : public FIX::Application
    {
        public:
            virtual ~AcceptorApp() {}

            //override methods in FIX::Application
            void onCreate(const FIX::SessionID&);
            void onLogon(const FIX::SessionID&);
            void onLogout(const FIX::SessionID&);
            void toAdmin(FIX::Message&, const FIX::SessionID&);
            void toApp(FIX::Message&, const FIX::SessionID&) throw (FIX::DoNotSend);
            void fromAdmin(const FIX::Message&, const FIX::SessionID&)
                throw (FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::FieldNotFound, FIX::RejectLogon);
            void fromApp(const FIX::Message&, const FIX::SessionID&)
                throw (FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::FieldNotFound, FIX::UnsupportedMessageType);
    };
}

#endif // _ACCEPTORAPP_INCLUDED_

#ifndef _INITIATORAPP_INCLUDED_
#define _INITIATORAPP_INCLUDED_

#include <quickfix/Application.h>

namespace myfix
{
    class InitiatorApp : public FIX::Application
    {
        public:
            virtual ~InitiatorApp() {}

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

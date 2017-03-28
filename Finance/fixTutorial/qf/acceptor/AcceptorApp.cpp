#include "AcceptorApp.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace myfix;


void AcceptorApp::onCreate(const FIX::SessionID& sessionID)
{
    cout << "New Session created: " << sessionID.toString() << endl;
}

void AcceptorApp::onLogon(const FIX::SessionID& sessionID)
{
    cout << "Logon received for session: " << sessionID.toString() << endl;
}

void AcceptorApp::onLogout(const FIX::SessionID& sessionID)
{
    cout << "Logout received for session: " << sessionID.toString() << endl;
}

void AcceptorApp::toAdmin(FIX::Message& msg, const FIX::SessionID& sessionID)
{
    cout << "Sending Admin Message: " << msg.toString() << "  to session: " << sessionID.toString() << endl;
}

void AcceptorApp::toApp(FIX::Message& msg, const FIX::SessionID& sessionID) throw (FIX::DoNotSend)
{
    cout << "Sending Business Message: " << msg.toString() << "  to session: " << sessionID.toString() << endl;
}

void AcceptorApp::fromAdmin(const FIX::Message& msg, const FIX::SessionID& sessionID)
                throw (FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::FieldNotFound, FIX::RejectLogon)
{
    cout << "Received Admin Message: " << msg.toString() << " from session: " << sessionID.toString() << endl;
}

void AcceptorApp::fromApp(const FIX::Message& msg, const FIX::SessionID& sessionID)
                throw (FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::FieldNotFound, FIX::UnsupportedMessageType)
{
    cout << "Received Business Message: " << msg.toString() << " from session: " << sessionID.toString() << endl;
}


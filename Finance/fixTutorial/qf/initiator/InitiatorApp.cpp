#include "InitiatorApp.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace myfix;


void InitiatorApp::onCreate(const FIX::SessionID& sessionID)
{
    cout << "New Session created: " << sessionID.toString() << endl;
}

void InitiatorApp::onLogon(const FIX::SessionID& sessionID)
{
    cout << "Logon received for session: " << sessionID.toString() << endl;
}

void InitiatorApp::onLogout(const FIX::SessionID& sessionID)
{
    cout << "Logout received for session: " << sessionID.toString() << endl;
}

void InitiatorApp::toAdmin(FIX::Message& msg, const FIX::SessionID& sessionID)
{
    cout << "Sending Admin Message: " << msg.toString() << "  to session: " << sessionID.toString() << endl;
}

void InitiatorApp::toApp(FIX::Message& msg, const FIX::SessionID& sessionID) throw (FIX::DoNotSend)
{
    cout << "Sending Business Message: " << msg.toString() << "  to session: " << sessionID.toString() << endl;
}

void InitiatorApp::fromAdmin(const FIX::Message& msg, const FIX::SessionID& sessionID)
                throw (FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::FieldNotFound, FIX::RejectLogon)
{
    cout << "Received Admin Message: " << msg.toString() << " from session: " << sessionID.toString() << endl;
}

void InitiatorApp::fromApp(const FIX::Message& msg, const FIX::SessionID& sessionID)
                throw (FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::FieldNotFound, FIX::UnsupportedMessageType)
{
    cout << "Received Business Message: " << msg.toString() << " from session: " << sessionID.toString() << endl;
}


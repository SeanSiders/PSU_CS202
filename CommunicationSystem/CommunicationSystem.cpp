/***** CLASS IMPLEMENTATION FILE *****/

//Sean Siders
//CS202
//Program 2 : Communication System
//10/30/2020

/*
This is the implementation of the |Communication| single inheritance hierarchy. |Slack|, |Discord|,
and |Gmail| are all derived from the abstract bass class |Communication|, and provide functionality
that is unique to the type of account it manages. These accounts interact with derived classes in
the |Server| hierarchy which are implemented in |DataStructures.cpp|.
*/

#include "CommunicationSystem.h"

/////////////////////////////////////////////// DEFAULT CONSTRUCTORS 

//for input from the user for |handle|, |first|, and |last|
Communication::Communication()
{
    std::cout << "ENTER THE FOLLOWING INFORMATION\nACCOUNT NAME";
    handle.getInput();

    std::cout << "FIRST NAME";
    first.getInput();

    std::cout << "LAST NAME";
    last.getInput();
}

Slack::Slack() : head(nullptr), linkedServer(nullptr)
{
    key.setString("SLACK");
}

Discord::Discord() : head(nullptr), linkedServer(nullptr)
{
    key.setString("DISCORD");
}

Gmail::Gmail() : head(nullptr), linkedServer(nullptr)
{
    key.setString("GMAIL");
}

/////////////////////////////////////////////// COPY CONSTRUCTORS 

Communication::Communication(const Communication& other) :
    handle(other.handle), first(other.first), last(other.last) {}

Slack::Slack(const Slack& other) : Communication(other)
{
    key.setString("SLACK");

    //copy over the server list from |other|
    copyServerList(head, other.head);
    linkedServer = other.linkedServer;
}

Discord::Discord(const Discord& other) : Communication(other)
{
    key.setString("DISCORD");

    //copy over the server list from |other|
    copyServerList(head, other.head);
    linkedServer = other.linkedServer;
}

Gmail::Gmail(const Gmail& other) : Communication(other)
{
    key.setString("GMAIL");

    //copy over the server list from |other|
    copyServerList(head, other.head);
    linkedServer = other.linkedServer;
}

/////////////////////////////////////////////// INITIALIZATION CONSTRUCTORS 

Communication::Communication(const String& _handle, const String& _first, const String& _last) :
    handle(_handle), first(_first), last(_last) {}

Slack::Slack(const String& _handle, const String& _first, const String& _last) :
    Communication(_handle, _first, _last), head(nullptr), linkedServer(nullptr)
{
    key.setString("SLACK");
}

Discord::Discord(const String& _handle, const String& _first, const String& _last) :
    Communication(_handle, _first, _last), head(nullptr), linkedServer(nullptr)
{
    key.setString("DISCORD");
}

Gmail::Gmail(const String& _handle, const String& _first, const String& _last) :
    Communication(_handle, _first, _last), head(nullptr), linkedServer(nullptr)
{
    key.setString("GMAIL");
}

/////////////////////////////////////////////// DESTRUCTORS 

Communication::~Communication() {}

Slack::~Slack()
{
    delete head;
    head = nullptr;
}

Discord::~Discord()
{
    delete head;
    head = nullptr;
}

Gmail::~Gmail()
{
    delete head;
    head = nullptr;
}

/////////////////////////////////////////////// COMMUNICATION 

//display the account name |handle|
void Communication::displayName() const
{
    handle.display();
}

void Communication::changeHandle()
{
    std::cout << "NEW HANDLE";
    handle.getInput();
}

//change the user's first and last name 
void Communication::changeName()
{
    std::cout << "FIRST NAME";
    first.getInput();

    std::cout << "LAST NAME";
    last.getInput();
}

//compare |handle| and |key| of |other| to this account, if they match return true
bool Communication::isMatch(const Communication& other) const
{
    return (handle.isMatch(other.handle) && key.isMatch(other.key));
}

//true if |handle| matches |_handle|
bool Communication::isMatch(const String& _handle) const
{
    return handle.isMatch(_handle);
}

//true if |handle| matches |_handle| and |key| matches |_key|
bool Communication::isMatch(const String& _handle, const String& _key) const
{
    return (handle.isMatch(_handle) && key.isMatch(_key));
}

/////////////////////////////////////////////// SLACK 

//display the user name, and the linked server and channel in a unique slack format
void Slack::display() const
{
    std::cout << "\nHANDLE : ";
    //display the user handle
    handle.display();
    std::cout << '\n';
    
    if (serverCheck())
    {
        std::cout << "<<<<<<<<<<< SLACK THREAD DISPLAY >>>>>>>>>>>\n";

        std::cout << "\n=======================================================\n";

        //display the thread in this slack server channel
        linkedServer->displayThread();

        std::cout << "\n=======================================================\n\n";
    }
}

//WRAPPER
//display the servers this account has access to
//display the current linked server
void Slack::displayServerList() const
{
    std::cout << '\n';

    handle.display();
    std::cout << " SERVERS\n\n";

    //display the server list
    displayServerList(head);

    //display the current linked server, and channels
    displayLinkedServer();
}

//RECURSIVE
//traverse with |head| displaying all server names
void Slack::displayServerList(ServerNode* head) const
{
    if (!head) return;
    head->getServer()->displayName();
    displayServerList(head->getNext());
}

//display the current slack server this account is linked to
void Slack::displayLinkedServer() const
{
    if (linkedServer)
    {
        std::cout << "\n=====================\n"
        << "CURRENT SLACK SERVER\n"
        << "=====================\n";

        linkedServer->display();
    }
}

//WRAPPER
//attempt add a server to the LLL of servers that this account has access to
//if the server is already in this list, or the server's key does not match this account, return false
bool Slack::addServer(Server* server)
{
    //cast the server pointer to |ChannelServer*|
    ChannelServer* castptr = dynamic_cast<ChannelServer*>(server);

    //if |server| is null, or an invalid type
    if (!server || !castptr || !castptr->keyCheck(key)) return false;

    return addServer(castptr, head);
}

//RECURSIVE
//traverse through the |ServerNode| LLL with |head|
//insert |server| at the tail unless the server is already in the list
bool Slack::addServer(ChannelServer* server, ServerNode*& head)
{
    //end of list was reached, insert the new server
    if (!head)
    {
        //allocate the new node
        head = new ServerNode(server);

        //set the currently linked server to this new server
        linkedServer = dynamic_cast<ChannelServer*>(server);

        return true;
    }

    //the server already exists in the list
    if (server == head->getServer()) return false;

    return addServer(server, head->getNext());
}

//WRAPPER
//remove a server from the LLL by name
//return false if no match was found
bool Slack::removeServer(const String& serverName)
{
    if (!head) return false;

    return removeServer(serverName, head);
}

//RECURSIVE
//traverse throught the LLL with |head|
//remove the node that contains a match
//if no match is found, return false
bool Slack::removeServer(const String& serverName, ServerNode*& head)
{
    //end of list, no match was found
    if (!head) return false;

    //if a match is found
    if (head->getServer()->isMatch(serverName))
    {
        //hold onto the rest of the list
        ServerNode* hold = head->getNext();

        //if the current linked server is the one being removed, then set the linked server to null
        if (linkedServer == head->getServer()) linkedServer = nullptr;

        //deallocate the node
        head->setNext(nullptr);
        delete head;

        //link the rest of the list
        head = hold;

        return true;
    }

    return removeServer(serverName, head->getNext());
}

//WRAPPER
//compare |serverName| with all servers in the LLL of |ServerNode|
//if a match is found, point |linkedServer| to that node and return true
//this allows to user to switch between servers that are linked to an account
bool Slack::setLinkedServer(String& serverName)
{
    if (!head) return false;

    return setLinkedServer(serverName, head);
}

//RECURSIVE
//traverse through the |ServerNode| LLL with |head|
bool Slack::setLinkedServer(String& serverName, ServerNode* head)
{
    //end of list, no match was found
    if (!head) return false;

    //if the server was found in the list
    if (head->getServer()->isMatch(serverName))
    {
        //set the linked pointer using a dynamic cast
        linkedServer = dynamic_cast<ChannelServer*>(head->getServer());

        return true;
    }

    return setLinkedServer(serverName, head->getNext());
}

//if there is no linked server, prompt the user with an error and return false
bool Slack::serverCheck() const
{
    if (!head || !linkedServer)
    {
        std::cout << "SLACK WARNING : no server currently linked\n\n";
        return false;
    }

    return true;
}

//post a message to the current linked server
//if message is null, prepare for user input
void Slack::post(const char* message)
{
    if (serverCheck())
    {
        if (!message) std::cout << "\n<<<<<<<<<<< SLACK POST >>>>>>>>>>>\n";

        //post a message to the server with user input, passing in the user handle
        linkedServer->post(handle, message);
    }
}

//make a copy of the LLL from |source| into |copy|
void Slack::copyServerList(ServerNode*& copy, ServerNode* source)
{
    if (!source) return;

    copy = new ServerNode(source->getServer());

    copyServerList(copy->getNext(), source->getNext());
}

//HIERARCHY OUTLIER : RTTI REQUIRED
//every server has 1 or more channels
//the channel within the current linked server can be set here with user input
void Slack::setLinkedChannel()
{
    if (serverCheck())
    {
        linkedServer->displayNames();
        String channelName;
        std::cout << "ENTER THE CHANNEL NAME TO SWITCH TO\n";
        channelName.getInput();

        if (linkedServer->changeChannel(channelName)) std::cout << "SLACK CHANNEL SUCCESSFULLY LINKED\n\n";
        else std::cout << "SLACK CHANNEL NOT FOUND\n\n";
    }
}

//HIERARCHY OUTLIER : RTTI REQUIRED
//allow the user to step through the messages in the server's linked channel
void Slack::reply()
{
    if (serverCheck())
    {
        std::cout << "\n<<<<<<<<<<< SLACK REPLY >>>>>>>>>>>\n"
        << "CONTROLS\n"
        << "'n' : next message\n"
        << "'r' : reply\n"
        << "'q' : quit\n";

        //begin reply process, passing in the user handle
        linkedServer->reply(handle);

        std::cout << "<<<<<<<<<<< END SLACK REPLY >>>>>>>>>>>\n";
    }
}

/////////////////////////////////////////////// DISCORD 

//display the user name, and the linked server and channel in a unique discord format
void Discord::display() const
{
    std::cout << "\nHANDLE : ";
    //display the user handle
    handle.display();
    std::cout << '\n';
    
    if (serverCheck())
    {
        std::cout << "############### DISCORD THREAD DISPLAY ###############\n";

        std::cout << "\n=======================================================\n";

        //display the thread in this discord server channel
        linkedServer->displayThread();

        std::cout << "\n=======================================================\n\n";
    }
}

//WRAPPER
//display the servers this account has access to
//display the current linked server
void Discord::displayServerList() const
{
    std::cout << '\n';

    handle.display();
    std::cout << " SERVERS\n\n";

    //display the server list
    displayServerList(head);

    //display the current linked server, and channels
    displayLinkedServer();
}

//RECURSIVE
//traverse with |head| displaying all server names
void Discord::displayServerList(ServerNode* head) const
{
    if (!head) return;
    head->getServer()->displayName();
    displayServerList(head->getNext());
}

//display the current discord server this account is linked to
void Discord::displayLinkedServer() const
{
    if (linkedServer)
    {
        std::cout << "\n======================\n"
        << "CURRENT DISCORD SERVER\n"
        << "======================\n";

        linkedServer->display();
    }
}

//WRAPPER
//attempt add a server to the LLL of servers that this account has access to
//if the server is already in this list, or the server's key does not match this account, return false
bool Discord::addServer(Server* server)
{
    //cast the server pointer to |ChannelServer*|
    ChannelServer* castptr = dynamic_cast<ChannelServer*>(server);

    //if |server| is null, or an invalid type
    if (!server || !castptr || !castptr->keyCheck(key)) return false;

    return addServer(castptr, head);
}

//RECURSIVE
//traverse through the |ServerNode| LLL with |head|
//insert |server| at the tail unless the server is already in the list
bool Discord::addServer(ChannelServer* server, ServerNode*& head)
{
    //end of list was reached, insert the new server
    if (!head)
    {
        //allocate the new node
        head = new ServerNode(server);

        //set the currently linked server to this new server
        linkedServer = server;

        return true;
    }

    //the server already exists in the list
    if (server == head->getServer()) return false;

    return addServer(server, head->getNext());
}

//WRAPPER
//remove a server from the LLL by name
//return false if no match was found
bool Discord::removeServer(const String& serverName)
{
    if (!head) return false;

    return removeServer(serverName, head);
}

//RECURSIVE
//traverse throught the LLL with |head|
//remove the node that contains a match
//if no match is found, return false
bool Discord::removeServer(const String& serverName, ServerNode*& head)
{
    //end of list, no match was found
    if (!head) return false;

    //if a match is found
    if (head->getServer()->isMatch(serverName))
    {
        //hold onto the rest of the list
        ServerNode* hold = head->getNext();

        //if the current linked server is the one being removed, then set the linked server to null
        if (linkedServer == head->getServer()) linkedServer = nullptr;

        //deallocate the node
        head->setNext(nullptr);
        delete head;

        //link the rest of the list
        head = hold;

        return true;
    }

    return removeServer(serverName, head->getNext());
}

//WRAPPER
//compare |serverName| with all servers in the LLL of |ServerNode|
//if a match is found, point |linkedServer| to that node and return true
//this allows to user to switch between servers that are linked to an account
bool Discord::setLinkedServer(String& serverName)
{
    if (!head) return false;

    return setLinkedServer(serverName, head);
}

//RECURSIVE
//traverse through the |ServerNode| LLL with |head|
bool Discord::setLinkedServer(String& serverName, ServerNode* head)
{
    //end of list, no match was found
    if (!head) return false;

    //if the server was found in the list
    if (head->getServer()->isMatch(serverName))
    {
        //set the linked pointer using a dynamic cast
        linkedServer = dynamic_cast<ChannelServer*>(head->getServer());

        return true;
    }

    return setLinkedServer(serverName, head->getNext());
}

//if there is no linked server, prompt the user with an error and return false
bool Discord::serverCheck() const
{
    if (!head || !linkedServer)
    {
        std::cout << "DISCORD WARNING : no server currently linked\n\n";
        return false;
    }

    return true;
}

//post a message to the current linked server
//if message is null, prepare for user input
void Discord::post(const char* message)
{
    if (serverCheck())
    {
        if (!message) std::cout << "\n############### DISCORD POST ###############\n";

        //post a message to the server with user input, passing in the user handle
        linkedServer->post(handle, message);
    }
}

//make a copy of the LLL from |source| into |copy|
void Discord::copyServerList(ServerNode*& copy, ServerNode* source)
{
    if (!source) return;

    copy = new ServerNode(source->getServer());

    copyServerList(copy->getNext(), source->getNext());
}

//HIERARCHY OUTLIER : RTTI REQUIRED
//every server has 1 or more channels
//the channel within the current linked server can be set here with user input
void Discord::setLinkedChannel()
{
    if (serverCheck())
    {
        linkedServer->displayNames();

        String channelName;
        std::cout << "ENTER THE CHANNEL NAME TO SWITCH TO\n";
        channelName.getInput();

        if (linkedServer->changeChannel(channelName)) std::cout << "DISCORD CHANNEL SUCCESSFULLY LINKED\n\n";
        else std::cout << "DISCORD CHANNEL NOT FOUND\n\n";
    }
}

/////////////////////////////////////////////// GMAIL

//display the user name, and the linked server and channel in a unique google format
void Gmail::display() const
{
    std::cout << "\nHANDLE : ";
    //display the user handle
    handle.display();
    std::cout << '\n';

    if (serverCheck())
    {
        std::cout << "*************** GMAIL DISPLAY ***************\n";
        
        std::cout << "\n=======================================================\n";

        //display the thread in this discord server channel
        linkedServer->display();

        std::cout << "\n=======================================================\n\n";
    }
}

//WRAPPER
//display the servers this account has access to
//display the current linked server
void Gmail::displayServerList() const
{
    std::cout << '\n';

    handle.display();
    std::cout << " SERVERS\n\n";

    //display the server list
    displayServerList(head);

    //display the current linked server, and channels
    displayLinkedServer();
}

//RECURSIVE
//traverse with |head| displaying all server names
void Gmail::displayServerList(ServerNode* head) const
{
    if (!head) return;
    head->getServer()->displayName();
    displayServerList(head->getNext());
}

//display the current google server this account is linked to
void Gmail::displayLinkedServer() const
{
    if (linkedServer)
    {
        std::cout << "\n====================\n"
        << "CURRENT GMAIL SERVER\n"
        << "=====================\n";

        linkedServer->display();
    }
}

//WRAPPER
//attempt add a server to the LLL of servers that this account has access to
//if the server is already in this list, or the server's key does not match this account, return false
bool Gmail::addServer(Server* server)
{
    EmailServer* castptr = dynamic_cast<EmailServer*>(server);
    //check that the right server was passed in
    if (!server || !castptr) return false;

    return addServer(castptr, head);
}

//RECURSIVE
//traverse through the |ServerNode| LLL with |head|
//insert |server| at the tail unless the server is already in the list
bool Gmail::addServer(EmailServer* server, ServerNode*& head)
{
    //end of list was reached, insert the new server
    if (!head)
    {
        //allocate the new node
        head = new ServerNode(server);

        //set the linked server if it has not yet been set
        //|linkedServer| will default to the first added server
        if (!linkedServer) linkedServer = server;

        return true;
    }

    //the server already exists in the list
    if (server == head->getServer()) return false;

    return addServer(server, head->getNext());
}

//WRAPPER
//remove a server from the LLL by name
//return false if no match was found
bool Gmail::removeServer(const String& serverName)
{
    if (!head) return false;

    return removeServer(serverName, head);
}

//RECURSIVE
//traverse throught the LLL with |head|
//remove the node that contains a match
//if no match is found, return false
bool Gmail::removeServer(const String& serverName, ServerNode*& head)
{
    //end of list, no match was found
    if (!head) return false;

    //if a match is found
    if (head->getServer()->isMatch(serverName))
    {
        //hold onto the rest of the list
        ServerNode* hold = head->getNext();

        //if the current linked server is the one being removed, then set the linked server to null
        if (linkedServer == head->getServer()) linkedServer = nullptr;

        //deallocate the node
        head->setNext(nullptr);
        delete head;

        //link the rest of the list
        head = hold;

        return true;
    }

    return removeServer(serverName, head->getNext());
}

//WRAPPER
//compare |serverName| with all servers in the LLL of |ServerNode|
//if a match is found, point |linkedServer| to that node and return true
//this allows to user to switch between servers that are linked to an account
bool Gmail::setLinkedServer(String& serverName)
{
    if (!head) return false;

    return setLinkedServer(serverName, head);
}

//RECURSIVE
//traverse through the |ServerNode| LLL with |head|
bool Gmail::setLinkedServer(String& serverName, ServerNode* head)
{
    //end of list, no match was found
    if (!head) return false;

    //if the server was found in the list
    if (head->getServer()->isMatch(serverName))
    {
        //set the linked pointer using a dynamic cast
        linkedServer = dynamic_cast<EmailServer*>(head->getServer());

        return true;
    }

    return setLinkedServer(serverName, head->getNext());
}

//if there is no linked server, prompt the user with an error and return false
bool Gmail::serverCheck() const
{
    if (!head || !linkedServer)
    {
        std::cout << "GMAIL WARNING : no server currently linked\n\n";
        return false;
    }

    return true;
}

//post a message to the current linked server
//if message is null, prepare for user input
void Gmail::post(const char* message)
{
    if (serverCheck())
    {
        if (!message)
        {
            std::cout << "\n*************** GMAIL POST ***************n";

            //post a message to the server with user input, passing in the user handle
            linkedServer->send(handle);
        }
        else linkedServer->send(handle, message);
    }
}

//make a copy of the LLL from |source| into |copy|
void Gmail::copyServerList(ServerNode*& copy, ServerNode* source)
{
    if (!source) return;

    copy = new ServerNode(source->getServer());

    copyServerList(copy->getNext(), source->getNext());
}

//HIERARCHY OUTLIER : RTTI REQUIRED
//reply to an email in the current |EmailServer|
void Gmail::reply()
{
    if (serverCheck())
    {
        std::cout << "\n*************** GMAIL REPLY ***************\n"
        << "CONTROLS\n"
        << "'n' : next message\n"
        << "'r' : reply\n"
        << "'q' : quit\n";

        //reply to an email in the current server
        linkedServer->reply(handle);
    }
}


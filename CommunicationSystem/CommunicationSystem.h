/***** CLASS INTERFACE FILE *****/

//Sean Siders
//CS202
//Program 2 : Communication System
//10/30/2020

/*
All class interfaces in this file exist in a hierarchy of single inheritance. All derived classes
are derived from the abstract base class |Communication|. Any class derived from |Communication|
manages the data for a specialized communication system.
*/

#ifndef COMMUNICATION_SYSTEM_H_
#define COMMUNICATION_SYSTEM_H_

#include <iostream>
#include <cstring>
#include "DataStructures.h"

//FORWARD DECLARATIONS
class Thread;
class Server;
class EmailServer;
class ChannelServer;
class ServerNode;

/////////////////////////////////////////////// ABSTRACT BASE // COMMUNICATION ACCOUNT

class Communication
{
    public:
    /////////////////// CONSTRUCTORS

    //default constructor will ask for input from the user for |handle|, |first|, and |last|
    Communication();
    Communication(const Communication& other);
    Communication(const String& _handle, const String& _first, const String& _last);

    virtual ~Communication();

    /////////////////// PURE VIRTUAL FUNCTIONS  

    //display the user name, and the linked server and channel (if linked)
    virtual void display() const = 0;

    //display the servers this account has access to
    virtual void displayServerList() const = 0;

    //display the current server this account is linked to
    virtual void displayLinkedServer() const = 0;

    //attempt add a server to the LLL of servers that this account has access to
    //if the server is already in this list, or the server's key does not match this account, return false
    virtual bool addServer(Server* server) = 0;

    //remove a server from the LLL by name
    //return false if no match was found
    virtual bool removeServer(const String& serverName) = 0;

    //compare |serverName| with all servers in the LLL of |ServerNode|
    //if a match is found, point |linkedServer| to that node and return true
    //this allows to user to switch between servers that are linked to an account
    virtual bool setLinkedServer(String& serverName) = 0;

    //post a message to the current linked server
    //if |message| is null, get user input at the server level
    virtual void post(const char* message = nullptr) = 0;

    /////////////////// NON-VIRTUAL PUBLIC FUNCTIONS  

    //display the account name |handle|
    void displayName() const;

    //change the handle
    void changeHandle();

    //change the first and last name
    void changeName();

    //compare |handle| and |key| of |other| to this account, if they match return true
    //the String overload will return the same result with string comparisons
    bool isMatch(const Communication& other) const;
    bool isMatch(const String& _handle) const;
    bool isMatch(const String& _handle, const String& _key) const;

    protected:
    //the handle, or username for this account
    String handle;

    //the user's first and last name, respectively
    String first;
    String last;

    //this key will reflect the type of account this is
    //this is used by |Interface| to determine if an incoming account is a duplicate of another
    //see |Interface::insertAccount|
    String key;
};

/////////////////////////////////////////////// DERIVED

/*
A |Slack| account can link to any number of slack servers, which are managed internally with a
linear linked list of |Server| pointers. A slack server supports channels, which are essentially
multiple threads on one server. The user can specify which slack server, and which of that server's
channels to link. The user can then access the linked channel to post or reply with a step based
algorithm implemented in |Thread::reply|. |reply| is unique to a |Slack| account.
*/

class Slack : public Communication
{
    public:
    /////////////////// CONSTRUCTORS 

    Slack();
    Slack(const Slack& other);
    Slack(const String& _handle, const String&  _first, const String& _last);

    ~Slack();

    /////////////////// PUBLIC FUNCTIONS  

    //display the user name, and the linked server and channel in a unique slack format
    void display() const;

    //display the servers this account has access to
    void displayServerList() const;

    //display the current slack server this account is linked to
    void displayLinkedServer() const;

    //attempt to add a server to the LLL of servers that this account has access to
    //if the server is already in this list, or the server's key does not match this account, return false
    bool addServer(Server* server);

    //remove a server from the LLL by name
    //return false if no match was found
    bool removeServer(const String& serverName);

    //compare |serverName| with all servers in the LLL of |ServerNode|
    //if a match is found, point |linkedServer| to that node and return true
    //this allows to user to switch between servers that are linked to an account
    bool setLinkedServer(String& serverName);

    //post a message to the current linked server
    //if |message| is null, get user input at the server level
    void post(const char* message = nullptr);

    /////////////////// HIERARCHY OUTLIERS : RTTI REQUIRED

    //every server has 1 or more channels
    //the channel within the current linked server can be set here with user input
    void setLinkedChannel();

    //allow the user to step through the messages in the server's linked channel
    void reply();

    private:
    /////////////////// DATA

    //a linear linked list of servers that this account is attached to
    //this list is not responsible for dynamic memory
    ServerNode* head;

    //the current server that the user account is accessing
    ChannelServer* linkedServer;

    /////////////////// PRIVATE FUNCTIONS 

    //traverse with |head| displaying all server names
    void displayServerList(ServerNode* head) const;

    //traverse through the |ServerNode| LLL with |head|
    //insert |server| at the tail unless the server is already in the list
    //return false if |server| is null, in the list, or does not contain the slack |key|
    bool addServer(ChannelServer* server, ServerNode*& head);

    //traverse throught the LLL with |head|
    //remove the node that contains a match
    //if no match is found, return false
    bool removeServer(const String& serverName, ServerNode*& head);

    //traverse through the |ServerNode| LLL with |head|
    bool setLinkedServer(String& serverName, ServerNode* head);

    //if there is no linked server, prompt the user with an error and return false
    bool serverCheck() const;

    //make a copy of the LLL from |source| into |copy|
    void copyServerList(ServerNode*& copy, ServerNode* source);
};

/*
A |Discord| account can manage any number of discord servers with a linear linked list of
|ServerNode|. Each server can have multiple channels, allowing the user to post to any specified
server the account contains, as well as that server's specific channel.
*/

class Discord : public Communication
{
    public:
    /////////////////// CONSTRUCTORS 

    Discord();
    Discord(const Discord& other);
    Discord(const String& _handle, const String& _first, const String& _last);

    ~Discord();

    /////////////////// PUBLIC FUNCTIONS  

    //display the user name, and the linked server and channel in a unique discord format
    void display() const;

    //display the servers this account has access to
    void displayServerList() const;

    //display the current discord server this account is linked to
    void displayLinkedServer() const;

    //attempt add a server to the LLL of servers that this account has access to
    //if the server is already in this list, or the server's key does not match this account, return false
    bool addServer(Server* server);

    //remove a server from the LLL by name
    //return false if no match was found
    bool removeServer(const String& serverName);

    //compare |serverName| with all servers in the LLL of |ServerNode|
    //if a match is found, point |linkedServer| to that node and return true
    //this allows to user to switch between servers that are linked to an account
    bool setLinkedServer(String& serverName);

    //post a message to the current linked server
    //if |message| is null, get user input at the server level
    void post(const char* message = nullptr);

    /////////////////// HIERARCHY OUTLIER : RTTI REQUIRED

    //every server has 1 or more channels
    //the channel within the current linked server can be set here with user input
    void setLinkedChannel();

    private:
    /////////////////// DATA

    //a linear linked list of servers that this account is attached to
    //this list is not responsible for dynamic memory
    ServerNode* head;

    //the current server that the user account is accessing
    ChannelServer* linkedServer;

    /////////////////// PRIVATE FUNCTIONS 

    //traverse with |head| displaying all server names
    void displayServerList(ServerNode* head) const;

    //traverse through the |ServerNode| LLL with |head|
    //insert |server| at the tail unless the server is already in the list
    //return false if |server| is null, in the list, or does not contain the discord |key|
    bool addServer(ChannelServer* server, ServerNode*& head);

    //traverse throught the LLL with |head|
    //remove the node that contains a match
    //if no match is found, return false
    bool removeServer(const String& serverName, ServerNode*& head);

    //traverse through the |ServerNode| LLL with |head|
    bool setLinkedServer(String& serverName, ServerNode* head);

    //if there is no linked server, prompt the user with an error and return false
    bool serverCheck() const;

    //make a copy of the LLL from |source| into |copy|
    void copyServerList(ServerNode*& copy, ServerNode* source);
};

/*
A |Gmail| account can only be connected to one google chat server at a time, allowing for a
single threaded discussion for the duration of that connection.
*/

class Gmail : public Communication
{
    public:
    /////////////////// CONSTRUCTORS 

    Gmail();
    Gmail(const Gmail& other);
    Gmail(const String& _handle, const String& _first, const String& _last);

    ~Gmail();

    /////////////////// PUBLIC FUNCTIONS  

    //display the user name, and the linked server's emails
    void display() const;

    //display the servers this account has access to
    void displayServerList() const;

    //display the current google server this account is linked to
    void displayLinkedServer() const;

    //attempt add a server to the LLL of servers that this account has access to
    //if the server is already in this list, or the server's key does not match this account, return false
    bool addServer(Server* server);

    //remove a server from the LLL by name
    //return false if no match was found
    bool removeServer(const String& serverName);

    //compare |serverName| with all servers in the LLL of |ServerNode|
    //if a match is found, point |linkedServer| to that node and return true
    //this allows to user to switch between servers that are linked to an account
    bool setLinkedServer(String& serverName);

    //post a message to the current linked server
    //if |message| is null, get user input at the server level
    void post(const char* message = nullptr);

    /////////////////// HIERARCHY OUTLIER : RTTI REQUIRED

    //reply to an email in the current |EmailServer|
    void reply();

    private:
    /////////////////// DATA

    //a linear linked list of servers that this account is attached to
    //this list is not responsible for dynamic memory
    ServerNode* head;

    //the current server that the user account is accessing
    //for Gmail, the first linked server will be the default Gmail server
    EmailServer* linkedServer;

    /////////////////// PRIVATE FUNCTIONS 

    //traverse with |head| displaying all server names
    void displayServerList(ServerNode* head) const;

    //traverse through the |ServerNode| LLL with |head|
    //insert |server| at the tail unless the server is already in the list
    //return false if |server| is null, in the list, or does not contain the google |key|
    bool addServer(EmailServer* server, ServerNode*& head);

    //traverse throught the LLL with |head|
    //remove the node that contains a match
    //if no match is found, return false
    bool removeServer(const String& serverName, ServerNode*& head);

    //traverse through the |ServerNode| LLL with |head|
    bool setLinkedServer(String& serverName, ServerNode* head);

    //if there is no linked server, prompt the user with an error and return false
    bool serverCheck() const;

    //make a copy of the LLL from |source| into |copy|
    void copyServerList(ServerNode*& copy, ServerNode* source);
};

#endif

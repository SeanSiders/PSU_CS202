/***** CLASS INTERFACE FILE *****/

//Sean Siders
//CS202
//Program 2 : Communication System
//10/30/2020

/*
Classes that are designed around data structures are interfaced in this file. The resulting system
from this collection of classes simulates 2 different servers |EmailServer| and |ChannelServer|,
that derived classes of |Communication| can interact with. |EmailServer| manages a stack of
|EmailThread| objects, which also manage stacks, effectively making a stack of stacks.
|ChannelServer| manages an array of |MessageThread| objects, which manage stacks, making an array of
stacks. |Interface| is provided as a client entry point to interact with the data structure
classes found here, and the |Communication| classes in |CommunicationSystem.h|.
*/

#ifndef DATA_STRUCTURES_H_
#define DATA_STRUCTURES_H_

#include "UnderlyingData.h"
#include "CommunicationSystem.h"

//FORWARD DECLARATIONS
class String;
class Email;
class Message;
class Communication;
class Slack;
class Discord;
class Gmail;
class Interface;
class Server;
class AccountNode;
class ServerNode;

//CONSTANT
//the max number of channels a ChannelServer can have
const int CHANNEL_MAX = 5;

/////////////////////////////////////////////// EXTERNAL FILE INTERFACE

/////////////////////////////////////////////// COMMUNICATION INTERFACE

/*
|Interface| will manage a linear linked list of all of the accounts created by a single user.
This is designed to be an interface that allows any derived classes of |Communication| to be managed
by one data structure. In addition to managing a user's communication accounts, it also links an
account to a desired server. This class can also be considered the main client entry point.
*/

class Interface
{
    public:
    /////////////////// CONSTRUCTOR

    Interface();
    Interface(const Interface& other);
    ~Interface();

    /////////////////// PUBLIC FUNCTIONS 

    //prompt a menu of options to the user, and take user input to perform an action
    void menu();

    //insert |newAccount| into the account list
    void insertAccount(Communication* newAccount);

    //insert |newServer| into the server list
    void insertServer(Server* newServer);

    private:
    /////////////////// DATA

    //head of the accounts linear linked list
    AccountNode* aHead;

    //head of the servers linear linked list
    ServerNode* sHead;

    //a string buffer for user input
    String stringBuffer;

    //an integer buffer for user input
    Int intBuffer;

    /////////////////// ACCOUNT LIST OPERATIONS

    //traverse with |head| displaying all accounts in the list, and their current server threads
    void fullDisplay(AccountNode* head) const;

    //traverse with |head| displaying all of the account names
    void displayAccounts(AccountNode* head) const;

    //prompt a menu to create one of the 3 account types, then insert it into the |AccountNode| list
    void createAccount();

    //insert a new account whos type is specified with |index| into the |AccountNode| list
    void insertAccount(const int index);

    //check that the account name is unique to any other accounts of that type in the list
    //insert at the end if it is unique, then return true, otherwise false
    bool insertAccount(AccountNode*& head, Communication* newAccount);

    //open an existing account in the account list
    //prompt the user with options to interact with the account, such as post, display, or reply
    void openAccount();

    //attempt to find an account that matches the name |accountName|, traversing with |head|
    Communication* retrieveAccount(const String& accountName, AccountNode* head);

    //attempt to remove an existing account with user input
    void removeAccount();

    //traverse the account list with |head| attempting to remove an account with name |toRemove|
    //false if no match was found
    bool removeAccount(const String& toRemove, AccountNode*& head);

    //////// RUN TIME TYPE IDENTIFICATION
    //attempt to dynamic cast into the overloaded |accountMenu|
    void accountMenu(Communication*& account);

    //OVERLOADED FUNCTION
    //prompt a menu unique to the account type passed in
    //return false if |account| is null
    bool accountMenu(Slack* account);
    bool accountMenu(Discord* account);
    bool accountMenu(Gmail* account);

    //OVERLOADED FUNCTION
    //get integer input from the user to call one of the procedures on an account
    bool accountCall(Slack* account);
    bool accountCall(Discord* account);
    bool accountCall(Gmail* account);

    //copy the account list from |source| into |destination|
    void copyAccountList(AccountNode*& destination, AccountNode* source);

    /////////////////// SERVER LIST OPERATIONS

    //display the list of servers, traversing with |head|
    void displayServers(ServerNode* head) const;

    //prompt a menu to create a server for one of the 3 account types, then insert it into the server list
    void createServer();

    //make a server that cooresponds to the type of account specified, then insert it into the server list
    void insertServer(const int index);

    //insert |server| into the head of the server list
    void insertServer(ServerNode*& head, Server* server);

    //OVERLOADED FUNCTION
    //traverse the account list with |head|
    //link |server| to an account that matches the |accountName| and |key|
    //false if no match is found or if the server is already linked to the account
    bool linkServer(Server* server, const String& accountName, const String& key, AccountNode* head);

    //traverse the server list with |head| to link a server with name |serverName| to |account|
    //false if no match is found
    bool linkServer(Communication* account, const String& serverName, ServerNode* head);

    //attempt to remove an existing server with user input
    void removeServer();

    //traverse the server list with |head| attempting to remove a server with name |toRemove|
    //false if no match was found
    bool removeServer(const String& toRemove, ServerNode*& head);

    //in the event of server being removed from the interface
    //any account that contains a pointer to that server must set the pointer to null
    //traverse the account list with |head| unlinking the server from any matching accounts
    //return the number of accounts that were unlinked
    int unlinkServer(const String& toUnlink, AccountNode* head);

    //deallocate the server list
    void deallocateServers(ServerNode*& head);

    //copy the server list from |source| into |destination|
    void copyServerList(ServerNode*& destination, ServerNode* source);
};

/////////////////////////////////////////////// COMMUNICATION NODE

/*
|AccountNode| provides a node for |Interface| to use in it's linear linked list. In addition to the
typical next pointer operations, |account| is an abstract base class pointer to |Communication|. The
derived classes of |Communication| are all perfect subsets of it. |Slack| however contains a unique
feature |reply| which can only be called with RTTI in the event of using the |account| pointer for
dynamic binding.
*/

class AccountNode
{
    public:
    /////////////////// CONSTRUCTORS

    AccountNode();
    AccountNode(Communication* _account);

    ~AccountNode();

    /////////////////// PUBLIC FUNCTIONS 

    Communication*& getAccount();
    AccountNode*& getNext();
    void setNext(AccountNode* _next);

    private:
    /////////////////// DATA 

    //The next |AccountNode| in the LLL
    AccountNode* next;

    //The abstract base class pointer, used for dynamic binding
    Communication* account;
};

/////////////////////////////////////////////// EMAIL THREAD // STACK 

/*
|EmailThread| manages a linear linked list in the form of a stack, using |Email| as the node. When
a new email is sent with |EmailServer|, a new instance of this class is allocated. Once that initial
email has been sent, the email can be replied to with |reply|. The original email and it's replies
are what create the stack that |EmailThread| manages.
*/

class EmailThread
{
    public:
    /////////////////// CONSTRUCTORS

    EmailThread();
    EmailThread(const EmailThread& other);
    EmailThread(const String& _sender);
    EmailThread(const String& _sender, const char* email, const char* recipient, const char* subject);

    ~EmailThread();

    /////////////////// PUBLIC FUNCTIONS 

    //send a new email into this stack
    void send(const String& sender);

    //display the entire thread, along with sub-threads
    //|prompt| can be supplied to have a unique prompt before each message displayed
    void display(const char* prompt = nullptr) const;

    //return |next|
    EmailThread*& getNext();

    //set |next| to |_next|
    void setNext(EmailThread* _next);

    private:
    /////////////////// DATA

    //the head of the linear linked list, or the top of the stack
    Email* top;

    //the next email thread in the |EmailServer|
    EmailThread* next;

    /////////////////// PRIVATE FUNCTIONS 

    //OVERLOADED FUNCTION
    //traverse to the bottom of the stack with |top|, displaying all messages
    void display(Email* top) const;
    void display(Email* top, const char* prompt) const;

    //copy this thread into |destination|, traversing with |top|
    void copy(Email*& destination, Email* top);
};

/////////////////////////////////////////////// MESSAGE THREAD // STACK 

/*
This stack is in the form of a linear linked list, where the underlying data is managed by the
|Message| class. Messages in all communication systems are stored in the form of a stack, so an
instance of this class will exist wherever threads are kept in a server.
*/

class MessageThread
{
    public:
    /////////////////// CONSTRUCTORS

    MessageThread();
    MessageThread(const MessageThread& other);
    MessageThread(const char* _threadName);

    ~MessageThread();

    /////////////////// PUBLIC FUNCTIONS 

    //display the name of the thread
    void displayName() const;

    //change |threadName| with user input 
    void changeName();

    //compare |_threadName| to |threadName|, true if they match
    bool isMatch(const String& other) const;

    //post to a thread with user input, taking in the user's handle
    //the new post will be a message inserted at the top of the stack
    //if |message| is null, prepare for user input
    void post(const String& userHandle, const char* message = nullptr);

    //step the user through a message thread, allowing them to reply to any messages along the way
    void reply(const String& userHandle);

    //display the entire thread, along with sub-threads
    //|prompt| can be supplied to have a unique prompt before each message displayed
    void display(const char* prompt = nullptr) const;

    //copy |other| into this message thread
    void copy(MessageThread& other);

    private:
    /////////////////// DATA

    //the name of the thread
    String threadName;

    //the head of the linear linked list, or the top of the stack
    Message* top;

    /////////////////// PRIVATE FUNCTIONS 

    //traverse the stack, letting the user reply to any message in the thread
    void reply(const String& userHandle, Message*& top);

    //OVERLOADED FUNCTION
    //traverse to the bottom of the stack with |top|, displaying all messages
    void display(Message* top) const;
    void display(Message* top, const char* prompt) const;

    //get valid char input from the user, which is used to navigate the thread and post replies
    //'n' : next message
    //'r' : reply
    //'q' : quit
    char getCharInput() const;

    //copy this thread into |destination|, traversing with |top|
    void copy(Message*& destination, Message* top);
};

/////////////////////////////////////////////// EMAIL // STACK NODE 

/*
An |Email| contains a message and just as a |Message| does, in addition to a recipient and
a subject for that email. This node type is managed by the |EmailThread| stack class.
*/

class Email : public String
{
    public:
    /////////////////// CONSTRUCTORS

    Email();
    Email(const Email& other);
    Email(const String& _sender);
    Email(const String& _sender, const char* email, const char* recipient, const char* subject);

    ~Email();

    /////////////////// PUBLIC FUNCTIONS 

    //display the user's email : |sender|, |recipient|, |subject|, and the email's contents
    void display() const;

    //return |next|
    Email*& getNext();

    //set |next| to |_next|
    void setNext(Email* _next);

    private:
    /////////////////// DATA

    //The sender's email addres
    String sender;

    //the recipient of this email
    //TODO support multiple recipients
    String recipient;

    //the subject of this email
    String subject;

    //the next email in this thread
    Email* next;
};

/////////////////////////////////////////////// MESSAGE // STACK NODE 

/*
|Message| manages the data involving a message in any of the derived |Communication| classes. In
addition to the char* that contains the text from the literal message, a linear linked list of
replies in the form of a stack will allow for proper message threading to occur. |Message| is a node
for the linear linked list managed by |Thread|. The char* that holds the message posted by the user
is in the inherited class |String|.
*/

class Message : public String
{
    public:
    /////////////////// CONSTRUCTORS

    Message();
    Message(const Message& other);
    Message(const String& _handle, const char* _message = nullptr);

    ~Message();

    /////////////////// PUBLIC FUNCTIONS

    //display the |handle| of the user that post the message, the |timestamp| and the post
    //display the thread of replies to this message
    void display() const;

    //reply to this message, |replies| handles this thread
    void reply(const String& userHandle);

    //return |next|
    Message*& getNext();

    //set |next| to |_next|
    void setNext(Message* _next);

    private:
    /////////////////// DATA 

    //the handle of the user that made the message
    String handle;

    //TODO a timestamp of when the message was created

    //the next message in the message stack : managed by |Thread| 
    Message* next;

    //the thread stack that contains replies to this message
    MessageThread replies;
};

/////////////////////////////////////////////// ABSTRACT BASE // SERVER

/*
Any class that is derived from the |Communication| abstract base class will contain 1 or more
pointers that point to a class in this hierarchy. This |Server| hierarchy is designed
to simulate a server that an account from the |Communication| hierarchy can then interact with.
*/

class Server
{
    public:
    /////////////////// CONSTRUCTORS

    Server();
    Server(const Server& other);
    Server(const char* _serverName);

    virtual ~Server();

    /////////////////// PURE VIRTUAL FUNCTIONS 

    //display server name and channel names
    //then display the current thread
    virtual void display() const = 0;

    //step the user through a message thread, allowing them to reply to any messages along the way
    virtual void reply(const String& userHandle) = 0;

    /////////////////// PUBLIC FUNCTIONS 

    //display server name
    void displayName() const;

    //change the server's name to |_serverName| with user input
    void changeName();

    //true if |_serverName| is a case sensitive match to this server's name
    bool isMatch(const char* _serverName) const;
    bool isMatch(const String& _serverName) const;

    protected:
    /////////////////// DATA

    //the name of the server
    String serverName;
};

/////////////////////////////////////////////// DERIVED // EMAIL SERVER

/*
This type of server manages a linear linked list of |Thread| objects, and is in the form of a stack.
Each new |EmailThread| added to the LLL is a new email. Either a new email can be sent with |send|
or an existing email replied to with |reply|. Replies to an existing email are managed by the
|EmailThread| stack.
*/

class EmailServer : public Server
{
    public:
    /////////////////// CONSTRUCTORS

    EmailServer();
    EmailServer(const EmailServer& other);
    EmailServer(const char* _key = nullptr);

    ~EmailServer();

    /////////////////// PUBLIC FUNCTIONS 

    //display server name and all email threads
    void display() const;

    //send an email, passing in the user's email address as |sender|
    void send(const String& sender, const char* email = nullptr,
    const char* recipient = nullptr, const char* subject = nullptr);

    //step the user through the |EmailThread| stack, allowing them to reply along the way
    void reply(const String& replier);

    private:
    /////////////////// DATA

    EmailThread* top;

    //the key this server is set to
    String key;

    /////////////////// PRIVATE FUNCTIONS 

    //traverse the stack with |top| displaying all threads
    void display(EmailThread* top) const;

    //traverse the stack, letting the user reply to any message in the thread
    void reply(const String& replier, EmailThread*& top);

    //get valid char input from the user, which is used to navigate the emails, and reply
    //'n' : next message
    //'r' : reply
    //'q' : quit
    char getCharInput() const;

    //copy the stack from |source| into |destination|
    void copy(EmailThread*& destination, EmailThread* source) const;
};

/////////////////////////////////////////////// DERIVED // CHANNEL SERVER

/*
This type of server manages an array of |Thread| objects. |Thread| manages an LLL stack, so
|ChannelServer| is consequently managing an array of linear linked list. Each index of the array is
a channel in the server. An account from the |Communication| hierarchy can use |ChannelServer| to
display, post, and reply to any of the available channels in this server.
*/

class ChannelServer : public Server
{
    public:
    /////////////////// CONSTRUCTORS

    ChannelServer(const char* _key = nullptr);
    ChannelServer(const ChannelServer& other);
    ChannelServer(const char* _serverName, const int _channelCount, const char* _key);

    ~ChannelServer();

    /////////////////// PUBLIC FUNCTIONS 

    //display server name and channel names
    //then display the current thread
    void display() const;

    //display the server name and channel names without the thread
    void displayNames() const;

    //HIERARCHY OUTLIER : RTTI REQUIRED
    //switch to a different channel in the server with |channelName|
    //if no channel is found that matches the user's string, return false
    //otherwise set |currentChannelIndex| to the matching index in |channels|
    bool changeChannel(const String& channelName);

    //display the current thread
    void displayThread() const;

    //post a message to the server's current linked channel with user input, taking in the user's handle
    //if |message| is null, prepare for user input
    void post(const String& userHandle, const char* message = nullptr);

    //step the user through a message thread, allowing them to reply to any messages along the way
    void reply(const String& userHandle);

    //compare |key| with |_key|, returning true if they match
    //this is a solution to keeping accounts that are unrelated to a specific server from accessing
    bool keyCheck(const String& _key) const;

    private:
    /////////////////// DATA

    //the number of channels in this server
    int channelCount;

    //the array of channels in this server, to be allocated to size |channelCount|
    MessageThread* channels;

    //the current channel index of |channels| the user is accessing through the server
    int currentChannelIndex;

    //the key this server is set to
    String key;

    /////////////////// PRIVATE FUNCTIONS

    //allocate the array of |Thread| objects
    //return false if the array has already been allocated, or if |channelCount| is invalid
    bool setupChannels(const int _channelCount);
};

/////////////////////////////////////////////// SERVER NODE

/*
This node is for a linear linked list of server pointers. These |Server| pointers are designed to
dereference a |Server| object that is managed elswhere. The node does not manage any dynamic memory,
but insead allows for the |Communication| derived classes to have access to a variety of |Server|
objects. The |Communication| derived classes manage this linear linked list.
*/

class ServerNode
{
    public:
    /////////////////// CONSTRUCTORS

    ServerNode();
    ServerNode(Server* _server);

    ~ServerNode();

    /////////////////// PUBLIC FUNCTIONS 

    Server*& getServer();
    ServerNode*& getNext();
    void setNext(ServerNode* _next);

    private:
    /////////////////// DATA

    //points to a server that exists in the system (not dynamically allocated by |ServerNode|)
    Server* server;

    //points to the next node in a linear data structure
    ServerNode* next;
};

#endif

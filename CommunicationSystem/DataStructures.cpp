/***** CLASS IMPLEMENTATION FILE *****/

//Sean Siders
//CS202
//Program 2 : Communication System
//10/30/2020

/*
All implementations of the class data structures are in this file. |EmailServer| manages a stack,
and |MessageServer| manages a linear linked list of stacks. A derived class from |Communication| is
designed to interact with one of these 2 types of servers to store all of the information involving
their messages.
*/

#include "DataStructures.h"

/////////////////////////////////////////////// DEFAULT CONSTRUCTORS 

EmailThread::EmailThread() : top(nullptr) {}

MessageThread::MessageThread() : top(nullptr) {}

Email::Email() : String(1000, '\n'), next(nullptr) {}

Message::Message() : next(nullptr), replies("Replies") {}

//get input from the user for the name of the server
Server::Server()
{
    std::cout << "ENTER SERVER NAME";
    serverName.getInput();
}

EmailServer::EmailServer(const char* _key) : top(nullptr), key(_key) {}

//get the number of desired channels from the user, then set up the array of LLL's
//|_key| is defaulted to null
ChannelServer::ChannelServer(const char* _key) : channels(nullptr), currentChannelIndex(0), key(_key)
{
    std::cout << "ENTER THE NUMBER OF DESIRED CHANNELS FOR THIS SERVER\nvalid range : (1, 5)";

    Int intBuffer;
    channelCount = intBuffer.getIntInput(1, 5);
    setupChannels(channelCount);
}

ServerNode::ServerNode() : server(nullptr), next(nullptr) {}

/////////////////////////////////////////////// COPY CONSTRUCTORS 

EmailThread::EmailThread(const EmailThread& other) : top(nullptr)
{
    //copy the stack from |other|
    copy(top, other.top);
}

MessageThread::MessageThread(const MessageThread& other) : threadName(other.threadName), top(nullptr)
{
    //copy the stack from |other|
    copy(top, other.top);
}

Email::Email(const Email& other) :
    String(other), sender(other.sender), recipient(other.recipient), subject(other.subject), next(nullptr)
{
}

Message::Message(const Message& other) :
    String(other), handle(other.handle), next(nullptr), replies(other.replies)
{
}

Server::Server(const Server& other) : serverName(other.serverName) {}

EmailServer::EmailServer(const EmailServer& other) : Server(other), top(nullptr)
{
    //copy the stack from |other|
    copy(top, other.top);
}

ChannelServer::ChannelServer(const ChannelServer& other) :
    Server(other), channels(nullptr), key(other.key)
{
    channelCount = other.channelCount;
    currentChannelIndex = other.currentChannelIndex;

    channels = new MessageThread[channelCount];

    //for pointer arithmetic
    MessageThread* sourceChannels = other.channels;

    //make a copy of each thread from |sourceChannels|
    for (int i = 0; i < channelCount; ++i)
    {
        channels[i].copy(*sourceChannels);
        ++sourceChannels;
    }
}

/////////////////////////////////////////////// INITIALIZATION CONSTRUCTORS 

EmailThread::EmailThread(const String& _sender, const char* email, const char* recipient, const char* subject)
{
    top = new Email(_sender, email, recipient, subject);
}

EmailThread::EmailThread(const String& _sender)
{
    top = new Email(_sender);
}

MessageThread::MessageThread(const char* _threadName) : threadName(_threadName), top(nullptr) {}

//take in the email's sender, passed from a user's email account
//get the email recipient, subject, and body with user input
Email::Email(const String& _sender) : String(1000, '\n'), sender(_sender)
{
    //recipient
    std::cout << "\nGETTING EMAIL INFORMATION\nRECIPIENT";
    recipient.getInput();

    //subject
    std::cout << "\nSUBJECT";
    subject.getInput();

    //email body
    std::cout << "\nEMAIL BODY";
    String::getInput();
}

//an email body was provided, default the recipient and subject to create a draft of the email
Email::Email(const String& _sender, const char* email, const char* recipient, const char* subject) :
    String(email), sender(_sender), recipient(recipient), subject(subject) {}

Message::Message(const String& _handle, const char* _message) :
    String(_message), handle(_handle), next(nullptr), replies("Replies") {}

Server::Server(const char* _serverName) : serverName(_serverName) {}

ChannelServer::ChannelServer(const char* _serverName, const int _channelCount, const char* _key) :
    Server(_serverName), channels(nullptr), currentChannelIndex(0), key(_key) {}
    
ServerNode::ServerNode(Server* _server) : next(nullptr)
{
    server = _server;
}

/////////////////////////////////////////////// DESTRUCTORS 

EmailThread::~EmailThread()
{
    delete top;
    top = nullptr;
    delete next;
    next = nullptr;
}

MessageThread::~MessageThread()
{
    delete top;
    top = nullptr;
}

Email::~Email()
{
    delete next;
    next = nullptr;
}

Message::~Message()
{
    delete next;
    next = nullptr;
}

Server::~Server() {}

EmailServer::~EmailServer()
{
    delete top;
}

ChannelServer::~ChannelServer()
{
    delete [] channels;
}

ServerNode::~ServerNode()
{
    server = nullptr;
    delete next;
    next = nullptr;
}

/////////////////////////////////////////////// EMAIL THREAD 

//send a new email into this stack
void EmailThread::send(const String& sender)
{
    //allocate a new |Email| object, passing in the sender's email, message, subject, and recipient
    //user input will be invoked via |String| if fields are null 
    Email* newEmail = new Email(sender);

    //if the stack is empty
    if (!top)
    {
        top = newEmail;
        return;
    }

    //hold onto the rest of the stack
    Email* hold = top;

    //assign the new top
    top = newEmail;

    //link the rest of the stack
    top->setNext(hold);
}

//WRAPPER
//display the entire thread, along with sub-threads
//|prompt| can be supplied to have a unique prompt before each message displayed
void EmailThread::display(const char* prompt) const
{
    std::cout << '\n';

    //determine whether a unique prompt will be displayed or not, as |prompt| is defaulted to null
    if (prompt) display(top, prompt);
    else display(top);
}

//RECURSIVE
//traverse to the bottom of the stack with |top|, displaying all messages
void EmailThread::display(Email* top) const
{
    if (!top) return;

    //display the email
    top->display();

    display(top->getNext());
}

//RECURSIVE
//traverse to the bottom of the stack with |top|, displaying all messages
//|prompt| can be supplied to have a unique prompt before each message displayed
void EmailThread::display(Email* top, const char* prompt) const
{
    if (!top) return;

    //display the prompt
    std::cout << prompt;

    //display the email 
    top->display();

    display(top->getNext(), prompt);
}

//copy this thread into |destination|, traversing with |top|
void EmailThread::copy(Email*& destination, Email* top)
{
    if (!top) return;

    destination = new Email(*top);

    copy(destination->getNext(), top->getNext());
}

//return |next|
EmailThread*& EmailThread::getNext()
{
    return next;
}

//set |next| to |_next|
void EmailThread::setNext(EmailThread* _next)
{
    next = _next;
}

/////////////////////////////////////////////// MESSAGE THREAD 

//display the name of the thread
void MessageThread::displayName() const
{
    threadName.display();
}

//change |threadName| with user input
void MessageThread::changeName()
{
    threadName.getInput();
}

//compare |_threadName| to |threadName|, true if they match
bool MessageThread::isMatch(const String& other) const
{
    return threadName.isMatch(other);
}

//post to a thread with user input, taking in the user's handle
//the new post will be a message inserted at the top of the stack
//if |message| is null, prepare for user input
void MessageThread::post(const String& userHandle, const char* message)
{
    //allocate a new message object, passing in the user handle
    //user input will be invoked via |String| if |message| is null
    Message* newPost = new Message(userHandle, message);

    //if the stack is empty
    if (!top)
    {
        top = newPost;
        return;
    }

    //hold onto the rest of the stack
    Message* hold = top;

    //assign the new top
    top = newPost;

    //link the rest of the stack
    top->setNext(hold);
}

//WRAPPER
//step the user through a message thread, allowing them to reply to any messages along the way
void MessageThread::reply(const String& userHandle)
{
    reply(userHandle, top);
}

//RECURSIVE
//traverse the stack, letting the user reply to any message in the thread
//'n' : next message
//'r' : reply
//'q' : quit
void MessageThread::reply(const String& userHandle, Message*& top)
{
    if (!top) return;

    std::cout << "\n<<<<<<<<<<<<<<< STEPPING >>>>>>>>>>>>>>>\n"
    << "VALID INPUT : 'n' 'r' 'q'";

    //display the message and thread of replies
    std::cout << "\n=======================================================\n";
    top->display();
    std::cout << "\n=======================================================\n\n";

    //get a char from the user
    char input = getCharInput();

    //reply to the current message, passing the user handle
    if ('r' == input)
    {
        std::cout << "NEW REPLY";
        top->reply(userHandle);
    }

    //end traversal
    if ('q' == input) return;

    reply(userHandle, top->getNext());
}

//WRAPPER
//display the entire thread, along with sub-threads
//|prompt| can be supplied to have a unique prompt before each message displayed
void MessageThread::display(const char* prompt) const
{
    std::cout << '\n';

    //determine whether a unique prompt will be displayed or not, as |prompt| is defaulted to null
    if (prompt) display(top, prompt);
    else display(top);
}

//RECURSIVE
//traverse to the bottom of the stack with |top|, displaying all messages
void MessageThread::display(Message* top) const
{
    if (!top) return;

    //display message and thread of replies
    top->display();

    display(top->getNext());
}

//RECURSIVE
//traverse to the bottom of the stack with |top|, displaying all messages
//|prompt| can be supplied to have a unique prompt before each message displayed
void MessageThread::display(Message* top, const char* prompt) const
{
    if (!top) return;

    //display the prompt
    std::cout << prompt;

    //display message and thread of replies
    top->display();

    display(top->getNext(), prompt);
}

//get valid char input from the user, which is used to navigate the thread and post replies
//'n' : next message
//'r' : reply
//'q' : quit
char MessageThread::getCharInput() const
{
    char input = '\0';

    std::cin >> input;
    std::cin.ignore(100, '\n');
    input = tolower(input);

    while ('n' != input && 'p' != input && 'r' != input && 'q' != input)
    {
        std::cout << "\nINVALID INPUT\nCONTROLS\n"
        << "'n' : next message\n"
        << "'r' : reply\n"
        << "'q' : quit\n\n>>> ";

        std::cin >> input;
        std::cin.ignore(100, '\n');
    }

    return input;
}

//copy |other| into this message thread
void MessageThread::copy(MessageThread& other)
{
    copy(top, other.top);
}

//copy this thread into |destination|, traversing with |top|
void MessageThread::copy(Message*& destination, Message* top)
{
    if (!top) return;

    destination = new Message(*top);

    copy(destination->getNext(), top->getNext());
}

/////////////////////////////////////////////// EMAIL // STACK NODE 

//display the user's email : |sender|, |recipient|, |subject|, and the email's contents
void Email::display() const
{
    sender.display();
    std::cout << " ::: ";

    //display message
    String::display();
}

//return |next|
Email*& Email::getNext()
{
    return next;
}

//set |next| to |_next|
void Email::setNext(Email* _next)
{
    next = _next;
}

/////////////////////////////////////////////// MESSAGE // STACK NODE

//display the |handle| of the user that post the message, the |timestamp| and the post
//display the thread of replies to this message
void Message::display() const
{
    handle.display();
    std::cout << " >>> ";

    //display message
    String::display();
    
    //display reply thread
    replies.display("\t-R-");
}

//reply to this message, |replies| handles this thread
void Message::reply(const String& userHandle)
{
    replies.post(userHandle);
}

//return |next|
Message*& Message::getNext()
{
    return next;
}

//set |next| to |_next|
void Message::setNext(Message* _next)
{
    next = _next;
}

/////////////////////////////////////////////// ABSTRACT BASE // SERVER 

//display server name
void Server::displayName() const
{
    std::cout << "\nSERVER : ";
    serverName.display();
    std::cout << '\n';
}

//change the server's name with user input
void Server::changeName()
{
    std::cout << "NEW SERVER NAME\n";
    serverName.getInput();
}

//true if |_serverName| is a case sensitive match to this server's name
bool Server::isMatch(const char* _serverName) const
{
    return serverName.isMatch(_serverName);
}

bool Server::isMatch(const String& _serverName) const
{
    return serverName.isMatch(_serverName);
}

/////////////////////////////////////////////// EMAIL SERVER

//WRAPPER
//display server name and all email threads
void EmailServer::display() const
{
    //display the email server name
    displayName();

    display(top);
}

//RECURSIVE
//traverse the stack with |top| displaying all threads
void EmailServer::display(EmailThread* top) const
{
    if (!top) return;
    top->display();
    display(top->getNext());
}

//send an email, passing in the user's email address as |sender|
void EmailServer::send(const String& sender, const char* email, const char* recipient, const char* subject)
{
    //if an email was supplied, pass it in, otherwise user input will be handled by |Email|
    EmailThread* newEmail = nullptr;

    if (email) newEmail = new EmailThread(sender, email, recipient, subject);
    else newEmail = new EmailThread(sender);

    //if the stack is empty
    if (!top)
    {
        top = newEmail;
        return;
    }

    //hold onto the rest of the stack
    EmailThread* hold = top;

    //assign the new top
    top = newEmail;

    //link the rest of the stack
    top->setNext(hold);
}

//WRAPPER
//step the user through a message thread, allowing them to reply to any messages along the way
void EmailServer::reply(const String& replier)
{
    reply(replier, top);
}

//RECURSIVE
//traverse the stack, letting the user reply to any message in the thread
//'n' : next message
//'r' : reply
//'q' : quit
void EmailServer::reply(const String& replier, EmailThread*& top)
{
    if (!top) return;

    std::cout << "\n<<<<<<<<<<<<<<< STEPPING >>>>>>>>>>>>>>>\n"
    << "VALID INPUT : 'n' 'r' 'q'";

    //display the message and thread of replies
    std::cout << "\n=======================================================\n";
    top->display();
    std::cout << "\n=======================================================\n\n";

    //get a char from the user
    char input = getCharInput();

    //reply to the current message, passing the user handle
    if ('r' == input)
    {
        std::cout << "NEW REPLY";
        top->send(replier);
    }

    //end traversal
    if ('q' == input) return;

    reply(replier, top->getNext());
}

//get valid char input from the user, which is used to navigate the thread and post replies
//'n' : next message
//'r' : reply
//'q' : quit
char EmailServer::getCharInput() const
{
    char input = '\0';

    std::cin >> input;
    std::cin.ignore(100, '\n');
    input = tolower(input);

    while ('n' != input && 'p' != input && 'r' != input && 'q' != input)
    {
        std::cout << "\nINVALID INPUT\nCONTROLS\n"
        << "'n' : next message\n"
        << "'r' : reply\n"
        << "'q' : quit\n\n>>> ";

        std::cin >> input;
        std::cin.ignore(100, '\n');
    }

    return input;
}

//copy the stack from |source| into |destination|
void EmailServer::copy(EmailThread*& destination, EmailThread* source) const
{
    if (!source) return;

    destination = new EmailThread(*source);

    copy(destination->getNext(), source->getNext());
}

/////////////////////////////////////////////// CHANNEL SERVER

//display server name and channel names
//then display the current thread
void ChannelServer::display() const
{
    displayNames();
    displayThread();
}

//display the server name and channel names without the thread
void ChannelServer::displayNames() const
{
    displayName();

    //if there are channels in the server, display their names
    if (channels)
    {
        std::cout << "==== CHANNELS\n" << "=============\n";

        for (int i = 0; i < channelCount; ++i)
        {
            //if the current channel is the linked one, display unique prompt
            if (i == currentChannelIndex) std::cout << "LINKED ---> ";
            else std::cout << "           ";

            channels[i].displayName();
            std::cout << '\n';
        }

        std::cout << '\n';
    }
}

//display the current channel thread
void ChannelServer::displayThread() const
{
    if (!channels) return;

    std::cout << "CHANNEL : ";

    //display channel name
    channels[currentChannelIndex].displayName();
    std::cout << '\n';

    //display thread
    channels[currentChannelIndex].display();
}

//allocate the array of |Thread| objects
//return false if the array has already been allocated, or if |channelCount| is invalid
bool ChannelServer::setupChannels(const int _channelCount)
{
    if (channels || _channelCount <= 0) return false;

    //if _channelCount is too large, set the default max of the member |channelCount|
    if (_channelCount <= CHANNEL_MAX) channelCount = _channelCount; 
    else channelCount = CHANNEL_MAX;

    //allocate array
    channels = new MessageThread[channelCount];

    std::cout << "\nGETTING SERVER | ";
    serverName.display();
    std::cout << " | CHANNEL NAMES\n\n";

    //set a name for each channel
    for (int i = 0; i < channelCount; ++i)
    {
        std::cout << "CHANNEL " << i + 1;
        channels[i].changeName();
    }

    return true;
}

//HIERARCHY OUTLIER : RTTI REQUIRED
//switch to a different channel in the server with |channelName|
//if no channel is found that matches the user's string, return false
//otherwise set |currentChannelIndex| to the matching index in |channels|
bool ChannelServer::changeChannel(const String& channelName)
{
    bool matched = false;

    //iterate through the array, comparing channel names
    for (int i = 0; i < channelCount && !matched; ++i)
    {
        matched = channels[i].isMatch(channelName);

        //set the index when a match is found
        if (matched) currentChannelIndex = i;
    }

    return matched;
}

//post a message to the server's current linked channel with user input, taking in the user's handle
//if |message| is null, prepare for user input
void ChannelServer::post(const String& userHandle, const char* message)
{
    if (channels) channels[currentChannelIndex].post(userHandle, message);
}

//step the user through a message thread, allowing them to reply to any messages along the way
void ChannelServer::reply(const String& userHandle)
{
    if (channels) channels[currentChannelIndex].reply(userHandle);
}

//compare |key| with |_key|, returning true if they match
//this is a solution to keeping accounts that are unrelated to a specific server from accessing
bool ChannelServer::keyCheck(const String& _key) const
{
    return key.isMatch(_key);
}

/////////////////////////////////////////////// SERVER NODE 

Server*& ServerNode::getServer()
{
    return server;
}

ServerNode*& ServerNode::getNext()
{
    return next;
}

void ServerNode::setNext(ServerNode* _next)
{
    next = _next;
}

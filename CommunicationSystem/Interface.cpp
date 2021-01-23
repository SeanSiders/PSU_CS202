/***** CLASS IMPLEMENTATION FILE *****/

//Sean Siders
//CS202
//Program 2 : Communication System
//10/30/2020

/*
|Interface| is the top level data structure for the entire communication system. It manages 2
linear linked lists, 1 for the accounts derived from |Communication| in |CommunicationSystem.h| and
another for the servers derived from |Server| in |DataStructures.h|. |Interface| is the client
entry point for the communication system.
*/

#include "DataStructures.h"

/////////////////////////////////////////////// DEFAULT CONSTRUCTORS 

Interface::Interface() : aHead(nullptr), sHead(nullptr) {}

AccountNode::AccountNode() : next(nullptr), account(nullptr) {}

/////////////////////////////////////////////// COPY CONSTRUCTORS 

Interface::Interface(const Interface& other)
{
    copyAccountList(aHead, other.aHead);
    copyServerList(sHead, other.sHead);
}

/////////////////////////////////////////////// INITIALIZATION CONSTRUCTORS 

AccountNode::AccountNode(Communication* _account) : next(nullptr), account(_account) {}

/////////////////////////////////////////////// DESTRUCTORS 

Interface::~Interface()
{
    //deallocation dealt with in |AccountNode| recursively
    delete aHead;

    //removal is dealt with in |Interface| recursively
    deallocateServers(sHead);
}

AccountNode::~AccountNode()
{
    delete account;
    delete next;
    next = nullptr;
}

/////////////////////////////////////////////// COMMUNICATION INTERFACE

//prompt a menu of options to the user, and take user input to perform an action
void Interface::menu() 
{
    std::cout << "\nCOMMUNICATION SYSTEM\n"
    << "====================\n"
    << "select an option with integer input\n\n"
    << "0) quit\n"
    << "1) create an account (Slack, Discord, or Gmail)\n"
    << "2) create a server and optionally link to an account\n"
    << "3) open an existing account to interact with it\n"
    << "4) display all accounts and their current threads\n"
    << "5) display all servers\n"
    << "6) remove an account\n"
    << "7) remove a server\n";

    switch(intBuffer.getIntInput(0, 7))
    {
        case 0: return;
        case 1: createAccount(); break;
        case 2: createServer(); break;
        case 3: openAccount(); break;
        case 4: fullDisplay(aHead); break;
        case 5: displayServers(sHead); break;
        case 6: removeAccount(); break;
        case 7: removeServer(); break;

        default: break;
    }

    menu();
}

//traverse with |head| displaying all of the account names
void Interface::displayAccounts(AccountNode* head) const
{
    if (!head) return;

    head->getAccount()->displayName();
    std::cout << '\n';

    displayAccounts(head->getNext());
}

//traverse with |head| displaying all accounts in the list, and their current server threads
void Interface::fullDisplay(AccountNode* head) const
{
    if (!head) return;
    head->getAccount()->display();
    fullDisplay(head->getNext());
}

//prompt a menu to create one of the 3 account types, then insert it into the |AccountNode| list
void Interface::createAccount()
{
    std::cout << "\nACCOUNT TYPES\n"
    << "select an option with integer input\n\n"
    << "0) quit\n"
    << "1) Slack\n"
    << "2) Discord\n"
    << "3) Gmail\n\n";

    insertAccount(intBuffer.getIntInput(0, 3));
}

//PUBLIC WRAPPER
void Interface::insertAccount(Communication* newAccount)
{
    insertAccount(aHead, newAccount);
}

//PRIVATE WRAPPER
//insert a new account whos type is specified with |index| into the |AccountNode| list
void Interface::insertAccount(const int index)
{
    //to hold the new account
    Communication* newAccount = nullptr;

    switch(index)
    {
        case 0: return;
        case 1: newAccount = new Slack; break;
        case 2: newAccount = new Discord; break;
        case 3: newAccount = new Gmail; break;

        default: break;
    }

    if (!aHead) aHead = new AccountNode(newAccount);
    else insertAccount(aHead, newAccount);
}

//RECURSIVE
//check that the account name is unique to any other accounts of that type in the list
//insert at the end if it is unique, then return true, otherwise false
bool Interface::insertAccount(AccountNode*& head, Communication* newAccount)
{
    //end of list reached, account is unique
    if (!head)
    {
        head = new AccountNode(newAccount);
        return true;
    }

    //if the account data matches the data in |head| return false, otherwise continue traversal
    return ((head->getAccount()->isMatch(*newAccount)) ?
    false : insertAccount(head->getNext(), newAccount));
}

//open an existing account in the account list
//prompt the user with options to interact with the account, such as post, display, or reply
void Interface::openAccount()
{
    if (!aHead)
    {
        std::cout << "\nWARNING : NO ACCOUNTS EXIST\n\n";
        return;
    }
    
    //display available accounts
    std::cout << "\nAVAILABLE ACCOUNTS\n"
    << "==================\n";

    displayAccounts(aHead);

    std::cout << "\nENTER THE ACCOUNT NAME YOU WOULD LIKE TO OPEN";
    stringBuffer.getInput();

    //attempt to retrieve a matching account
    Communication* account = retrieveAccount(stringBuffer, aHead);

    //if retrieve failed to find a match
    if (!account)
    {
        std::cout << "\nNO ACCOUNT FOUND\n\n";
        return;
    }

    //bring the opened account into a user menu
    accountMenu(account);
}

//////// RUN TIME TYPE IDENTIFICATION
//attempt to dynamic cast into the overloaded |accountMenu|
void Interface::accountMenu(Communication*& account)
{
    if (!accountMenu(dynamic_cast<Slack*>(account)) &&
        !accountMenu(dynamic_cast<Discord*>(account)) &&
        !accountMenu(dynamic_cast<Gmail*>(account)))
    {
        std::cout << "WARNING : account open failed\n\n";
    }
}

//OVERLOADED FUNCTION
//prompt a menu unique to the account type passed in
//return false if |account| is null

////// SLACK MENU

bool Interface::accountMenu(Slack* account)
{
    if (!account) return false;

    std::cout << "\n<<<<<<<<<<<<<<< SLACK MENU >>>>>>>>>>>>>>>\nhandle : ";
    account->displayName();

    std::cout << "\nenter an option with integer input\n"
    << "0) quit\n"
    << "1) post\n"
    << "2) reply to a post\n"
    << "3) display all threads\n"
    << "4) link a server to this account\n"
    << "5) switch the current server\n"
    << "6) switch the channel within the current server\n"
    << "7) remove a server from this account\n\n";

    return (accountCall(account) ? accountMenu(account) : true);
}

//get integer input from the user to call one of the procedures on an account
bool Interface::accountCall(Slack* account)
{
    switch(intBuffer.getIntInput(0, 7))
    {
        case 0: return false;

        case 1: account->post(); break;
        case 2: account->reply(); break;
        case 3: account->display(); break;

        //get the name of the server to add to the account, then attempt the link
        case 4:
            std::cout << "ENTER THE SERVER NAME TO LINK THE ACCOUNT TO";

            stringBuffer.getInput();

            if (!linkServer(account, stringBuffer, sHead)) std::cout << "SERVER LINK FAILED\n\n";
            else std::cout << "SERVER SUCCESSFULLY LINKED\n\n";

            break;
        
        //display the current linked servers for this account, then attempt to switch servers
        case 5:
            account->displayServerList();

            std::cout << "ENTER THE SERVER NAME TO SWITCH TO";
            stringBuffer.getInput();

            if (!account->setLinkedServer(stringBuffer)) std::cout << "SERVER NOT LINKED TO THIS ACCOUNT\n\n";
            else std::cout << "SERVER SUCCESSFULLY SWITCHED\n\n";

            break;

        case 6: account->setLinkedChannel(); break;

        //display the current linked servers for this account, then attempt a removal
        case 7:
            account->displayServerList();

            std::cout << "\nENTER THE SERVER NAME TO REMOVE";
            stringBuffer.getInput();

            if (!account->removeServer(stringBuffer)) std::cout << "SERVER NOT LINKED TO THIS ACCOUNT\n\n";
            else std::cout << "SERVER SUCCESSFULLY REMOVED\n\n";

            break;

        default: break;
    }

    return true;
}

////// DISCORD MENU

bool Interface::accountMenu(Discord* account)
{
    if (!account) return false;

    std::cout << "\n=============== DISCORD MENU ===============\nhandle : ";
    account->displayName();

    std::cout << "\nenter an option with integer input\n"
    << "0) quit\n"
    << "1) post\n"
    << "2) display all threads\n"
    << "3) link a server to this account\n"
    << "4) switch the current server\n"
    << "5) switch the channel within the current server\n"
    << "6) remove a server from this account\n\n";

    return (accountCall(account) ? accountMenu(account) : true);
}

//get integer input from the user to call one of the procedures on an account
bool Interface::accountCall(Discord* account)
{
    switch(intBuffer.getIntInput(0, 6))
    {
        case 0: return false;

        case 1: account->post(); break;
        case 2: account->display(); break;

        //get the name of the server to add to the account, then attempt the link
        case 3:
            std::cout << "ENTER THE SERVER NAME TO LINK THE ACCOUNT TO";

            stringBuffer.getInput();

            if (!linkServer(account, stringBuffer, sHead)) std::cout << "SERVER LINK FAILED\n\n";
            else std::cout << "SERVER SUCCESSFULLY LINKED\n\n";

            break;
        
        //display the current linked servers for this account, then attempt to switch servers
        case 4:
            account->displayServerList();

            std::cout << "ENTER THE SERVER NAME TO SWITCH TO";
            stringBuffer.getInput();

            if (!account->setLinkedServer(stringBuffer)) std::cout << "SERVER NOT LINKED TO THIS ACCOUNT\n\n";
            else std::cout << "SERVER SUCCESSFULLY SWITCHED\n\n";

            break;

        case 5: account->setLinkedChannel(); break;

        //display the current linked servers for this account, then attempt a removal
        case 6:
            account->displayServerList();

            std::cout << "\nENTER THE SERVER NAME TO REMOVE";
            stringBuffer.getInput();

            if (!account->removeServer(stringBuffer)) std::cout << "SERVER NOT LINKED TO THIS ACCOUNT\n\n";
            else std::cout << "SERVER SUCCESSFULLY REMOVED\n\n";

            break;

        default: break;
    }

    return true;
}

////// GMAIL MENU

bool Interface::accountMenu(Gmail* account)
{
    if (!account) return false;
    
    std::cout << "\n*************** GMAIL MENU ***************\nhandle : ";
    account->displayName();

    std::cout << "\nenter an option with integer input\n"
    << "0) quit\n"
    << "1) send an email\n"
    << "2) reply to an existing email\n"
    << "3) display all emails\n"
    << "4) add a server to the account\n"
    << "5) switch the current server\n"
    << "6) remove a server from this account\n\n";

    return (accountCall(account) ? accountMenu(account) : true);
}

//get integer input from the user to call one of the procedures on an account
bool Interface::accountCall(Gmail* account)
{
    switch(intBuffer.getIntInput(0, 6))
    {
        case 0: return false;

        case 1: account->post(); break;
        case 2: account->reply(); break;
        case 3: account->display(); break;

        //get the name of the server to add to the account, then attempt the link
        case 4:
            std::cout << "ENTER THE SERVER NAME TO LINK THE ACCOUNT TO";

            stringBuffer.getInput();

            if (!linkServer(account, stringBuffer, sHead)) std::cout << "SERVER LINK FAILED\n\n";
            else std::cout << "SERVER SUCCESSFULLY LINKED\n\n";

            break;
        
        //display the current linked servers for this account, then attempt to switch servers
        case 5:
            account->displayServerList();

            std::cout << "ENTER THE SERVER NAME TO SWITCH TO";
            stringBuffer.getInput();

            if (!account->setLinkedServer(stringBuffer)) std::cout << "SERVER NOT LINKED TO THIS ACCOUNT\n\n";
            else std::cout << "SERVER SUCCESSFULLY SWITCHED\n\n";

            break;

        //display the current linked servers for this account, then attempt a removal
        case 6:
            account->displayServerList();

            std::cout << "\nENTER THE SERVER NAME TO REMOVE";
            stringBuffer.getInput();

            if (!account->removeServer(stringBuffer)) std::cout << "SERVER NOT LINKED TO THIS ACCOUNT\n\n";
            else std::cout << "SERVER SUCCESSFULLY REMOVED\n\n";

            break;

        default: break;
    }

    return true;
}

//attempt to find an account that matches the name |accountName|, traversing with |head|
Communication* Interface::retrieveAccount(const String& accountName, AccountNode* head)
{
    if (!head) return nullptr;

    if (head->getAccount()->isMatch(accountName)) return head->getAccount();

    return retrieveAccount(accountName, head->getNext());
}

//attempt to remove an existing account with user input
void Interface::removeAccount()
{
    //if there are no accounts in the list
    if (!aHead)
    {
        std::cout << "\nWARNING : there are no accounts\n\n";
        return; 
    }

    //display the account list
    displayAccounts(aHead);

    //get user input
    std::cout << "\nENTER THE ACCOUNT BY NAME THAT YOU WOULD LIKE REMOVED\n";
    stringBuffer.getInput();

    if (removeAccount(stringBuffer, aHead)) std::cout << "\nACCOUNT SUCCESSFULLY REMOVED\n\n";
    else std::cout << "\nNO ACCOUNT MATCHED THAT NAME\n\n";
}

//traverse the account list with |head| attempting to remove an account with name |toRemove|
//false if no match was found
bool Interface::removeAccount(const String& toRemove, AccountNode*& head)
{
    //end of list, no match was found
    if (!head) return false;

    //a match was found, remove the account
    if (head->getAccount()->isMatch(toRemove))
    {
        //hold onto the rest of the list
        AccountNode*& hold = head->getNext();

        //deallocate
        head->setNext(nullptr);
        delete head;

        //link up
        head = hold;

        return true;
    }

    return removeAccount(toRemove, head->getNext());
}

//copy the account list from |source| into |destination|
void Interface::copyAccountList(AccountNode*& destination, AccountNode* source)
{
    if (!source) return;
    destination = new AccountNode(*source);
    copyAccountList(destination->getNext(), source->getNext());
}

//display the list of servers, traversing with |head|
void Interface::displayServers(ServerNode* head) const
{
    if (!head) return;
    head->getServer()->displayName();
    displayServers(head->getNext());
}

//prompt a menu to create a server for one of the 3 account types, then insert it into the server list
void Interface::createServer()
{
    std::cout << "\nSERVER TYPES\n"
    << "select an option with integer input\n\n"
    << "0) quit\n"
    << "1) Slack\n"
    << "2) Discord\n"
    << "3) Gmail\n\n";

    insertServer(intBuffer.getIntInput(0, 3));
}

//PUBLIC WRAPPER
//insert |newServer| into the server list
void Interface::insertServer(Server* newServer)
{
    insertServer(sHead, newServer);
}

//make a server that cooresponds to the type of account specified, then insert it into the server list
void Interface::insertServer(const int index)
{
    Server* newServer = nullptr;

    //|newServer| will either be a |ChannelServer| or |EmailServer| depending on the account type
    switch(index)
    {
        case 0: return;
        case 1: newServer = new ChannelServer("SLACK"); break;
        case 2: newServer = new ChannelServer("DISCORD"); break;
        case 3: newServer = new EmailServer("GMAIL"); break;

        default: break;
    }

    insertServer(sHead, newServer);

    //link the server to an account if there are any
    if (aHead)
    {
        //|key| will represent the type of account that the server should link to
        String key;

        switch(index)
        {
            case 1: key.setString("SLACK"); break;
            case 2: key.setString("DISCORD"); break;
            case 3: key.setString("GMAIL"); break;

            default: break;
        }

        displayAccounts(aHead);

        std::cout << "ENTER THE ";
        key.display();
        std::cout << " ACCOUNT NAME TO LINK THIS SERVER TO OR ENTER 0 TO QUIT";

        //|stringBuffer| will hold the account name
        stringBuffer.getInput();

        //if the user decided to quit
        if (stringBuffer.isMatch("0")) return;

        if (!linkServer(sHead->getServer(), stringBuffer, key, aHead)) std::cout << "\nLINK FAILED\n\n";
        else std::cout << "\nACCOUNT SUCCESSFULLY LINKED TO SERVER\n\n";
    }
}

//insert |server| into the head of the server list
void Interface::insertServer(ServerNode*& head, Server* server)
{
    //insert the new server at the head of the server list
    if (!head) head = new ServerNode(server);
    else
    {
        //hold onto the rest of the list
        ServerNode* hold = sHead;

        //allocate
        sHead = new ServerNode(server);

        //link the rest of the list
        sHead->setNext(hold);
    }
}

//OVERLOADED FUNCTION
//traverse the account list with |head|
//link |server| to an account that matches the |accountName| and |key|
//false if no match is found or if the server is already linked to the account
bool Interface::linkServer(Server* server, const String& accountName, const String& key, AccountNode* head)
{
    //end of list, no match found
    if (!head) return false;

    if (head->getAccount()->isMatch(accountName, key))
    {
        //false if the server is already linked to that account
        if (!head->getAccount()->addServer(server))
        {
            std::cout << "\nSERVER ALREADY LINKED TO THIS ACCOUNT";
            return false;
        }

        return true;
    }

    return linkServer(server, accountName, key, head->getNext());
}

//traverse the server list with |head| to link a server with name |serverName| to |account|
//false if no match is found
bool Interface::linkServer(Communication* account, const String& serverName, ServerNode* head)
{
    if (!head) return false;

    if (head->getServer()->isMatch(serverName))
    {
        if(!account->addServer(head->getServer()))
        {
            std::cout << "\nSERVER LINK FAILED";
            return false;
        }

        return true;
    }

    return linkServer(account, serverName, head->getNext());
}

//attempt to remove an existing server with user input
void Interface::removeServer()
{
    //if there are no servers in the list
    if (!sHead)
    {
        std::cout << "\nWARNING : there are no servers\n\n";
        return; 
    }

    //display the account list
    displayServers(sHead);

    //get user input
    std::cout << "\nENTER THE SERVER BY NAME THAT YOU WOULD LIKE REMOVED\n";
    stringBuffer.getInput();

    if (removeServer(stringBuffer, sHead)) std::cout << "\nSERVER SUCCESSFULLY REMOVED\n\n";
    else std::cout << "\nNO SERVER MATCHED THAT NAME\n\n";
}

//traverse the server list with |head| attempting to remove a server with name |toRemove|
//false if no match was found
bool Interface::removeServer(const String& toRemove, ServerNode*& head)
{
    //end of list, no match was found
    if (!head) return false;

    //a match was found, remove the account
    if (head->getServer()->isMatch(toRemove))
    {
        //unlink accounts from the server, catching the number of unlinks
        int unlinkCount = unlinkServer(toRemove, aHead);

        if (unlinkCount)
        {
            std::cout << '\n' << unlinkCount << " ACCOUNTS UNLINKED FROM : ";
            toRemove.display();
            std::cout << "\n\n";
        }

        //hold onto the rest of the list
        ServerNode* hold = head->getNext();

        //deallocate
        head->setNext(nullptr);
        delete head->getServer();
        delete head;

        //link up
        head = hold;

        return true;
    }

    return removeServer(toRemove, head->getNext());
}

//in the event of server being removed from the interface
//any account that contains a pointer to that server must set the pointer to null
//traverse the account list with |head| unlinking the server from any matching accounts
//return the number of accounts unlinked
int Interface::unlinkServer(const String& toUnlink, AccountNode* head)
{
    if (!head) return 0;

    return unlinkServer(toUnlink, head->getNext()) +
    (head->getAccount()->removeServer(toUnlink)) ? 1 : 0;
}

//deallocate the server list
void Interface::deallocateServers(ServerNode*& head)
{
    if (!head) return;

    //hold onto the rest of the list
    ServerNode* hold = head->getNext();

    //deallocate head
    delete head->getServer();
    head->setNext(nullptr);
    delete head;

    deallocateServers(hold);
}

//copy the server list from |source| into |destination|
void Interface::copyServerList(ServerNode*& destination, ServerNode* source)
{
    if (!source) return;
    destination = new ServerNode(*source);
    copyServerList(destination->getNext(), source->getNext());
}

/////////////////////////////////////////////// COMMUNICATION NODE

Communication*& AccountNode::getAccount()
{
    return account;
}

AccountNode*& AccountNode::getNext()
{
    return next;
}

void AccountNode::setNext(AccountNode* _next)
{
    next = _next;
}

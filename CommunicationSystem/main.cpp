/***** MAIN ENTRY POINT FILE *****/

//Sean Siders
//CS202
//Program 2 : Communication System
//10/30/2020

/*
|Interface| is the entry point for a client to access the communication system. From there,
accounts can be made, as well as servers for those accounts to interact with. The result is a
polymorphic messaging system.
*/

#include "CommunicationSystem.h"

int main()
{
    Interface interface;

    interface.menu();
    return 0;
}




> Sean Siders
> CS 202
> 11/04/2020
> Program 3 Design // Pokémon!
# Game Objects
## Interface *// user interface* (Base)
>Member
>- RNG

This will be the front end interface of the program, prompting the user with helpful information and dealing with all user input. The **String** and **Int** classes will be used as user input buffers. Either **Region** or **Arena** will provide the user with the gameplay interface, depending on the events happening in game. **Region** will simulate the real world and **Arena** will be exclusively for Pokémon battles between **User** and **NPC**. **RNG** will be used by both derived interface classes, **Region** and **Arena**, to simulate a factor of chance in the gameplay.

#### Region *// primary gameplay interface (Derived)*
>Members
>- Name
>- Time
>- Pokémon array *// daytime*
>- Pokémon array *// nighttime*
>- NPC array
>- Battle arena

This interface will manage the random **Pokémon** encounters, as well as the **NPC** encounters where battles will occur. A day in the game lasts 10 minutes total, making the available Pokémon encounters change from daytime to nighttime, and vice versa every 5 minutes, this will be managed by *Time*. Initially, a NPC encounter will happen for every 2 Pokémon encounters. When an NPC encounter happens the **Arena** member of this class will take over as the interface to simulate a Pokémon battle.

#### Arena *// temporary gameplay interface* (Derived)
>Members
>- User pointer
>- NPC pointer
>- RNG

When a **User** encounters an **NPC**, as determined by **Region**, the **Arena** interface will take over, simulating a Pokémon battle between the two game actors. The **NPC** will be provided by the array of NPCs within **Region**. The battle will be turn based, choosing 1 Pokémon at a time to call out. The **NPC** will iterate through their Pokémon array until it is depleted and the **User** claims victory. **RNG** will be used to determine with moves the NPC's Pokémon uses in battle.

## Trainer *// game actor* (Base)
>Members
>- Trainer Name

Either the user or an NPC will use this hierarchy to represent actual Pokémon trainers in the game.
### User (Derived)
>Members
>- 2-3 Tree of Pokémon caught

This class will be for the user of the game, and will interact primarily with the data structure that stores the Pokémon that the user has caught.
### NPC (Derived)
>Members
>- array of Pokémon
 
These objects will be procedurally generated either by **Region** or another unique class if the problem becomes too complex. **User** will interact with the **NPC** objects when a trainer battle occurs. In battle, the NPC will go through all of their Pokémon in the array, as the user *hopefully* climbs their way to victory.

## Pokémon *// game actor*
>Members
>-  Name
>-  Nickname
>- Type
>- Health stat
>- Attack stat
>- Defense stat
>- Speed stat
>- % Chance the Pokémon will be caught
>- Moves array *// size = 4*

>Operator Overloads
>- = *Making a copy of RHS into LHS*
>- += / -= *Increase or decrease Pokémon's health stat, if time permits, a **stat** class will be implemented*
>- == *Determining if two Pokémon match, including the nickname*

Pokémon will be procedurally generated in a similar way to NPCs, which will be handled either by **Region** or another class that **Region** contains as a member. Every Pokémon will have a constant name, unique stats that will be used as a factor in battle, and a constant % catch rate that will be used when **User** tries to catch this Pokémon. These members will be set during procedural generation. Nickname on the other hand, will be determined by **User** at the time of catching this Pokémon. A Pokémon can have up to 4 moves at a time., which **User** can teach by interacting with the decide to teach a Pokémon a move, by retrieving one from the *array of DLLs*.

## Move (Base)
>Members
>- Name
>- Base power
>- Stat boost / buff

>Operator Overloads
>- += / -= *Increase or decrease the base power*
>- < / > / <= / >= / == *To compare base powers between moves*

Any move that a Pokémon can use in battle will be managed by this hierarchy. There are essentially 3 different types of moves. The first will only require the base **Move** class, and has a base power of 0. This type of move will buff one or more of the Pokémon's stats. The other two moves are the offensive **Attack** and defensive **Defense**. Stat boosts are possible for any type of move.

#### Attack (Derived)
All offense moves that subtract from the opposing Pokémon's health stat will be managed by this derived class. The opposing Pokémon can either choose to use a **Defense** move to mitigate damage, or just take the hit full on.

#### Defense (Derived)
When a Pokémon is attacked in battle, the **Trainer** can choose a **Defense** move to mitigate incoming damage (*if a defense move is available*). If a Defense move is used, it will take in an **Attack**, and subtract from it's base power using the defense move's base power. Following this, the resulting Pokémon's health stat will be calculated. Stat boosts are also possible in this class.

## Type
>Members
>- Primary Type
>- Secondary Type

All Pokémon will have at least a primary type, and will contain an object of **Type**. This is an enumerator class that manages the typing of that containing Pokémon. During battle, depending on the types between Pokémon, an **Attack** or **Defense** base power can be increased or decreased. For now, there will be the following possible types.

>Type Enumerator
>- Fire
>- Water
>- Grass

#### 
Type effectiveness 
---
|Offense  | Defense | Power Boost |
|--|--|--|
| Fire | Grass | 150 |
| Water | Fire | 150 |
| Grass | Water | 150 |
---

# Data Structures
All data structures will be implemented as templates, to support any possible data types. The data type **T** that is used, must have all of the necessary operator overloads for the data structure to properly manage that data type. All data structures will contain display, insert, retrieve, remove, and removal all procedures.
 
## 2-3 Tree // *Template*
>Member
> 2-3 Node pointer *// root*

A balanced 2-3 tree will manage 2-3 nodes of any data type **T**. The primary use of this structure will be to keep track of all of the Pokémon a **User** has caught. The **User** will contain a 2-3 Tree object. The Pokémon will be sorted by the Pokémon's member *Nickname* which is set by the **User**. Nicknames must be unique to insert to into the 2-3 tree.

## 2-3 Node *// Template derived from T*
>Member
>2-3 Node pointer array *// size = 3*

This node will be used by the 2-3 tree to traverse the tree, with basic set and get functions for each index of the pointer array within this class.

## Array of Doubly Linked Lists // *Template*
>Members
>- List Node pointer array
>- array size

The primary purpose of this array of linked lists is to keep a dynamic database of all possible moves a Pokémon can learn, which will then be used in Pokémon battles between **User** and **NPC**.

## List Node *// Template derived from T*
>Members
> List Node pointer *// next pointer*
> List Node pointer *// previous pointer*

This node will be used by the array of doubly linked lists to traverse all of the doubly linked lists in the array. Basic set and get functions will be implemented to deal with the next pointer in this class.

# Datatype Libraries
## String (Base)
All char* data will be handled by this library. Basic input, output, and comparison operations will be available.
#### Int (Derived)
String to integer conversion will be handled here to mitigate user input errors when an integer is expected.

## RNG (Random Number Generator)
Generates random integers and returns them upon request. This will be used for anything within the game that requires chance as a factor.

<!--stackedit_data:
eyJoaXN0b3J5IjpbMTcyNjQ5NzgxMyw5OTgyMDU4NiwxODc2MD
E0MzU4LC00NTY3ODA5ODYsLTQ5MzAzNTE3MiwyMTA5MTc5NTUw
LC0yMjA3Njc4MTksLTE2MDgwMzczOTgsLTI5MDI0NzUzNiw5MD
g0MTg0MjEsMTEwODA2MzAzOSwtODA1NzMxNjQ4LC0xMTg1Njc5
MjIwLC0xNDI5MTEzNjQ3LDE1NDE5MjgwNDMsNzk3OTE1MjZdfQ
==
-->
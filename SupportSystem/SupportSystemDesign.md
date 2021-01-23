Sean Siders
CS202
Program 1 Design : Support System

---
# Background
This Program will provide a database for giving and receiving donations that serve as relief efforts to citizens in need, due to an unexpected crisis. Donors will be able to access the program to report essential information about their relief effort. Those in need can utilize the program's search feature, to browse the catalogue of donated relief efforts, giving them a full view of what is available. The variety of relief efforts will currently be limited to 3 types, **housing**, **clothing**, and **food**, which will all fall into the hierarchy of the **support class** as their own derived classes.

# Class Hierarchy

`void display()`
Display all information about the relief effort. This display function will exist in the base class as well as all subclasses, for each class will be individually responsible for displaying its own data.

## Support : Base Class
The **support class** will be the base class of any relief efforts that are made available in this program. Within this class, all basic information can be found about the relief effort, such as **title**, an optional **donor name** , **date of donation**, and a **quantity** in the event that duplicates of the same item are provided by the donor. Additionally, for the data structure that will serve as the search history of this database, the **search frequency** will internally count the number of times a particular relief effort has been searched for by **title**.

`bool isMatch(const char* _title)`
Compare `_title` with `this->title` using `strcmp` from the cstring library. True if the titles match. This will be used when a  user searches for a particular donation.

`int compareFrequency(const int _frequency)`
Calculate the difference between `_frequency` and `this->frequency`, returning the result. A negative value will indicate the incoming frequency is higher in value, and vice versa. This function will aid in the search history feature, that is ordered by search frequency. This will be implemented with a data structure specified in **Data Structures**.

## Housing : Sub Class
This class will contain the number of people that can be housed, address or location, and the number of current residents (if applicable). There will also be the option of offering **food**, and **clothing**, in conjunction with **housing**, which in that case, **food**, and **clothing** class objects, will be utilized within the **housing** class.

`bool addResidents(const int count)`
When someone accepts the housing through the system, they can submit how many people will be living there. **Housing** will store a **capacity** variable, which will serve as a limit to the number of people that can comfortably live there. This function will return false, if **count** + **current residents** exceeds **capacity**.

## Food : Sub Class
In early development, this class will only handle cold food, that has proper **allergen information** and an **expiration date**. The possibility of hot food donations may be considered in the future, which will consist of **date**, **time**, and **location** of the hot food to be served.

## Clothing : Sub Class
Information about the clothing donated will contain the **size**, **condition**, and the **suggested gender**, these members will most effectively be enumerations, but must be converted from string input by the user. An additional class to handle these conversions to the enum may be necessary.

## Date
All mentioned data members that deal with a **date** will be abstracted into a class. Classes in the hierarchy that have a date will hold an object of this class.

# Data Structures
The following data structures will have implementation of insert, removal, display, retrieval, and remove-all functionality.

>Queue
>
A circular linked list will be implemented to serve as a queue for each type of relief efforts. The first three relief efforts that will be supported are **housing**, **clothing**, and **food**, which will each have their own respective queue. The queue's insertion algorithm will put the newest donations at the back, supporting a "first in first out" design.

>Linear Linked List (search history)
>
A linear linked list will keep track of all search history in the database. The list will be sorted from most frequently searched to least frequently searched. When a new item is searched for, the list will mutate to keep the data structure sorted by frequency.

## Node
This will be a subclass of **Support**, which will be able to traverse both the queue, and search history list. This will be the glue that holds all of the classes in the hierarchy together into the provided data structures.

# Testing
Procedural testing will be performed throughout the development of this program with a single .txt file. All tests will be automated through a **Testing Interface** class, which will read in the external file, and interact with the program to simulate multiple instance of submitting and receiving donations.

# Additional Features
The following features may be implemented if time permits the opportunity.

>Donation History List
>An additional linear linked list could be used as a "donation history" list, which would act as an archive for all relief efforts that have been accepted by a user in crisis.

>Cross-Donor Duplicate Consolidation
>In the event that duplicate items are donated between more than 1 donor, the system will keep the inventory contained in one instance of the support class. Additional structure or class abstraction will be required to keep track of the different donor names, and dates of donation.
<!--stackedit_data:
eyJoaXN0b3J5IjpbLTc5Mzg5MjM2OV19
-->
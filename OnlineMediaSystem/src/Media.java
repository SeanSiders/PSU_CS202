//Sean Siders
//CS202
//Online Media System
//11/30/2020

//////////////// ABSTRACT SUPER CLASS

/*
This abstraction is the super class of the |Media| hierarchy. All items in the online media system are
sub-classes of |Media|. |Media| manages all of the essential information about a piece of media, and provides an
interface for all sub-classes to implement. The only function that is not implemented throughout the hierarchy is
|nameCompare|, which is used by the |Channel| data structure in key-related procedures.
 */

import java.util.Scanner;

public abstract class Media extends Utils {

    //////////////// FIELDS

    //a title for the media
    protected String title;

    //the creator of the media
    protected String author;

    //the date and time at which this item was created
    protected String creationTimestamp;

    //a self-documenting descriptive title for the type of media this is
    protected String mediaType;

    //the due date for the student to consume the content by
    protected Date dueDate;

    //////////////// CONSTRUCTORS

    public Media() {

        //record the time of creation
        creationTimestamp = getTimestamp();

        System.out.print("\nAUTHOR NAME >>> ");
        author = getString();

        System.out.print("TITLE >>> ");
        title = getString();

        System.out.print("DUE DATE ");
        dueDate = new Date();
    }

    public Media(Media source) {

        this.creationTimestamp = source.creationTimestamp;
        this.author = source.author;
        this.title = source.title;
        this.dueDate = new Date(source.dueDate);
    }

    public Media(String author) {

        //record the time of creation
        creationTimestamp = getTimestamp();

        this.author = author;

        System.out.print("TITLE >>> ");
        title = getString();

        System.out.print("DUE DATE ");
        dueDate = new Date();
    }

    public Media(Scanner fields) {

        title = fields.next();
        author = fields.next();
        creationTimestamp = fields.next();
        dueDate = new Date(fields.next());
    }

    //////////////// ABSTRACT FUNCTIONS

    abstract public void interact();
    abstract public void edit();

    //////////////// PUBLIC FUNCTIONS

    //// HIERARCHY OVERLOAD
    //allow the media data to be edited only if |instructorName| matches |author|
    public void edit(String instructorName) {

        if (author.equals(instructorName)) {

            System.out.print("TITLE >>> ");
            title = getString();

            System.out.print("DUE DATE ");
            dueDate = new Date();
        }
        else System.out.print("EDITING PRIVILEGES DENIED\n\n");
    }

    //display information about the media
    public void display() {

        System.out.print("\nMEDIA TITLE | " + title +
                         "\nAUTHOR NAME | " + author +
                         "\nTIME OF CREATION | " + creationTimestamp +
                         "\nMEDIA TYPE | " + mediaType +
                         "\nDUE DATE | ");

        dueDate.display();

        System.out.println();
    }

    //compare |this.title| with |title|, true if they are a case-sensitive match
    public boolean nameCompare(String title) {

        return this.title.equals(title);
    }
}

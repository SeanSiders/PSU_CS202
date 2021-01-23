//Sean Siders
//CS202
//Online Media System
//11/30/2020

/*
This abstraction manages a linear linked list of |AuthoredText|. This is primarily used to store
text created by the students within a |Forum| discussion.

TODO support video comments
 */

public class TextList extends Utils {

    //////////////// FIELDS

    //first node in the list
    private TextNode head;

    //last node in the list
    private TextNode tail;

    //////////////// CONSTRUCTORS

    public TextList() {

        head = null;
        tail = null;
    }

    //////////////// PUBLIC FUNCTIONS

    //// WRAPPER
    //display the list
    public void display() {

        display(head);
    }

    //true if the list is empty
    public boolean empty() {

        return head == null;
    }

    //insert |text| at the front of the list
    public void pushFront(AuthoredText text) {

        //empty list
        if (head == null) {

            head = new TextNode(text);
            tail = head;
            return;
        }

        //insert at head
        TextNode hold = head;
        head = new TextNode(text);
        head.setNext(hold);
    }

    //// WRAPPER
    //walk the user through each |AuthoredText| in the list
    //give the user the option to remove any post upon visit
    public void edit() {

        System.out.print("""
                         
                         ======== DISCUSSION REMOVAL ========
                         r) remove text
                         n) next post
                         q) quit
                         
                         """);

        head = edit(head);
    }

    //////////////// PRIVATE FUNCTIONS

    //// RECURSIVE
    private void display(TextNode head) {

        if (head == null) return;
        head.display();
        display(head.next());
    }

    //// RECURSIVE
    //traverse with |head| removing nodes upon the user's request
    private TextNode edit(TextNode head) {

        if (head == null) return null;

        head.display();

        switch(getChar()) {

            case 'r' : return edit(head.next());
            case 'n' : break;
            default : return head;
        }

        head.setNext(edit(head.next()));
        return head;
    }
}

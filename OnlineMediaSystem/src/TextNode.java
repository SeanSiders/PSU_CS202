//Sean Siders
//CS202
//Online Media System
//11/30/2020

/*
Node abstraction for |TextList|.
 */

public class TextNode extends AuthoredText {

    //////////////// FIELDS

    //next node in the list
    private TextNode next;

    //////////////// CONSTRUCTORS

    public TextNode() {

        next = null;
    }

    public TextNode(AuthoredText text) {

        super(text);
        next = null;
    }

    //////////////// PUBLIC FUNCTIONS

    //get the next node in the list
    public TextNode next() {

        return next;
    }

    //set the next node in the list
    public void setNext(TextNode next) {

        this.next = next;
    }
}

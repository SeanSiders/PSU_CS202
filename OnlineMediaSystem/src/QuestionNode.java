//Sean Siders
//CS202
//Online Media System
//11/30/2020

/*
Node abstraction for |Quiz|. This data structure is in the form of a linear linked list,
and any number of |Questions| can be created.
 */

public class QuestionNode extends Question {

    //////////////// FIELDS

    //next node in the list
    private QuestionNode next;

    //////////////// CONSTRUCTORS

    public QuestionNode() {

        next = null;
    }

    public QuestionNode(Question question) {

        super(question);
        next = null;
    }

    //////////////// PUBLIC FUNCTIONS

    //get the next node in the list
    public QuestionNode next() {

        return next;
    }

    //set the next node in the list
    public void setNext(QuestionNode next) {

        this.next = next;
    }
}
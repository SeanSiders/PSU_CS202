//Sean Siders
//CS202
//Online Media System
//11/30/2020

/*
An instructor can create a forum where students can post to the discussion board. A topic is presented
to the students to discuss about. A forum is a sub-class in the |Media| hierarchy.
 */

import java.util.Scanner;

public class Forum extends Media {

    //////////////// FIELDS

    //the forum's discussion topic or question
    String topic;

    //the thread of posts from students about the topic
    TextList discussion;

    //////////////// CONSTRUCTOR

    public Forum() {

        mediaType = "FORUM";

        System.out.print("DISCUSSION TOPIC >>> ");
        topic = getString();
        discussion = new TextList();
    }

    public Forum(String author) {

        super(author);

        mediaType = "FORUM";

        System.out.print("DISCUSSION TOPIC >>> ");
        topic = getString();
        discussion = new TextList();
    }

    public Forum(Scanner fields) {

        super(fields);

        mediaType = "FORUM";

        topic = fields.next();
        discussion = new TextList();
    }

    //////////////// PUBLIC FUNCTIONS

    //display the topic and the student discussion
    public void display() {

        super.display();
        System.out.print("TOPIC | " + topic + "\n\n======== DISCUSSION ========\n\n");
        if (discussion.empty()) System.out.print("*** No one has participated in this forum\n\n");
        else discussion.display();
    }

    //post to the forum
    public void interact() {

        display();
        discussion.pushFront(new AuthoredText());
    }

    //give the user the option to either edit the topic or the discussion
    public void edit() {

        System.out.print("""
                        ======== FORUM EDIT ========
                        0) quit
                        1) display forum
                        2) edit the topic
                        3) edit the discussion
                        """ + ">>> ");

        switch (getInt(0, 3)) {

            case 1 : display(); break;
            case 2 : editTopic(); break;
            case 3 : editDiscussion(); break;
            default : return;
        }

        edit();
    }

    //////////////// PRIVATE FUNCTIONS

    //get a new topic from the user
    private void editTopic() {

        System.out.print("DISCUSSION TOPIC >>> ");
        topic = getString();
    }

    //prompt the user with a menu of options related to editing the discussion
    private void editDiscussion() {

        System.out.print("""
                        ======== DISCUSSION EDIT ========
                        0) quit
                        1) display discussion
                        2) remove a post 
                        """ + ">>> ");

        switch (getInt(0, 2)) {

            case 1 : discussion.display(); break;
            case 2 : discussion.edit(); break;
            default : return;
        }

        editDiscussion();
    }
}

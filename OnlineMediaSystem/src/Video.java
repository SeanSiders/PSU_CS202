//Sean Siders
//CS202
//Online Media System
//11/30/2020

/*
All video data will be managed by this class. A video has a play length and an option of closed captioning.
A video is a sub-class in the |Media| hierarchy.
 */

import java.util.Scanner;

public class Video extends Media {

    //////////////// FIELDS

    //the play length of the video
    float videoLength;

    //if the video has captioning, this will be set to true
    boolean hasCaptioning;

    //any closed captioning for the video
    String closedCaptioning;

    //////////////// CONSTRUCTORS

    public Video() {

        //set the media type
        mediaType = "VIDEO";

        System.out.print("VIDEO LENGTH (float value) >>> ");
        videoLength = getFloat();

        System.out.print("DOES YOUR VIDEO CONTAIN CLOSED CAPTIONING?\n(y/n) >>> ");
        if (getYesNo()) {

            hasCaptioning = true;
            System.out.print("CLOSED CAPTIONING >>> ");
            closedCaptioning = getString();
        }
        else hasCaptioning = false;
    }

    public Video(String author) {

        super(author);

        //set the media type
        mediaType = "VIDEO";

        System.out.print("VIDEO LENGTH (float value) >>> ");
        videoLength = getFloat();

        System.out.print("DOES YOUR VIDEO CONTAIN CLOSED CAPTIONING?\n(y/n) >>> ");
        if (getYesNo()) {

            hasCaptioning = true;
            System.out.print("CLOSED CAPTIONING >>> ");
            closedCaptioning = getString();
        }
        else hasCaptioning = false;
    }

    public Video(Scanner fields) {

        super(fields);

        //set the media type
        mediaType = "VIDEO";

        videoLength = fields.nextFloat();
        hasCaptioning = true;
        closedCaptioning = fields.next();
    }

    //////////////// PUBLIC FUNCTIONS

    //display all information about the video
    public void display() {

        super.display();

        System.out.print("\nVIDEO LENGTH | " + videoLength + " hrs");
        if (hasCaptioning) System.out.print("\n\nCLOSED CAPTIONING\n" + "=================\n" + closedCaptioning + "\n\n");
    }

    //play the video
    public void interact() {

        System.out.print("NOW PLAYING : " + title + "...\n" + closedCaptioning + "\n\n");
    }

    //prompt the user with a menu of edit options related to the video data
    public void edit() {

        System.out.print("""
                        ======== VIDEO EDIT ========
                        0) quit
                        1) display
                        2) edit video length
                        3) edit closed captioning
                        """ + ">>> ");

        switch (getInt(0, 3)) {

            case 1 : display(); break;
            case 2 : editLength(); break;
            case 3 : editClosedCaptioning(); break;
            default : return;
        }

        edit();
    }

    //////////////// PUBLIC FUNCTIONS

    //get user input for a new video length
    protected void editLength() {

        System.out.print("VIDEO LENGTH (float value) >>> ");
        videoLength = getFloat();
    }

    //get user input for new closed captioning
    protected void editClosedCaptioning() {

        System.out.print("DOES YOUR VIDEO CONTAIN CLOSED CAPTIONING?\n(y/n) >>> ");
        if (getYesNo()) {

            hasCaptioning = true;
            System.out.print("CLOSED CAPTIONING >>> ");
            closedCaptioning = getString();
        }
        else {
            hasCaptioning = false;
            closedCaptioning = null;
        }
    }
}
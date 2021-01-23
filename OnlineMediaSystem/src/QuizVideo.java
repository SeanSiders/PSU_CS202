//Sean Siders
//CS202
//Online Media System
//11/30/2020

/*
|QuizVideo| is both a |Video| with the option of closed captioning and an array of quizzes. As the video plays
quizzes will be prompted to the user, where answer input will be read in. These quizzes are defaulted to publish
grades immediately upon completion, continuing video play afterwards. |QuizVideo| is a sub-class of the
|Media| hierarchy.
 */

import java.util.Scanner;

public class QuizVideo extends Video {

    //////////////// FIELDS

    //the array of quizzes that will occur throughout the video
    private Quiz [] quizzes;

    //array of times within the video's play length, where quiz questions will occur
    private float [] quizTimes;

    //the number of quizzes in the video
    private int quizCount;

    //////////////// CONSTRUCTORS

    public QuizVideo() {

        //set the media type
        mediaType = "QUIZ VIDEO";

        System.out.print("ENTER THE NUMBER OF QUIZZES THIS VIDEO WILL HAVE\nvalid range : (1, 10) >>> ");
        quizCount = getInt(1, 10);

        quizzes = new Quiz[quizCount];
        quizTimes = new float[quizCount];

        setupQuizzes();
    }

    public QuizVideo(String author) {

        super(author);

        //set the media type
        mediaType = "QUIZ VIDEO";

        System.out.print("ENTER THE NUMBER OF QUIZZES THIS VIDEO WILL HAVE\nvalid range : (1, 10) >>> ");
        quizCount = getInt(1, 10);

        quizzes = new Quiz[quizCount];
        quizTimes = new float[quizCount];

        setupQuizzes();
    }

    public QuizVideo(Scanner fields) {

        super(fields);

        //set the media type
        mediaType = "QUIZ VIDEO";

        quizCount = fields.nextInt();
        quizzes = new Quiz[quizCount];
        quizTimes = new float[quizCount];

        for (int i = 0; i < quizCount; ++i) {

            quizTimes[i] = fields.nextFloat();
            quizzes[i] = new Quiz(fields, this);
        }
    }

    //////////////// PUBLIC FUNCTIONS

    //display all information about the quiz video
    public void display() {

        super.display();
        System.out.print("\nQUIZ COUNT : " + quizCount);

        for (int i = 0; i < quizCount; ++i) {

            System.out.print("\nQUIZ " + (i + 1) + " PROMPT TIME | " + quizTimes[i] + "\n");
            quizzes[i].display();
        }
    }

    //play the video and take the quizzes at the specified video play times
    public void interact() {

        for (int i = 0; i < quizCount; ++i) {

            System.out.print("QUIZ " + (i + 1) + " PROMPT TIME | " + quizTimes[i] + "\n\n");

            //quiz results will be immediately displayed
            quizzes[i].interact();
        }

        System.out.print("VIDEO END\n\n");
    }

    //prompt the user with a menu of edit options
    public void edit() {

        System.out.print("""
                        ======== VIDEO EDIT ========
                        0) quit
                        1) display
                        2) edit video length
                        3) edit closed captioning
                        4) edit quiz prompt times
                        5) edit a quiz
                        """ + ">>> ");

        switch (getInt(0, 5)) {

            case 1 : display(); break;
            case 2 : editLength(); break;
            case 3 : editClosedCaptioning(); break;
            case 4 : editQuizTimes(); break;
            case 5 : editQuizzes(); break;
            default : return;
        }

        edit();
    }

    //////////////// PRIVATE FUNCTIONS

    //get user input for the quiz prompt times and the quiz questions
    private void setupQuizzes() {

        //to prevent quiz times from being entered in a non-linear fashion
        float lastQuizTime = 0.f;
        for (int i = 0; i < quizCount; ++i) {

            //get a float between the last entered quiz time and the length of the video
            System.out.print("QUIZ PROMPT TIME\nvalid float range (0, " + videoLength + ") >>> ");
            quizTimes[i] = getFloat(lastQuizTime, videoLength);
            lastQuizTime = quizTimes[i];

            //create the quiz, defaulting auto-publish to on
            quizzes[i] = new Quiz(true);
        }
    }

    //go through the array of quiz times letting the user change any of the times
    private void editQuizTimes() {

        for (int i = 0; i < quizCount; ++i) {

            System.out.print("\n======== QUIZ " + (i + 1) + " ========\nPROMPT TIME | " + quizTimes[i] + "\n");
            quizzes[i].display();

            System.out.print("WOULD YOU LIKE TO CHANGE THE PROMPT TIME?\n(y/n)");
            if (getYesNo()){

                System.out.print("ENTER A NEW PROMPT TIME\nfloat value >>> ");
                quizTimes[i] = getFloat(0, videoLength);
            }
        }
    }

    //go through the array of quizzes letting the user change any of the quizzes
    private void editQuizzes() {

        for (int i = 0; i < quizCount; ++i) {

            System.out.print("\n======== QUIZ " + (i + 1) + " ========\nPROMPT TIME | " + quizTimes[i] + "\n");
            quizzes[i].display();

            System.out.print("WOULD YOU LIKE TO EDIT THIS QUIZ?\n(y/n)");
            if (getYesNo()) quizzes[i].edit();
        }
    }
}

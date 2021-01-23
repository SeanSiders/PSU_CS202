//Sean Siders
//CS202
//Online Media System
//11/30/2020

/*
A course can be opened by either a teacher in |teacherMode| or student in |studentMode|. From here
a variety of options related to the course content will be presented to the user.
 */

import java.util.Scanner;
import java.io.FileNotFoundException;

public class Course extends Channel {

    //////////////// FIELDS

    //the course title
    String courseTitle;

    //the course instructor's name
    String instructorName;

    //the date that this course will begin
    Date beginDate;

    //the date that this course will end
    Date endDate;

    //////////////// CONSTRUCTORS

    public Course() {

        System.out.print("\nCOURSE NAME >>> ");
        courseTitle = getString();

        System.out.print("\nINSTRUCTOR NAME >>> ");
        instructorName = getString();

        System.out.print("\nBEGIN DATE >>> ");
        beginDate = new Date();

        System.out.print("\nEND DATE >>> ");
        endDate = new Date();

        open();
    }

    //parameterized with the filepath for an external file that contains data for the system
    public Course(String filepath) throws FileNotFoundException {

        super(filepath);

        Scanner courseFields = getFieldScanner("---");

        courseTitle = courseFields.next();
        beginDate = new Date(courseFields.next());
        endDate = new Date(courseFields.next());
        instructorName = courseFields.next();

        readInMedia();
    }

    //////////////// PUBLIC FUNCTIONS

    //open the course, giving the user the option of instructor mode or student mode
    public void open() {

        System.out.print("\n======== ");
        displayName();
        System.out.print(" ========\n\n");

        System.out.print("""
                    
                             0) quit
                             1) instructor mode
                             2) student mode
                             """ + ">>> ");

        switch (getInt(0, 2)) {
            case 1 : instructorMode(); break;
            case 2 : studentMode(); break;
            default : return;
        }

        open();
    }
    //display the course name
    public void displayName() {

        System.out.print(courseTitle);
    }

    //return an integer value that reflects the comparison of |courseTitle| and the |courseTitle| of |other|
    // < 0 : |otherTitle| is alphabetically less
    // > 0 : |otherTitle| is alphabetically larger
    // 0 : they are equivalent
    public int compareTitles(Course other) {

        return other.courseTitle.compareTo(courseTitle);
    }

    //overload to compare directly to a string
    public int compareTitles(String otherTitle) {

        return otherTitle.compareTo(courseTitle);
    }

    //open the course in admin mode, giving the user all options of editing course content
    //the admin will also have the option of simulating a student in the course
    public void instructorMode() {

        System.out.print("\n======== " + courseTitle + " ========\n*** INSTRUCTOR MODE AS | " + instructorName + "\n\n");

        System.out.print("""
                         0) quit
                         1) display all media
                         2) create a new media item
                         3) remove a media item
                         4) open a media item
                         
                         select an option with integer input
                         """ + ">>> ");

        switch(getInt(0, 4)) {

            case 1 : display(); break;
            case 2 : createMedia(); break;
            case 3 : removeMedia(); break;
            case 4 : openMedia(); break;
            default : return;
        }

        instructorMode();
    }

    //open this course in student mode
    //prompt a menu of options for the student to interact with the course
    public void studentMode() {

        System.out.print("\n======== " + courseTitle + " ========\n*** STUDENT MODE\n\n");

        System.out.print("""
                         0) quit
                         1) display all media
                         2) open a topic
                          
                         select an option with integer input
                         """ + ">>> ");

        switch (getInt(0, 2)) {

            case 1 : display(); break;
            case 2 : openTopic(); break;
            default : return;
        }

        studentMode();
    }

    //////////////// PRIVATE FUNCTIONS

    //read in the media items from the loaded external datafile
    private void readInMedia() {

        //read in the type of media
        String mediaType = read("---");
        int playlistIndex = 0;

        while (mediaType != null) {

            playlistIndex = readInt("---");

            switch (mediaType) {
                case "FORUM" -> insertAt(playlistIndex, new Forum(getFieldScanner("---")));
                case "VIDEO" -> insertAt(playlistIndex, new Video(getFieldScanner("---")));
                case "QUIZ" -> insertAt(playlistIndex, new Quiz(getFieldScanner("---")));
                case "QUIZ_VIDEO" -> insertAt(playlistIndex, new QuizVideo(getFieldScanner("---")));
                default -> throw new IllegalArgumentException("INVALID ENTRY IN EXTERNAL DATAFILE : ");
            }

            mediaType = read("---");
        }
    }

    //prompt the user with a menu of media options to create
    //create the item, then insert it into the channel
    private void createMedia() {

        System.out.print("""
                         ======== MEDIA CREATION MENU ========
                         
                         0) quit
                         1) forum 
                         2) video
                         3) quiz
                         4) quiz-video
                         
                         select a media item to create with integer input
                         """ + ">>> ");

        switch (getInt(0, 4)) {

            case 1 : insertMedia(new Forum(instructorName)); break;
            case 2 : insertMedia(new Video(instructorName)); break;
            case 3 : insertMedia(new Quiz(instructorName)); break;
            case 4 : insertMedia(new QuizVideo(instructorName)); break;
            default : return;
        }

        createMedia();
    }

    //determine where the new media item should be inserted into the channel
    //the user will also have to option to draft it by inserting into |drafts|
    private void insertMedia(Media toInsert) {

        topicDisplay();
        System.out.print("WHICH TOPIC WOULD YOU LIKE TO INSERT THE NEW MEDIA?\nTOPIC NAME (not case sensitive) >>> ");

        while (!insert(getString(), toInsert)) {

            System.out.print("NO PLAYLIST MATCHED THAT NAME\n");
            topicDisplay();
            System.out.print("WHICH TOPIC WOULD YOU LIKE TO INSERT THE NEW MEDIA?\nTOPIC NAME (not case sensitive) >>> ");
        }

        System.out.print("MEDIA SUCCESSFULLY INSERTED\n\n");
    }

    //get the name of the media items to remove, then remove them from the channel
    private void removeMedia() {

        System.out.print("ENTER THE NAME OF THE MEDIA ITEM YOU WANT REMOVED\nMEDIA TITLE (case sensitive) >>> ");
        if (remove(getString())) System.out.print("MEDIA SUCCESSFULLY REMOVED\n");
        else System.out.print("NO MEDIA WAS FOUND MATCHING THAT NAME\n");
    }

    //attempt to retrieve a media item by name
    //if successfully retrieved, prompt the user with a menu of options to perform on the media
    private void openMedia() {

        System.out.print("ENTER THE NAME OF THE MEDIA ITEM YOU WANT RETRIEVED\nMEDIA TITLE (case sensitive) >>> ");
        Media retrieved = retrieve(getString());

        if (retrieved != null) openMedia(retrieved);
        else System.out.print("NO MEDIA WAS FOUND MATCHING THAT NAME\n");
    }

    //prompt the user with a menu of options related to their retrieved media
    private void openMedia(Media retrieved) {

        System.out.print("MEDIA SUCCESSFULLY RETRIEVED\n\n");

        System.out.print("""
                            ======== RETRIEVED MEDIA MENU ========
                            
                            0) quit
                            1) display
                            2) interact in student mode
                            3) edit media item
                            4) edit admin data (HIERARCHY OVERLOAD)
                            """ + ">>> ");

        switch (getInt(0, 4)) {

            case 1 : retrieved.display(); break;
            case 2 : retrieved.interact(); break;
            case 3 : retrieved.edit(); break;
            case 4 : retrieved.edit(instructorName); break;

            default : return;
        }

        openMedia(retrieved);
    }

    //open a topic in student mode
    //interact with every media item in the topic |Playlist|
    private void openTopic() {

        //display all topic names
        topicDisplay();

        //get a topic name from the user
        System.out.print("\nENTER THE TOPIC NAME YOU WISH TO OPEN\nTOPIC NAME (non-case sensitive) >>> ");

        //prompt the user if no matching topic was found
        if (!interactTopic(getString())) System.out.print("\nNO TOPIC MATCHED THE PROVIDED INPUT\n\n");
    }
}

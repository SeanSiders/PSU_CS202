//Sean Siders
//CS202
//Online Media System
//11/30/2020

public class AuthoredText extends Utils {

    //////////////// FIELDS

    //the author of the text
    protected String author;

    //the date and time at which this text was created
    private final String creationTimestamp;

    //the text content created by the author
    protected String text;

    //////////////// CONSTRUCTORS

    public AuthoredText() {

        creationTimestamp = getTimestamp();

        System.out.print("ENTER THE FOLLOWING INFORMATION\nAUTHOR >>> ");
        author = getString();

        System.out.print("\nTEXT INPUT\n==========\n");
        text = getString();
    }

    public AuthoredText(String author) {

        creationTimestamp = getTimestamp();
        this.author = author;

        System.out.print("\nTEXT INPUT\n==========\n");
        text = getString();
    }

    public AuthoredText(String author, String creationTimestamp, String text) {

        this.author = author;
        this.creationTimestamp = creationTimestamp;
        this.text = text;
    }

    //copy constructor
    public AuthoredText(AuthoredText source) {

        this.author = source.author;
        this.creationTimestamp = source.creationTimestamp;
        this.text = source.text;
    }
    //////////////// PUBLIC FUNCTIONS

    //display all information about the text, including the text
    public void display() {

        System.out.print("AUTHOR | " + author
                         + "\nTIME OF CREATION | " + creationTimestamp
                         + "\nTEXT\n====\n" + text + "\n\n");
    }
}
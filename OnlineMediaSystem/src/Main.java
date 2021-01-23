//Sean Siders
//CS202
//Online Media System
//11/30/2020

///////////// MAIN ENTRY POINT

/*
The program should be run from the |Main| class, where an external data filepath is specified, and all
necessary objects are created for the program to run as expected.
 */

import java.io.FileNotFoundException;

public class Main {

    public static void main(String [] args) throws FileNotFoundException {

        //one |University| currently exists in this program
        University university = new University(("src/Database/CourseDatabase.txt"));

        //open the university, where user menu options are prompted
        university.open();
    }
}

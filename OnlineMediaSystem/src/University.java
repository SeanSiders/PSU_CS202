//Sean Siders
//CS202
//Online Media System
//11/30/2020

/*
The university manages all courses in the system. It is an abstraction that extends a binary
search tree of courses. Administrators can use edit any course from here, and students can access
their courses that they are authorized to interact with.
 */

import java.io.FileNotFoundException;
import java.util.Scanner;

public class University extends CourseTree {

    //////////////// FIELDS

    //the university's name
    private String universityName;

    //////////////// CONSTRUCTORS

    public University() {

        System.out.print("\nENTER THE UNIVERSITY NAME\n>>> ");
        universityName = getString();
    }

    public University(String filepath) throws FileNotFoundException {

        //load external data file with the filepath
        loadFile(filepath);

        universityName = read("\n");

        readInCourses();
    }

    //////////////// PUBLIC FUNCTIONS

    //prompt the user with a menu of options for the |Courses| at this |University|
    public void open() {

        //////// HARDCODED REMOVAL TEST CASES

        //Root removal
        //remove("Integral Calculus : MTH252");

        //IOS is in the right subtree
        //remove("Chemistry lab : CHEM201");

        //Leaf Removal
        //remove("Music Conducting Practices : MUS413");

        //IOS is the left child
        //remove("Physics with Calculus : PHY211");

        //IOS is the right child
        //remove("French Studies : FR411");

        System.out.print("UNIVERSITY | " + universityName + "\n" +
                         """
                         
                         0) quit
                         1) display all courses by title
                         2) add a new course
                         3) open a course
                         4) remove a course
                         5) remove all courses
                         """ + ">>> ");

        switch (getInt(0, 5)) {

            case 1 : if (!display()) { System.out.print("NO COURSES HAVE BEEN CREATED\n\n"); }; break;
            case 2 : insert(new Course()); break;
            case 3 : openCourse(); break;
            case 4 : removeCourse(); break;
            case 5 : removeAllCheck(); break;
            default : return;
        }

        open();
    }

    //////////////// PRIVATE FUNCTIONS

    //insert the new courses with their external data file paths into the course tree
    private void readInCourses() throws FileNotFoundException {

        //the filepath to the course's data
        String courseFilepath = read("\n");

        while (courseFilepath != null) {

            insert(new Course(courseFilepath));
            courseFilepath = read("\n");
        }
    }

    //open a course with user input, by retrieving the course from the tree
    private void openCourse() {

        display();
        System.out.print("\nENTER THE NAME OF THE COURSE YOU WANT TO OPEN\nCOURSE NAME (case sensitive) >>> ");
        Course retrieved = retrieve(getString());

        if (retrieved != null) retrieved.open();
        else System.out.print("NO COURSES MATCHED THAT NAME\n\n");
    }

    //attempt to remove a course with user input by name
    private void removeCourse() {

        display();
        System.out.print("\nENTER THE NAME OF THE COURSE YOU WANT TO REMOVE\nCOURSE NAME (case sensitive) >>> ");

        if (remove(getString())) System.out.print("COURSE SUCCESSFULLY REMOVED\n\n");
        else System.out.print("NO COURSES MATCHED THAT NAME\n\n");
    }

    //double check that the user wants to remove all courses
    private void removeAllCheck() {

        display();
        System.out.print("\nALL COURSES WILL BE REMOVED FROM THE SYSTEM\nare you sure? (y/n) >>> ");

        if (getYesNo()) {

            removeAll();
            System.out.print("ALL COURSES WERE REMOVED\n\n");
        }
        else System.out.print("COURSES WERE NOT REMOVED\n\n");
    }
}

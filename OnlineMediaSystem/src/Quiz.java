//Sean Siders
//CS202
//Online Media System
//11/30/2020

/*
A teacher can create a quiz for the students. There can be any number of questions. Upon a student opening
the quiz with |interact| answers will be read in from the student. The teacher can specify whether the grade
for a quiz is published immediately upon completion or not. |Quiz| is a sub-class in the |Media| hierarchy.
 */

import java.util.Scanner;

public class Quiz extends Media {

    public static void main(String [] args) {

        Quiz q = new Quiz();

        q.interact();
    }

    //////////////// FIELDS

    //the last node in the list
    QuestionNode head;

    //the first node in the list
    QuestionNode tail;

    //the number of questions in the quiz
    int questionCount;

    //whether or not the student should be able to see their grade immediately following the quiz
    boolean autoPublishGrades;

    //whether or not the quiz has been taken by a student
    boolean taken;

    //the number of correctly answered questions
    int correctCount;

    //the student's grade from the quiz
    float grade;

    //////////////// CONSTRUCTORS

    public Quiz() {

        head = null;
        tail = null;
        questionCount = 0;
        correctCount = 0;
        grade = 0.f;
        taken = false;

        //set the media type
        mediaType = "QUIZ";

        setAutoPublish();

        //create the quiz with user input
        create();
    }

    public Quiz(String author) {

        super(author);

        head = null;
        tail = null;
        questionCount = 0;
        correctCount = 0;
        grade = 0.f;
        taken = false;

        //set the media type
        mediaType = "QUIZ";

        setAutoPublish();

        //create the quiz with user input
        create();
    }

    public Quiz(boolean autoPublishGrades) {

        this.autoPublishGrades = autoPublishGrades;
        taken = false;
        create();
    }

    public Quiz(Scanner fields) {

        super(fields);

        //set the media type
        mediaType = "QUIZ";

        correctCount = 0;
        grade = 0.f;
        taken = false;

        questionCount = fields.nextInt();
        autoPublishGrades = fields.nextBoolean();

        for (int i = 0; i < questionCount; ++i) pushBack(new Question(fields));
    }

    public Quiz(Scanner fields, Media source) {

        super(source);

        //set the media type
        mediaType = "QUIZ";

        correctCount = 0;
        grade = 0.f;
        taken = false;

        questionCount = fields.nextInt();
        autoPublishGrades = fields.nextBoolean();

        for (int i = 0; i < questionCount; ++i) pushBack(new Question(fields));
    }

    //////////////// PUBLIC FUNCTIONS

    //// WRAPPER
    //display all information about the quiz
    public void display() {

        super.display();

        //if a student has taken the quiz, display the quiz results
        if (taken) displayResults();
        display(head);
    }

    //create the quiz with user input, give the user the option to make edits
    public void create() {

        System.out.print("\n======== QUESTION INPUT ========\n\n");

        //create the questions
        do {
            pushBack(new Question());
            ++questionCount;
            System.out.print("\nWOULD YOU LIKE TO ENTER ANOTHER QUESTION? (y/n)");

        } while (getYesNo());

        //echo back the quiz input
        System.out.print("\n======== QUIZ CREATED ========\n\n");
        display();
        System.out.print("QUESTION COUNT | " + questionCount + "\n\n");

        //give the user the option of editing the quiz
        System.out.print("WOULD YOU LIKE TO MAKE ANY EDITS?\n(y/n) >>> ");
        if (getYesNo()) edit();
    }

    //prompt a menu of options for the user to make a variety of edits to the quiz
    public void edit() {

        System.out.print("""

                0) quit
                1) set auto publish
                2) add a question
                3) edit questions

                 >>>\s""");

        switch (getInt(0, 3)) {

            case 1: setAutoPublish(); break;
            case 2: pushBack(new Question()); break;
            case 3: head = editQuestions(head); break;

            default: return;
        }

        edit();
    }

    //// WRAPPER
    //walk through the quiz questions, getting answers from the user
    public void interact() {

        //take the quiz
       correctCount = interact(head, 1);

       //calculate the student's percent grade
       if (0 != correctCount) grade = (float)(questionCount / correctCount) * 100.f;

       //display results if auto publish is set to on
       if (autoPublishGrades) {

           displayResults();
           display(head);
       }
    }

    //////////////// PRIVATE FUNCTIONS

    //add a question to the quiz
    private void pushBack(Question question) {

        //empty list
        if (head == null) {

            head = new QuestionNode(question);
            tail = head;
            return;
        }

        //grow the tail
        tail.setNext(new QuestionNode(question));
        tail = tail.next();
    }

    //// RECURSIVE
    //traverse the list with |head|, displaying all questions
    private void display(QuestionNode head) {

        if (head == null) return;
        head.display();
        display(head.next());
    }

    //display the results of the quiz
    private void displayResults() {

        System.out.print("\n======== QUIZ RESULTS ========\n" +
                         "CORRECT ANSWERS | " + correctCount + " / " + questionCount +
                         "\nGRADE | " + grade + "\n\n");
    }

    //set whether or not quiz grades should be automatically published with user input
    private void setAutoPublish() {

        System.out.print("WOULD YOU LIKE THE GRADES TO BE AUTOMATICALLY PUBLISHED AFTER COMPLETION?\n(y/n) >>> ");
        autoPublishGrades = getYesNo();

        if (autoPublishGrades) System.out.print("GRADES WILL BE AUTOMATICALLY PUBLISHED\n\n");
        else System.out.print("GRADES WILL NOT BE AUTOMATICALLY PUBLISHED\n\n");
    }

    //// WRAPPER
    //edit the questions recursively in the quiz
    private QuestionNode editQuestions(QuestionNode head) {

        if (head == null) return null;

        //display the question, and ask the user if they would like to edit
        head.display();
        System.out.print("WOULD YOU LIKE TO EDIT THIS QUESTION?\n(y/n) >>> ");

        if (getYesNo()) {

            //make a new question
            System.out.print("\nENTER NEW FIELDS FOR THIS QUESTION\n");
            QuestionNode newNode = new QuestionNode(new Question());

            newNode.setNext(head.next());
            head = newNode;

            return head;
        }

        head.setNext(editQuestions(head.next()));

        return head;
    }

    //// RECURSIVE
    //traverse the list with |head|, getting answers to each question from the user
    //returning the number of correct answers
    private int interact(QuestionNode head, int currentQuestion) {

        if (head == null) return 0;

        System.out.print("\nQUESTION " + currentQuestion + " / " + questionCount + "\n");
        ++currentQuestion;

        //the student's answer was correct
        if (head.getStudentAnswer()) return interact(head.next(), currentQuestion) + 1;

        //the student's answer was not correct
        return interact(head.next(), currentQuestion);
    }
}

//Sean Siders
//CS202
//Online Media System
//11/30/2020

/*
This abstraction manages a single question within a |Quiz|. In addition to a quiz, any number of answer keys
can be provided, as well as a description of the answer.
 */

import java.util.Scanner;

public class Question extends Utils {

    public static void main(String [] args) {

        Question q = new Question();
    }

    //////////////// FIELDS

    //the question
    String question;

    //all expected correct answers to the question
    String [] answerKeys;

    //the student's answer to the question
    String studentAnswer;

    //the author's description of the correct answer
    String description;

    //whether or not the student's answer was correct
    boolean correct;

    //////////////// CONSTRUCTORS

    public Question() {

        System.out.print("ENTER THE QUESTION >>> ");
        question = getString();

        System.out.print("ENTER A COMMA SEPARATED LIST OF CORRECT ANSWERS\n>>> ");
        answerKeys = getStringsFromCommaSeparatedList();

        System.out.print("ANSWER DESCRIPTION >>> ");
        description = getString();

        correct = false;
    }

    public Question(Question source) {

        this.question = source.question;
        this.answerKeys = source.answerKeys;
        this.studentAnswer = source.studentAnswer;
        this.description = source.description;
        this.correct = source.correct;
    }

    public Question(Scanner fields) {

        studentAnswer = null;
        correct = false;

        question = fields.next();
        answerKeys = new String[fields.nextInt()];

        //read in the answer keys
        for (int i = 0; i < answerKeys.length; ++i) answerKeys[i] = fields.next();

        description = fields.next();
    }

    //////////////// PUBLIC FUNCTIONS

    //display all correct answers to the question and the author's description of the answers
    //determine whether |studentAnswer| was a correct answer by comparing to |answerKeys|
    public void display() {

        System.out.print("QUESTION : " + question + "\n\n");

        if (studentAnswer != null) System.out.print("YOUR ANSWER : " + studentAnswer + "\n\n");

        System.out.print("CORRECT ANSWERS\n\n");
        for (int i = 0; i < answerKeys.length; ++i) {

            System.out.println((i + 1) + ": " + answerKeys[i] + "\n");
        }

        System.out.print("ANSWER DESCRIPTION : " + description + "\n\n");

        if (correct) System.out.print("YOUR ANSWER WAS CORRECT!\n\n");
    }

    //display the question and get an answer from the student
    //true if the student's answer was correct
    public boolean getStudentAnswer() {

        System.out.print(question + "\n\n");

        System.out.print("INPUT ANSWER >>> ");
        studentAnswer = getString();

        checkAnswer(studentAnswer);

        return correct;
    }

    //////////////// PRIVATE FUNCTIONS

    //check the student's answer against all correct answers
    //true if a non-case sensitive match is found
    private void checkAnswer(String studentAnswer) {

        for (int i = 0; !correct && i < answerKeys.length; ++i)  correct = answerKeys[i].equalsIgnoreCase(studentAnswer);
    }
}
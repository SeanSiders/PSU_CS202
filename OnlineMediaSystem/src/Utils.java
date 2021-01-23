//Sean Siders
//CS202
//Online Media System
//11/30/2020

/*
The |Scanner| class is used for all input in this program. Any possible input operations are within the
|Utils| class. |Calender| is also used to record the times of certain object creations.
 */

import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Calendar;

public class Utils {

    //////////////// FIELDS

    //input buffer for all user input
    private Scanner buffer;
    private Scanner externalDatabase;
    private Calendar calendar;

    //////////////// CONSTRUCTOR

    public Utils() {

        buffer = new Scanner(System.in);
        calendar = Calendar.getInstance();
    }

    //////////////// PUBLIC FUNCTIONS

    //attempt to open an external file that exists in |filepath|
    //load this file into |externalDatabase|
    public void loadFile(String filepath) throws FileNotFoundException {

        File database = new File(filepath);
        externalDatabase = new Scanner(database);
    }

    //read from the external data file up to the specified delimiter
    public String read(String delimiter) {

        //if the database has been completely read
        if (!externalDatabase.hasNextLine()) return null;

        externalDatabase.useDelimiter(delimiter);
        return externalDatabase.next();
    }

    //read an integer from the external data file up to the specified delimiter
    public int readInt(String delimiter) {

        //if the database has been completely read
        if (!externalDatabase.hasNextLine()) return 0;

        externalDatabase.useDelimiter(delimiter);
        return externalDatabase.nextInt();
    }

    //// WRAPPER
    public Scanner getFieldScanner(String delimiter) {

        return getFieldScanner(delimiter, 1);
    }

    //load a new scanner with the number of lines specified with |lineCount| from |externalDatabase|
    //this scanner contains all fields for a particular |Media| class
    public Scanner getFieldScanner(String delimiter, int lineCount) {

        //collect all field lines for the scanner
        StringBuilder fields = new StringBuilder();
        for (int i = 0; i < lineCount; ++i) fields.append(externalDatabase.nextLine()).append("\n");

        //create the scanner and set the delimiter
        Scanner fieldScanner = new Scanner(String.valueOf(fields));
        fieldScanner.useDelimiter(delimiter);
        return fieldScanner;
    }

    //get String input from the user
    public String getString() {

        return buffer.nextLine();
    }

    //get char input from the user
    public char getChar() {

        return buffer.nextLine().charAt(0);
    }

    // WRAPPER
    public int getInt() {

        return getInt(0, 2000000000);
    }

    //get string input from the user, then convert it to an integer
    //repeat the process if the user entered a non-integer
    public int getInt(int min, int max) {

        //value to return
        int intValue = 0;
        boolean isValid = false;

        do {

            //convert |digitInput| to a char array
            char[] cString = getString().toCharArray();
            int E = 1;

            //attempt to convert |cString| to an integer
            for (int i = cString.length - 1; i >= 0; --i) {

                //not integer input, request new input
                if (!Character.isDigit(cString[i])) {

                    System.out.print("INVALID INPUT : ENTER AN INTEGER\n valid range (" + min + ", " + max + ") >>> ");
                    cString = getString().toCharArray();

                    //reset the parameters
                    intValue = 0;
                    E = 1;

                    //decrements to the last element in the next iteration
                    i = cString.length;
                } else {

                    intValue += digitToInt(cString[i]) * E;
                    E *= 10;
                }
            }

            if (intValue < min || intValue > max)
                System.out.print("INVALID INPUT : ENTER AN INTEGER\n valid range (" + min + ", " + max + ") >>> ");
            else isValid = true;
        } while (!isValid);

        return intValue;
    }

    //// WRAPPER
    public float getFloat() {

        return getFloat(0.f, 2000000000.f);
    }

    //get string input from the user, then convert it to a float
    //repeat the process if the user entered a non-float
    public float getFloat(float min, float max) {

        //the converted float to return
        float floatValue = 0.f;
        boolean isValid = false;

        do {

            char[] cString = getString().toCharArray();

            //the current power of 10
            int E = 1;

            for (int i = cString.length - 1; i >= 0; --i) {

                //decimal encountered, divide by the power of 10
                if ('.' == cString[i]) {

                    floatValue /= E;

                    //the rest of integers will be the true integer values starting at E1
                    E = 1;
                }

                //the input was not a true float value, new input will be requested
                else if (!Character.isDigit(cString[i])) {

                    System.out.print("INVALID INPUT : ENTER A FLOAT\n valid range (" + min + ", " + max + ") >>> ");
                    cString = getString().toCharArray();

                    //initialize values for the new float conversion
                    floatValue = 0.f;
                    E = 1;

                    //decrements to the last element in the next iteration
                    i = cString.length;
                }

                //calculate the integer value using the power of 10 |E|.
                else {

                    floatValue += digitToInt(cString[i]) * E;

                    //calculate the new power of 10
                    E *= 10;
                }
            }

            if (floatValue < min || floatValue > max)
                System.out.print("INVALID INPUT : ENTER A FLOAT\n valid range (" + min + ", " + max + ") >>> ");
            else isValid = true;

        } while (!isValid);

        return floatValue;
    }

    public String getTimestamp() {

        return calendar.getTime().toString();
    }

    //get a y for yes or n for no, if y is input return true
    public boolean getYesNo() {

        char response = Character.toLowerCase(getChar());

        //invalid input case
        while ('y' != response && 'n' != response) {

            System.out.print("INVALID INPUT : ENTER A \"y\" for \"yes\" or \"n\" for \"no\"");
            response = Character.toLowerCase(getChar());
        }

        return 'y' == response;
    }

    //get a comma separated list from the user, place each item into an element of a String array
    //return the resulting array
    public String [] getStringsFromCommaSeparatedList() {

        //get the comma separated list
        String commaSeparatedList = getString();

        //determine the size of the answer array by counting the number of occurring ", "
        int commaCount = commaSeparatedList.split(", ", -1).length - 1;

        //allocate the String array to return
        String [] entries = new String[commaCount + 1];

        //parse the String, populating |entries|
        Scanner listParser = new Scanner(commaSeparatedList);

        listParser.useDelimiter(", ");

        //populate the array of strings
        for (int i = 0; i <= commaCount; ++i) entries[i] = listParser.next();

        return entries;
    }

    //////////////// PROTECTED FUNCTIONS

    //convert a char to it's respective integer value
    protected int digitToInt(char digit) {

        return digit - '0';
    }
}

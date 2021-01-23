//Sean Siders
//CS202
//Online Media System
//11/30/2020

/*
The |Date| abstraction holds integer values for each of the 3 entries in a date. Basic input checking
is performed to encourage valid date input.
 */

public class Date extends Utils {

    //////////////// FIELDS

    //integer values of the dates
    int month;
    int day;
    int year;

    //final values to indicate valid input ranges
    final int MONTH = 12;
    final int DAY = 31;

    //////////////// CONSTRUCTORS

    public Date() {

        System.out.print("MM/DD/YYYY >>> ");
        char [] cString = getString().toCharArray();

        while (!isValidDate(cString) || !convert(cString)) {

            System.out.print("INVALID INPUT\nMM/DD/YYYY >>> ");
            cString = getString().toCharArray();
        }
    }

    public Date(String date) {

        char [] cString = date.toCharArray();
        if (!convert(cString)) System.out.print("INVALID PARAMETERIZED DATE ARG : " + date + "\n\n");
    }

    public Date(Date source) {

        this.day = source.day;
        this.month = source.month;
        this.year = source.year;
    }

    //////////////// PUBLIC FUNCTIONS

    //display the formatted date
    public void display() {

        System.out.print(month + "/" + day + "/" + year);
    }

    //compare the integral date values, true if they match
    public boolean equals(Date other) {

        return  month == other.month &&
                day == other.day &&
                year == other.year;
    }

    //true of the char array contains a date string that is in the format DD/MM/YYYY
    private boolean isValidDate(char [] cString) {

        return  10 == cString.length &&
                Character.isDigit(cString[0]) &&
                Character.isDigit(cString[1]) &&
                '/' == cString[2] &&

                Character.isDigit(cString[3]) &&
                Character.isDigit(cString[4]) &&
                '/' == cString[5] &&

                Character.isDigit(cString[6]) &&
                Character.isDigit(cString[7]) &&
                Character.isDigit(cString[8]) &&
                Character.isDigit(cString[9]);
    }

    //convert |cString| into its respective int date values for day, month, and year
    //return false if these int values are semantically invalid
    private boolean convert(char [] cString) {

        if (10 != cString.length) return false;

        month = digitToInt(cString[1]) + digitToInt(cString[0]) * 10;
        if (month <= 0 || month > MONTH) return false;

        day = digitToInt(cString[4]) + digitToInt(cString[3]) * 10;
        if (day <= 0 || day > DAY) return false;

        year = 0;
        int E = 1;

        for (int i = cString.length - 1; i >= cString.length - 4; --i) {

            year += digitToInt(cString[i]) * E;
            E *= 10;
        }

        return 0 < year;
    }
}

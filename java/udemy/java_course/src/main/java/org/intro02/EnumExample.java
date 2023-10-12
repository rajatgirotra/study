package org.intro02;

import java.util.Arrays;

/*
all enums in java automatically extend the java.lang.Enum class
Enums are just names constants. Enums can also declare other fields which can help in constructing the enums.
Example:
 */

enum DaysOfTheWeek {
    SUNDAY (0),
    MONDAY (1),
    TUESDAY (0),
    WEDNESDAY (2),
    THURSDAY (0),
    FRIDAY (2),
    SATURDAY (1);

    // any fields you declare in enums must be final so that they cannot be modified from outside.
    final int gymHours;

    DaysOfTheWeek(int gymHours) {
        this.gymHours = gymHours;
    }
};

public class EnumExample {
    public static void main(String[] args) {
        DaysOfTheWeek mon = DaysOfTheWeek.MONDAY;
        System.out.println("Enum.MONDAY ordinal: " + mon.ordinal());
        System.out.println("Enum.MONDAY name: " + mon.name());
        System.out.println("Enum.MONDAY toString: " + mon.toString());
        try {
            System.out.println("Enum.valueOf: " + DaysOfTheWeek.valueOf("ABC")); // exception
        } catch(IllegalArgumentException e) {
            System.out.println("Exception: "  + e.getMessage());
        }
        System.out.println("Enum.valueOf: " + DaysOfTheWeek.valueOf("THURSDAY")); // Enum.valueOf() returns the enum object.

        // iterate all enum values
        for(var enumObj : DaysOfTheWeek.values()) {
            System.out.print(String.format("Gym hours on %s: %d%n", enumObj.toString(), enumObj.gymHours));
        }

        char[] JavaCharArray = new char[4];
JavaCharArray[0] = 'r';
JavaCharArray[1] = 's';
JavaCharArray[2] = 't';
JavaCharArray[3] = 'u';
System.out.println(JavaCharArray.length + " " + JavaCharArray[3]);

       char[] JavaCharArray2 = new char[4];
JavaCharArray2[0] = 'r';
JavaCharArray2[1] = 's';
JavaCharArray2[2] = 't';
JavaCharArray2[3] = 'u';
System.out.println(Boolean.valueOf(Arrays.equals(JavaCharArray, JavaCharArray2)));
    }
}

package org.example;

import java.time.LocalDate;
import java.time.Period;

// very trivial class which checks Customer fields are valid.
public class CustomerValidationService {

    private static boolean isEmailValid(Customer c) {
        return c.getEmail().contains("@"); // some stupid validation
    }

    private static boolean isPhoneNumberValid(Customer c) {
        return c.getPhoneNumber().startsWith("+"); // some stupid validation
    }

    private static boolean isAdult(Customer c) {
        return Period.between(c.getDob(), LocalDate.now()).getYears() > 21;
    }

    public static boolean isValid(Customer c) {
        return isEmailValid(c) && isAdult(c) && isPhoneNumberValid(c);
    }
}

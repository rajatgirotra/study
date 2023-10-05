package org.example;

import java.time.LocalDate;

public class CombinatorPattern {
    public static void main(String[] args) {
        Customer c = new Customer("Rajat Girotra",
                "a@a.com", "+6512345678", LocalDate.of(1998, 1, 31));

        // very basic way of performing customer validation.
        boolean valid = CustomerValidationService.isValid(c);
        System.out.println("Is Customer valid: " + valid);

        // A better way is to chain validators. See CustomerVali
    }
}

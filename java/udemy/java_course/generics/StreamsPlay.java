package org.example;

/*
Streams is an API introduced in Java 8 which works best with Collections.
It provides a number of methods to work with items in a Collection using a declarative approach instead of
manually writing for loops to traverse each item in Collection

Some of the API's we will try here are
filter()
sort()
allMatch()
anyMatch()
noneMatch()
map()
collectors.groupingBy()
max()
min()
 */

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

enum Gender {
    MALE, FEMALE
}


public class StreamsPlay {
    private static final Person[] personsAll = new Person[] {
            new Person("Rajat Girotra", 40, Gender.MALE, "rajat@java.com"),
            new Person("Vidhu Girotra", 22, Gender.FEMALE, "vidhu@java.com"),
            new Person("Kavish Gupta", 46, Gender.MALE, "kavish@java.com"),
            new Person("Pooja Verdi", 46, Gender.FEMALE, "pooja@java.com"),
            new Person("Jack Ma", 55, Gender.MALE, "jack@java.com"),
            new Person("Jenne Lee", 27, Gender.FEMALE, "jenne@java.com"),
            new Person("Kathy Wood", 6, Gender.FEMALE, "kathy@java.com"),
    };

    public static void main(String[] args) {
        List<Person> persons = new ArrayList<>(Arrays.asList(personsAll));

        // filter all females. filter takes a predicate. you have seen already that Predicate is a functional interface
        List<Person> collect = persons.stream()
                .filter(pp -> pp.gender().equals(Gender.FEMALE))
                .toList();
        System.out.println("Females in List:");
        collect.forEach(System.out::println); // method reference

        // sort. Comparator.comparing takes a Function<T, R>
        System.out.println("\nPersons sorted by age:");
        List<Person> sortedByAge = persons.stream()
                .sorted(Comparator.comparing(Person::age))
                .toList();
        sortedByAge.forEach(System.out::println);

        // sort. Comparator.comparing takes a Function<T, R>
        System.out.println("\nPersons sorted by age in decreasing order and then by name in increasing order");
        List<Person> sortedComplex = persons.stream()
                .sorted(Comparator.comparing(Person::age).reversed().thenComparing(Person::name))
                .toList();
        sortedComplex.forEach(System.out::println);

        // allMatch. allMatch takes a Predicate
        boolean bAllAbove10 = persons.stream().allMatch(pp -> pp.age() > 10);
        System.out.println("\nAre all persons above 10: " + bAllAbove10);

        // anyMatch. anyMatch takes a Predicate
        boolean bAnyAbove50 = persons.stream().anyMatch(pp -> pp.age() > 50);
        System.out.println("\nAny person above 50: " + bAnyAbove50);

        // noneMatch. noneMatch takes a Predicate
        boolean bNoOneAbove100 = persons.stream().noneMatch(pp -> pp.age() > 100);
        System.out.println("\nNo person above 100: " + bNoOneAbove100);

        // max and min. Max and Min take a Comparator.
        // and Comparator.comparing takes a Function<T, R> and returns a Comparator<R>
        // max returns an Optional<Integer>
        Person person = persons.stream()
                .max(Comparator.comparing(Person::age))
                .orElseThrow();
        System.out.println("\nPerson with max age is: " + person);

        // map.
        List<Integer> allAges = persons.stream().map(Person::age)
                .toList();
        System.out.println("\nAges of all person fetched using stream().map(): " + allAges);

        // create a grouping of Males and Females.
        Map<Gender, List<Person>> personsByGender = persons.stream()
                .collect(Collectors.groupingBy(Person::gender));
        System.out.println("\npersons grouped by gender");
        personsByGender.forEach((gender, genderList) -> {
            System.out.println(gender);
            genderList.forEach(System.out::println);
        });
    }
}

/* streams provide a very good way of chaining functions. We call it the combinator pattern.
It's like decorator in Python. Read CombinatorPattern.java next
 */
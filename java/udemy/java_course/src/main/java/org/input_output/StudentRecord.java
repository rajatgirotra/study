package org.input_output;

import java.time.Month;
import java.util.Random;

// StudentId, Country, YearOfEnrollment, Age, Gender, Major, InternshipMonth, GPA"
public class StudentRecord {
    private static Random random = new Random();
    private static String[] countryCodes= {"IN", "US", "CN", "UK", "CA", "HK", "SG", "AU", "NZ"};
    private int studentId;
    private String country;
    private int yearOfEnrollment;
    private int age;
    private char gender;

    private String major;
    private String internshipMonth;
    private double gpa;

    public static StudentRecord getRandomStudentRecord() {
        return new StudentRecord();
    }
    private StudentRecord() {
        studentId = getRandomStudentId();
        country = getRandomCountry();
        yearOfEnrollment = getRandomYearOfEnrollment();
        age = getRandomAge();
        gender = getRandomGender();
        major = getRandomMajor();
        internshipMonth = getRandomInternshipMonth();
        gpa = getRandomGPA();
    }

    private int getRandomStudentId() {
        return random.nextInt(1000, 9999);
    }

    private String getRandomCountry() {
        return countryCodes[random.nextInt(countryCodes.length)];
    }

    private int getRandomYearOfEnrollment() {
        return random.nextInt(2002, 2023);
    }
    private int getRandomAge() {
        return random.nextInt(22, 61);
    }

    private char getRandomGender() {
        char[] gender = {'M', 'F'};
        return gender[random.nextInt(gender.length)];
    }

    private String getRandomMajor() {
        String[] majors = {"Computer Science", "Business Finance", "Retail Marketing", "Business Development", "Human Resources"};
        return majors[random.nextInt(majors.length)];
    }

    private String getRandomInternshipMonth() {
        return Month.of(random.nextInt(1,12)).toString();
    }

    private double getRandomGPA() {
        return random.nextDouble(50.0, 99.9);
    }

    @Override
    public String toString() {
        return studentId
                + "," + country
                + "," + yearOfEnrollment
                + "," + age
                + "," + gender
                + "," + major
                + "," + internshipMonth
                + "," + String.format("%.2f", gpa);
    }

    public int getStudentId() {
        return studentId;
    }

    public String getCountry() {
        return country;
    }

    public int getYearOfEnrollment() {
        return yearOfEnrollment;
    }

    public int getAge() {
        return age;
    }

    public char getGender() {
        return gender;
    }

    public String getMajor() {
        return major;
    }

    public String getInternshipMonth() {
        return internshipMonth;
    }

    public double getGpa() {
        return gpa;
    }
}

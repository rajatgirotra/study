package org.example;


public record Person(String name, int age, Gender gender, String email) {
    @Override
    public String name() {
        return name;
    }

    @Override
    public int age() {
        return age;
    }

    @Override
    public Gender gender() {
        return gender;
    }

    @Override
    public String email() {
        return email;
    }
}

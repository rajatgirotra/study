package org.intro01;

public class Main_07 {
    public static void main(String[] args) {
//        SalariedEmployee se = new SalariedEmployee("Rajat Girotra", "1983-05-21",
//                206905, "2020-11-02", 145000, false);
//        System.out.println("Age is " + se.getAge());
//        se.collectPay();
//        se.retire();

        Employee tim = new Employee("Tim", "1983-05-21", "2020-11-02");
        System.out.println(tim);
        System.out.println("Age is " + tim.getAge());
        System.out.println("Pay is " + tim.collectPay());

        SalariedEmployee joe = new SalariedEmployee("Joe", "1984-09-06", "2023-05-29", 150000);
        System.out.println(joe);
        System.out.println("Age is " + joe.getAge());
        System.out.println("Joe's paycheck is $" + joe.collectPay());
        joe.retire();
        System.out.println("Joe's pension pay is $" + joe.collectPay());


    }
}

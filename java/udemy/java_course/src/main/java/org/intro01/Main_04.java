package org.intro01;

public class Main_04 {
    public static void main(String[] args) {
        Account acc = new Account();

        acc.setCustomerName("RajatGirotra");
        acc.setCustomerPhone("81684024");
        acc.setCustomerEmail("rajatgirotra@yahoo.com");

        System.out.println("New account balance of " + acc.getCustomerName() + " is $" + acc.getAccountBalance());
        acc.withdraw(300);
        acc.deposit(50.5);
        acc.withdraw(250.51);
        acc.withdraw(250.5);

        for(int i = 1; i <= 5; ++i) {
            Student s = new Student("S92300" + i,
                    switch(i) {
                       case 1 -> "Rajat";
                        case 2 -> "Vidhu";
                        case 3 -> "Myra";
                        case 4 -> "Viraj";
                        case 5 -> "Prisha";
                        default -> "Anonymous";
                    }, "21-05-1983", "Java Masterclass");
            System.out.println(s);
        }

        for(int i = 1; i <= 5; ++i) {
            LPAStudent s = new LPAStudent("X92300" + i,
                    switch(i) {
                        case 1 -> "Rajat";
                        case 2 -> "Vidhu";
                        case 3 -> "Myra";
                        case 4 -> "Viraj";
                        case 5 -> "Prisha";
                        default -> "Anonymous";
                    }, "06-09-1984", "Java Masterclass");
            System.out.println(s);
            System.out.println(s.id());
        }


    }
}

package org.multithreading;

public class BankAccountTest {
    public static void main(String[] args) {
        BankAccount account = new BankAccount(1000, "12345-678");
        var t1 = new Thread(new DepositAndWithdraw(account, 300, 50));
        var t2 = new Thread(new DepositAndWithdraw(account, 203.75, 100));

        t1.start(); t2.start();

        try {
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        System.out.println(account);

    }
}

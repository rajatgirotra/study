package org.multithreading;

import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class BankAccount {
    private double balance;
    private final String accountNumber;

    private final Lock lock;

    public BankAccount(double balance, String accountNumber) {
        this.balance = balance;
        this.accountNumber = accountNumber;
        this.lock = new ReentrantLock(true);
    }

//    public synchronized void deposit(double amount) {
//        this.balance += amount;
//    }
//
//    public synchronized void withdraw(double amount) {
//        this.balance -= amount;
//    }

//    public synchronized void deposit(double amount) {
//        synchronized (this) {
//            this.balance += amount;
//        }
//
//    }
//
//    public synchronized void withdraw(double amount) {
//        synchronized (this) {
//            this.balance -= amount;
//        }
//    }
    public void deposit(double amount) {
        boolean status = false;
        try {
            if(lock.tryLock(1, TimeUnit.SECONDS)) {
                try {
                    this.balance += amount;
                    //Thread.sleep(2000);
                    status = true;
                } finally {
                    lock.unlock();
                }
            } else {
                System.out.println("Could not get lock");
            }
        }catch(InterruptedException e) {
            System.out.println("deposit interrupted");
        }
        System.out.println("Deposit status: " + status);
    }

    public void withdraw(double amount) {
        boolean status = false;
        try {
            if(lock.tryLock(1, TimeUnit.SECONDS)) {
                try {
                    this.balance -= amount;
                    status = true;
                } finally {
                    lock.unlock();
                }
            } else {
                System.out.println("Could not get lock");
            }
        }catch(InterruptedException e) {
            System.out.println("withdraw interrupted");
        }
        System.out.println("Deposit status: " + status);
    }

    @Override
    public String toString() {
        return "BankAccount{" +
                "balance=" + balance +
                ", accountNumber='" + accountNumber + '\'' +
                '}';
    }

    public String getAccountNumber() {
        return accountNumber;
    }

    public void printAccountNumber() {
        System.out.println("AccountNumber: " + accountNumber);
    }
}

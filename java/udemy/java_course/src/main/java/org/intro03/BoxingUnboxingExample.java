package org.intro03;

import java.util.*;

class Customer {
    private String name;
    private ArrayList<Double> transactions = null;

    public Customer(String name) {
        this.name = name;
        this.transactions = new ArrayList<>();
    }

    @Override
    public boolean equals(Object o) {
        if(!(o instanceof Customer)) {
            return false;
        }
        if(o != this) {
            Customer c = (Customer)o;
            return this.name.equalsIgnoreCase(c.name);
        }
        return true;
    }

    public void addTransaction(double value) {
        transactions.add(value);
    }

    public void printTransaction() {
        System.out.println(String.format("Transactions for customer %s", name));
        var sep = new String("*").repeat(30);
        System.out.println(sep);
        if(transactions.isEmpty()) {
            System.out.println("No transactionss found");
        } else {
            for(var trans : transactions) {
                if(trans < 0) {
                    System.out.println(String.format("Debit of %f", trans));
                } else {
                    System.out.println(String.format("Credit of %f", trans));
                }
            }
        }
        System.out.println(sep);
    }
}

class Bank {
    private String bankName;
    private ArrayList<Customer> customers = null;

    public Bank(String bankName) {
        this.bankName = bankName;
        this.customers = new ArrayList<>();
    }

    public void addCustomer(String name) {
        if(customers.contains(new Customer(name))) {
            System.out.println("Customer already exists");
            return;
        }
        customers.add(new Customer(name));
        System.out.println(String.format("Customer %s added", name));
    }

    public void addTransaction(String customerName, double value) {
        var idx = customers.indexOf(new Customer(customerName));
        if(idx < 0) {
            System.out.println(String.format("Customer %s not found. failed to add transaction", customerName));
        }
        customers.get(idx).addTransaction(value);
    }

    public void printTransactions() {
        System.out.println(String.format("Bank %s", bankName));
        for(var c : customers) {
            c.printTransaction();
        }
    }
}

public class BoxingUnboxingExample {
    public static void main(String[] args) {
        Bank bank = new Bank("DBS Bank");
        bank.addCustomer("Rajat");
        bank.addCustomer("Vidhu");
        
        
        bank.addTransaction("Rajat", 100);
        bank.addTransaction("Vidhu", 200);
        bank.addTransaction("Vidhu", -8200);
        bank.printTransactions();
    }
}
package org.multithreading;

public class DepositAndWithdraw implements Runnable {
    private BankAccount account;
    private final double depositAmount;
    private final double withdrawAmount;

    public DepositAndWithdraw(BankAccount account, double depositAmount, double withdrawAmount) {
        this.account = account;
        this.depositAmount = depositAmount;
        this.withdrawAmount = withdrawAmount;
    }

    @Override
    public void run() {
        this.account.deposit(depositAmount);
        this.account.withdraw(withdrawAmount);
    }
}

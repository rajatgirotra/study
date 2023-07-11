public class Account {
    private String m_accountNumber;
    private double m_accountBalance;
    private String m_customerName;
    private String m_customerEmail;
    private String m_customerPhone;

    public Account() {
        this("12345", 500.00, "UnknownCustomer", "unknown@unknown.com", "(087) 123-4567");
    }

    public Account(String m_customerName, String m_customerEmail, String m_customerPhone) {
        this("12345", 500.00, m_customerName, m_customerEmail, m_customerPhone);
    }

    public Account(String m_accountNumber, double m_accountBalance, String m_customerName, String m_customerEmail, String m_customerPhone) {
        this.m_accountNumber = m_accountNumber;
        this.m_accountBalance = m_accountBalance;
        this.m_customerName = m_customerName;
        this.m_customerEmail = m_customerEmail;
        this.m_customerPhone = m_customerPhone;
    }

    public String getAccountNumber() {
        return m_accountNumber;
    }

    public void setAccountNumber(String m_accountNumber) {
        this.m_accountNumber = m_accountNumber;
    }

    public double getAccountBalance() {
        return m_accountBalance;
    }

    public void setAccountBalance(double m_accountBalance) {
        this.m_accountBalance = m_accountBalance;
    }

    public String getCustomerName() {
        return m_customerName;
    }

    public void setCustomerName(String m_customerName) {
        this.m_customerName = m_customerName;
    }

    public String getCustomerEmail() {
        return m_customerEmail;
    }

    public void setCustomerEmail(String m_customerEmail) {
        this.m_customerEmail = m_customerEmail;
    }

    public String getCustomerPhone() {
        return m_customerPhone;
    }

    public void setCustomerPhone(String m_customerPhone) {
        this.m_customerPhone = m_customerPhone;
    }

    public void deposit(double money_in) {
        this.m_accountBalance += money_in;
        System.out.println("Deposited $" + money_in + " in account " + this.m_accountNumber + ". Clear balance is $" + this.m_accountBalance);
    }

    public void withdraw(double money_out) {
        if (this.m_accountBalance - money_out < 0) {
            System.out.println("Withdrawal of $" + money_out + " failed from account " + this.m_accountNumber + ". balance of $" + this.m_accountBalance + " is too low.");
        } else {
            this.m_accountBalance -= money_out;
            System.out.println("Withdrawal of $" + money_out + " successful from account " + this.m_accountNumber + ". Clear balance is $" + this.m_accountBalance);
        }
    }
}

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
    }
}

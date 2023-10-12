package org.intro02;

public class Printer {
    private int tonerLevel;
    private int pagesPrinted;
    private boolean duplex;    

    public Printer(int toner, boolean duplex) {
        this.tonerLevel = (toner <= 100 && toner >= 0 ? toner : -1);
        this.duplex = duplex;
        this.pagesPrinted = 0;
    }

    public int addToner(int tonerAmount) {
        int newLevel = this.tonerLevel + tonerAmount;
        if(newLevel > 100 || newLevel < 0) return -1;
        this.tonerLevel = newLevel;
        return newLevel;
    }

    public int getPagesPrinted() {
        return pagesPrinted;
    }

    public int printPages(int pageCount) {
        int pagesToPrint = pageCount;
        if(this.duplex) {
            pagesToPrint = (pagesToPrint / 2) + (pagesToPrint % 2);
            System.out.println("Duplex printing is enabled");
        }
        pagesPrinted += pagesToPrint;
        return pagesToPrint;
    }

    public void test() {
        System.out.println(String.format("%s", getClass().getSimpleName()));
    }

    public static void main(String[] args) {
        Printer printer = new Printer(50, true);
        System.out.println("initial page count = " + printer.getPagesPrinted());

        int pagesPrinted = printer.printPages(5);
        System.out.printf("Current Job Pages: %d, Printer Total: %d %n",
                pagesPrinted, printer.getPagesPrinted());

        pagesPrinted = printer.printPages(10);
        System.out.printf("Current Job Pages: %d, Printer Total: %d %n",
                pagesPrinted, printer.getPagesPrinted());

        printer.test();

    }

}

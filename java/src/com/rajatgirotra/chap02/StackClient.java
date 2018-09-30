package com.rajatgirotra.chap02;

public class StackClient {
    public static void main(String[] args) {
        PrintableStack ps = new PrintableStack(40);
        String line = "!no tis ot nuf era skcatS";

        for(int i = 0; i < line.length(); ++i) {
            ps.push(line.charAt(i));
        }

        ps.popAndPrintStack();
    }
}

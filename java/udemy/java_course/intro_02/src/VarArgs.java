package intro_02.src;

public class VarArgs {
    // We can also pass variable number of arguments like this "String... args" instead of "String[] args"
    // this way you can pass multiple String as arguments or a String array, both
    public static void main(String... args) {
        // System.out.println(args); // works as usual

        String text = "Hello World";
        printText(text); // pass a single String

        printText(text.split(" ")); // pass an array of Strings

        printText("Hello", "World", "Goodbye"); // pass multiple string arguments
    }

    // remember can only have one variable arguments in a method, and that must be the last one
    public static void printText(String... args) {
        System.out.println("-".repeat(20));
        for(int i = 0; i < args.length; ++i) {
            System.out.println(args[i]);
        }
    }
}

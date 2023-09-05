public class Main_09 {
    public static void main(String[] args) {
        // a new way to create multi line strings easily in Java is to enclose them inside """ """.
        String multiLineString = """
            A multi line bulleted list:
                \u2022 First point.
                    \u2022 Second sub point.
                """;
        
        System.out.println(multiLineString);

        // System.out.printf() is for formatting just like in C/C++
        int age = 40;
        System.out.printf("You age is %d%n", age); // %n is same as \n but, %n will output the platform specific line separator.

        int yearOfBirth = 2023 - age;
        System.out.printf("Age: %d, BirthYear: %d%n", age, yearOfBirth);
        System.out.printf("Age: %.2f", (float)age); // print as float

        for(int i = 1; i < 1000000; i *= 10) {
            System.out.println("Printing:" + i);
        }

        // same as above but with right alignment
        for(int i = 1; i < 1000000; i *= 10) {
            System.out.printf("Printing %7d%n", i);
        }

        // for string objects, we can use format() or formatted() functions
        String formattedString = String.format("Your age is: %d%n", age);
        System.out.println(formattedString);

        formattedString = "Age: %d, BirthYear: %d%n".formatted(age, yearOfBirth);
        System.out.println(formattedString);

    }
}

// Filename: Temperature.java
public class Temperature {
    public static void main(String args[]) {
        float fahrenheit = 62.5f;

        /* Convert */
        float celsius = 0.0f;
        Temperature poTemp = new Temperature();

        celsius = poTemp.f2c(fahrenheit);
        System.out.println(fahrenheit + "F = " + celsius + 'C');
    }

    float f2c(double fahr) {
        return (float) ((fahr - 32) * 5 / 9);
    }
}


/*

C = 5
    -  * (F - 32)
    9

*/
package intro_02.src;

import java.util.Arrays;
import java.util.Random;


public class SortArray {
    public static void main(String[] args) {
        int[] arr = new int[10];
        Random random = new Random();

        for(int i = 0; i < arr.length; ++i) {
            arr[i] = random.nextInt(100);
        }

        System.out.println("Unsorted array: " + Arrays.toString(arr));
        Arrays.sort(arr);
        for(int i = 0, j = arr.length-1; i < arr.length/2; ++i, --j) {
            var temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
        System.out.println("sorted array: " + Arrays.toString(arr));

    }
}
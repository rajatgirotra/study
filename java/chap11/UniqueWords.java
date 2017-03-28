/*
 * Please read Stack.java first
 * Read all the unique words in a file and print them out.
 */

import com.rajatgirotra.util.*;
import java.util.*;
public class UniqueWords {
	public static void main(String[] args) {
		Set<String> words = new TreeSet<String>(
				new TextFile("D:\\Study\\JAVA\\my_practice\\TIJ4\\chap11\\Stack.java", "\\r+"));
		System.out.println(words);
		
		//Doing a case insensitive search
		Set<String> noCaseWords = new TreeSet<String>(String.CASE_INSENSITIVE_ORDER); //Make it case insensitive
		noCaseWords.addAll(new TextFile("D:\\Study\\JAVA\\my_practice\\TIJ4\\chap11\\Stack.java", "\\r+"));
		System.out.println(noCaseWords);
	}
}

/*
Please read PetMap.java next
*/
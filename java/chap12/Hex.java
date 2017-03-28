/*
 * Please read DatabaseException.java first.
 * Demonstrate the use of Formatter.format() to produce a HEX DUMP.
 */

import java.util.*;
import com.rajatgirotra.util.*;
import java.io.*;
public class Hex {
	
	public static String produceHexDump(byte[] data) {
		StringBuilder sb = new StringBuilder();
		int n = 0;
		for(byte b : data) {
			if(n % 32 == 0)
				sb.append(String.format("%05X: ", n));
			sb.append(String.format("%02X ", b));
			++n;
			if(n % 32 == 0) {
				sb.append("\n");				
			}
		}
		sb.append("\n");
		return sb.toString();
	}
	
	public static void main(String[] args) throws IOException {
		if(args.length == 0) {
			System.out.println(produceHexDump(BinaryFile.read(new File("D:\\Study\\JAVA\\my_practice\\TIJ4\\chap12\\bin\\Hex.class"))));
		}
		else {
			System.out.println(produceHexDump(BinaryFile.read(new File(args[0]))));
		}
	}
}

/*
please read integerMatch.java next
*/
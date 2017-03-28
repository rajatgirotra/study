/*
 * Please read MapGenerator.java first
 */
package com.rajatgirotra.util;

import java.util.*;

public class Arrays2 {
	public static String toString(boolean[] a) {
		StringBuffer result = new StringBuffer("[ ");
		for(int i = 0; i < a.length; ++i) {
			result.append(a[i]);
			if( i < a.length -1 ) {
				result.append(", ");				
			}
		}
		result.append(" ]");
		return result.toString();
	}

	public static String toString(char[] a) {
		StringBuffer result = new StringBuffer("[ ");
		for(int i = 0; i < a.length; ++i) {
			result.append(a[i]);
			if( i < a.length -1 ) {
				result.append(", ");				
			}
		}
		result.append(" ]");
		return result.toString();
	}

	public static String toString(byte[] a) {
		StringBuffer result = new StringBuffer("[ ");
		for(int i = 0; i < a.length; ++i) {
			result.append(a[i]);
			if( i < a.length -1 ) {
				result.append(", ");				
			}
		}
		result.append(" ]");
		return result.toString();
	}

	public static String toString(short[] a) {
		StringBuffer result = new StringBuffer("[ ");
		for(int i = 0; i < a.length; ++i) {
			result.append(a[i]);
			if( i < a.length -1 ) {
				result.append(", ");				
			}
		}
		result.append(" ]");
		return result.toString();
	}

	public static String toString(int[] a) {
		StringBuffer result = new StringBuffer("[ ");
		for(int i = 0; i < a.length; ++i) {
			result.append(a[i]);
			if( i < a.length -1 ) {
				result.append(", ");				
			}
		}
		result.append(" ]");
		return result.toString();
	}

	public static String toString(long[] a) {
		StringBuffer result = new StringBuffer("[ ");
		for(int i = 0; i < a.length; ++i) {
			result.append(a[i]);
			if( i < a.length -1 ) {
				result.append(", ");				
			}
		}
		result.append(" ]");
		return result.toString();
	}

	public static String toString(float[] a) {
		StringBuffer result = new StringBuffer("[ ");
		for(int i = 0; i < a.length; ++i) {
			result.append(a[i]);
			if( i < a.length -1 ) {
				result.append(", ");				
			}
		}
		result.append(" ]");
		return result.toString();
	}

	public static String toString(double[] a) {
		StringBuffer result = new StringBuffer("[ ");
		for(int i = 0; i < a.length; ++i) {
			result.append(a[i]);
			if( i < a.length -1 ) {
				result.append(", ");				
			}
		}
		result.append(" ]");
		return result.toString();
	}

	public static String toString(Object[] a) {
		StringBuffer result = new StringBuffer("[ ");
		for(int i = 0; i < a.length; ++i) {
			result.append(a[i]);
			if( i < a.length -1 ) {
				result.append(", ");				
			}
		}
		result.append(" ]");
		return result.toString();
	}

	public static void fill (Object[] a, Generator gen) {
		fill(a, 0, a.length, gen);
	}

	public static void fill (Object[] a, int from, int to, Generator gen) {
		for(int i = from; i < to; ++i) {
			a[i] = gen.next();
		}
	}

	public static void fill (char[] a, CharGenerator gen) {
		fill(a, 0, a.length, gen);
	}

	public static void fill (char[] a, int from, int to, CharGenerator gen) {
		for(int i = from; i < to; ++i) {
			a[i] = gen.next();
		}
	}

	public static void fill (byte[] a, ByteGenerator gen) {
		fill(a, 0, a.length, gen);
	}

	public static void fill (byte[] a, int from, int to, ByteGenerator gen) {
		for(int i = from; i < to; ++i) {
			a[i] = gen.next();
		}
	}

	public static void fill (short[] a, ShortGenerator gen) {
		fill(a, 0, a.length, gen);
	}

	public static void fill (short[] a, int from, int to, ShortGenerator gen) {
		for(int i = from; i < to; ++i) {
			a[i] = gen.next();
		}
	}

	public static void fill (int[] a, IntGenerator gen) {
		fill(a, 0, a.length, gen);
	}

	public static void fill (int[] a, int from, int to, IntGenerator gen) {
		for(int i = from; i < to; ++i) {
			a[i] = gen.next();
		}
	}
	
	public static void fill (long[] a, LongGenerator gen) {
		fill(a, 0, a.length, gen);
	}

	public static void fill (long[] a, int from, int to, LongGenerator gen) {
		for(int i = from; i < to; ++i) {
			a[i] = gen.next();
		}
	}
	

	public static void fill (float[] a, FloatGenerator gen) {
		fill(a, 0, a.length, gen);
	}

	public static void fill (float[] a, int from, int to, FloatGenerator gen) {
		for(int i = from; i < to; ++i) {
			a[i] = gen.next();
		}
	}

	public static void fill (double[] a, DoubleGenerator gen) {
		fill(a, 0, a.length, gen);
	}

	public static void fill (double[] a, int from, int to, DoubleGenerator gen) {
		for(int i = from; i < to; ++i) {
			a[i] = gen.next();
		}
	}

	public static void fill (boolean[] a, BooleanGenerator gen) {
		fill(a, 0, a.length, gen);
	}

	public static void fill (boolean[] a, int from, int to, BooleanGenerator gen) {
		for(int i = from; i < to; ++i) {
			a[i] = gen.next();
		}
	}

	private static Random rand = new Random();
	private static String alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	public static class RandCharGenerator implements CharGenerator {
		// A static nested class can access static variables of its enclosing class.
		private char[] src = alphabets.toCharArray();
		public char next() {
			return src[rand.nextInt(src.length)];
		}
	}
	public static class	RandStringGenerator implements Generator {
		private int len;
		private RandCharGenerator cg = new RandCharGenerator();
		public RandStringGenerator(int length) {
			len = length;
		}
		public Object next() {
			char[] buf = new char[len];
			for(int i = 0; i < len; i++)
				buf[i] = cg.next();
			//String c'tor that takes a char array to initialize itself.
			return new String(buf);
		}
	}

	public static class RandBooleanGenerator implements BooleanGenerator {
		public boolean next() {
			return rand.nextBoolean();
		}
	}

	public static class RandIntGenerator implements IntGenerator {
		int mod = 10000;
		public RandIntGenerator() {}
		public RandIntGenerator(int modulo) { mod = modulo; }
		public int next() {
			return rand.nextInt(mod);
		}
	}

	public static class RandFloatGenerator implements FloatGenerator {
		public float next() {
			return rand.nextFloat();
		}
	}

	public static class RandDoubleGenerator implements DoubleGenerator {
		public double next() {
			return rand.nextDouble();
		}
	}

	public static class RandLongGenerator implements LongGenerator {
		public long next() {
			return rand.nextLong();
		}
	}

	public static class RandShortGenerator implements ShortGenerator {
		public short next() {
			return (short)rand.nextInt();
		}
	}
	public static class RandByteGenerator implements ByteGenerator {
		public byte next() {
			return (byte)rand.nextInt();
		}
	}
}

/*
Please read Collections2.java next
*/
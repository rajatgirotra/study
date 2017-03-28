/*
 * Please read Must_Read_1.txt first
 */

import java.util.*;

class Frob {}
class Fnorkle {}
class Quark<Q> {}
class Particle<POSITION,MOMENTUM> {}

public class LostInformation {
	public static void main(String[] args) {
		List<Frob> list = new ArrayList<Frob>();
		
		Map<Frob,Fnorkle> map = new HashMap<Frob,Fnorkle>();
		
		Quark<Fnorkle> quark = new Quark<Fnorkle>();
		
		Particle<Long,Double> p = new Particle<Long,Double>();
		
		System.out.println(Arrays.toString(list.getClass().getTypeParameters())); //at run time the type parameter gets erased to its raw type which is List
		// and inside the JAVA source code a list interface is declared as interface List<E>; so the output here is that identifier "E". 
		System.out.println(Arrays.toString(map.getClass().getTypeParameters())); // same as above. interface Map<K, V>
		System.out.println(Arrays.toString(quark.getClass().getTypeParameters()));//similarly here the raw type is Quarke for which the type identifier is Q. 
		System.out.println(Arrays.toString(p.getClass().getTypeParameters()));		
	}
}

/*
Please read Templates.cpp next
*/
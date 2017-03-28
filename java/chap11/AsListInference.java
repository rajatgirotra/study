/*
 * Please read AddingGroups.java first.
 * A restriction with the Arrays.asList() interface is that it assumed the type of the list it is assigning
 * to, and does not pay attention to what we specify as the generic on the left hand side. We can overcome
 * that by using an "EXPLICIT TYPE ARGUMENT SPECIFICATION".
 * On the other hand Collections.addAll() do not have this problem, as they deduce the generic type from
 * the first argument.
 */

import java.util.*;

class PPet {	
}
class DDog extends PPet {	
}
class CCat extends PPet {	
}
class CCow extends PPet {	
}
class Breezer extends DDog {	
}
class ScoobyDoo extends DDog {	
}
class Kitty extends CCat {	
}

public class AsListInference {
	public static void main(String[] args) {
		 List<PPet> petList = Arrays.asList(new DDog(), new CCat(), new CCow()); // This is OK.
		 
		 //Wont Compile:
		 //Error msg: Type mismatch: cannot convert from List<Breezer> to List<Pet>
		 //List<Pet> petList1 = Arrays.asList(new Breezer());
		 //List<Pet> petList2 = Arrays.asList(new Kitty());
		 //List<Pet> petList3 = Arrays.asList(new ScoobyDoo(), new Breezer());
		 
		 //Strange enough, this works..!!
		 List<PPet> petList4 = Arrays.asList(new Breezer(), new Kitty());
		 for(PPet c : petList4) {
			 System.out.println(c);
		 }
		 
		 //To make the above work, you would need to give the compiler a hint as below:
		 List<PPet> petList1 = Arrays.<PPet>asList(new Breezer());
		 List<PPet> petList2 = Arrays.<PPet>asList(new Kitty());
		 List<PPet> petList3 = Arrays.<PPet>asList(new ScoobyDoo(), new Breezer());
		  for(PPet c : petList1) {
			 System.out.println(c);
		 }
		 
		 for(PPet c : petList2) {
			 System.out.println(c);
		 }
		 for(PPet c : petList3) {
			 System.out.println(c);
		 }
		 
		 //or you can say.
		 List<? extends PPet> petList6 = Arrays.asList(new ScoobyDoo(), new Breezer());
		 
		 //Collections.addAll() work OK..
		 List<PPet> petList5 = new ArrayList<PPet>();
		 Collections.addAll(petList5, new PPet(), new DDog(), new CCat(), new CCow(),
				 			new Breezer(), new ScoobyDoo(), new Kitty());
		 
		  for(PPet c : petList5) {
			 System.out.println(c);
		 }		 
	}
}


/*
Please read PrintingContainers.java next
*/
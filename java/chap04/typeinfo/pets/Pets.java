package typeinfo.pets;

import java.util.ArrayList;

public class Pets {
	private static PetCreator petCreator = new LiteralPetCreator();
	
	public static Pet randomPet() {
		return petCreator.randomPet();
	}
	
	public static Pet[] createArray(int size) {
		return petCreator.createArray(size);
	}
	
	public static ArrayList<Pet> arrayList(int size) {
		return petCreator.arrayList(size);
	}
}

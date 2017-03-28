package typeinfo.pets;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public abstract class PetCreator {
	public abstract List<Class<? extends Pet>> types();
	private static Random rand = new Random(47);
	public Pet randomPet() {
		int n = rand.nextInt(types().size());
		try {
			return types().get(n).newInstance();
		} catch (InstantiationException e) {
			throw new RuntimeException(e);			
		} catch (IllegalAccessException e) {
			throw new RuntimeException(e);
		}
	}
	
	public Pet[] createArray(int size) {
		Pet p[] = new Pet[size];
		for(int i = 0; i < size; ++i) {
			p[i] = randomPet();
		}
		return p;
	}
	
	public ArrayList<Pet> arrayList(int size) {
		ArrayList<Pet> arrayList = new ArrayList<Pet>();
		Collections.addAll(arrayList, createArray(size));
		return arrayList;
	}
}

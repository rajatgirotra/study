package typeinfo.pets;

import java.util.ArrayList;
import java.util.List;

public class ForNameCreator extends PetCreator{
	private static List<Class<? extends Pet>> arrayList = new ArrayList<Class<? extends Pet>>();
	
	private static String typeNames[] = {
											"typeinfo.pets.Mutt",
											"typeinfo.pets.Pug",
											"typeinfo.pets.Cymric",
											"typeinfo.pets.Manx",
											"typeinfo.pets.EgyptianMau",
											"typeinfo.pets.Hamster",
										};
	
	static {
		loader();
	}
	@SuppressWarnings("unchecked")
	private static void loader() {
		for(String name : typeNames) {
			try {
				arrayList.add((Class<? extends Pet>) Class.forName(name));
			} catch (ClassNotFoundException e) {
				throw new RuntimeException(e);
			}
		}
	}	
	public List<Class<? extends Pet>> types() {
		return arrayList;
	}
}

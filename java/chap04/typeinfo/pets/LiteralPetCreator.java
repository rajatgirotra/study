package typeinfo.pets;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class LiteralPetCreator extends PetCreator{
	@SuppressWarnings("unchecked")
	public static List<Class<? extends Pet>> petList = 
		Collections.unmodifiableList(Arrays.asList(Pet.class, Dog.class, Cat.class, Rodent.class, Cymric.class, 
				                                   EgyptianMau.class, Hamster.class, Manx.class, Mouse.class, Mutt.class,
				                                   Pug.class, Rat.class));
	
	private static List<Class<? extends Pet>> restrictedList = petList.subList(petList.indexOf(Cymric.class), petList.size());
	
	public List<Class<? extends Pet>> types() {
		return restrictedList;
	}
	
	public static void main(String[] args) {
		System.out.println(restrictedList);
	}
}

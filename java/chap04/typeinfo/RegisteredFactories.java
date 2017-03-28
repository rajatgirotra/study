package typeinfo;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Random;

class Part {
	public String toString() {
		return getClass().getSimpleName();
	}
	
	//Create a static list of Factories.
	@SuppressWarnings("unchecked")
	private static List<Class<? extends Part>> list = 
						Collections.unmodifiableList(Arrays.asList(FuelFilter.class, AirFilter.class, FanBelt.class, GeneratorBelt.class));
	
	public static Part createRandom() throws InstantiationException, IllegalAccessException {
		int n = rand.nextInt(list.size());
		Part p = list.get(n).newInstance();
		return p;
	}
	
	private static Random rand = new Random(7);
}

class Filter extends Part{	
}

class FuelFilter extends Filter{	
}

class AirFilter extends Filter{	
}

class Belt extends Part {	
}

class FanBelt extends Belt {	
}

class GeneratorBelt extends Belt {	
}

public class RegisteredFactories {
	public static void main(String[] args) throws InstantiationException, IllegalAccessException {
		for(int i = 0; i < 10; ++i) {
			System.out.println(Part.createRandom());
		}
	}
}

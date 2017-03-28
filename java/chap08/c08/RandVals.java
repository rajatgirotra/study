package c08;

import java.util.*;

public interface RandVals {
	Random rand = new Random();
	int i = rand.nextInt();
	long l = rand.nextLong();
	float f = rand.nextFloat();
	double d = rand.nextDouble();	
}

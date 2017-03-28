/*
 * Please read Sets.java first
 * Should be self explanatory.
 */
import java.util.EnumSet;
import java.util.Set;

public class WatercolorSets {
	public static void  main(String[] args) {
		Set<Watercolors> set1 = EnumSet.range(Watercolors.LEMON_YELLOW,
														Watercolors.PHTHALO_BLUE);
		Set<Watercolors> set2 = EnumSet.range(Watercolors.VIOLET,
											  Watercolors.RAW_UMBER);		
		System.out.println(Sets.union(set1, set2));
		System.out.println(Sets.intersection(set1, set2));
		System.out.println(Sets.difference(set1, set2));
		System.out.println(Sets.complement(set1, set2));		
	}
}

/*
Please read ContainerMethodDifferences.java first
*/
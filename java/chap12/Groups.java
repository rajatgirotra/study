import java.util.regex.Matcher;
import java.util.regex.Pattern;

/*
 * Please read integerMatch.java first.
 */

/*
Groups are regular expressions set off by parentheses that can be called up later with their group number. Group 0 indicates the
whole expression match, group l is the first parenthesized group, etc. Thus in "A(B(C))D"
there are three groups: Group 0 is ABCD, group 1 is BC, and group 2 is C.

The Matcher object has methods to give you information about groups:

public int groupCount()
   returns the number of groups in this matcher’s pattern. Group 0 is not included in this count.


public String group()
   returns group 0 (the entire match) from the previous match operation (find( ), for example)


public String group(int i)
   returns the given group number during the previous match operation. If the match was successful, but the group
   specified failed to match any part of the input string, then null is returned.


public int start(int group)
    returns the start index of the group found in the previous match operation.


public int end(int group)
    returns the index of the last character, plus one, of the group found in the previous match operation.
 */

public class Groups {
	static public final String POEM =
		"Twas brillig, and the slithy toves\n" +
		"Did gyre and gimble in the wabe.\n" +
		"All mimsy were the borogoves,\n" +
		"And the mome raths outgrabe.\n\n" +
		"Beware the Jabberwock, my son,\n" +
		"The jaws that bite, the claws that catch.\n" +
		"Beware the Jubjub bird, and shun\n" +
		"The frumious Bandersnatch.";
	public static void main(String[] args) {
		Matcher m =
			Pattern.compile("(?m)(\\S+)\\s+((\\S+)\\s+(\\S+))$")
			.matcher(POEM);
		while(m.find()) {
			for(int j = 0; j <= m.groupCount(); j++)
				System.out.print("[" + m.group(j) + "]");
			System.out.println();
		}
	}
}

/*
please read Splitting.java next */

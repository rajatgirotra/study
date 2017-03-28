/*
 * Please read Turtle.java first.
 * Using String.format()
 * Java SE5 also took a cue from C’s sprintf( ), which is used to create Strings. String.format( ) is a static method which
 * takes all the same arguments as Formatter’s format( ) but returns a String. It can come in handy when you only need to
 * call format( ) once:
 */

public class DatabaseException extends Exception {
	public DatabaseException(int transactionID, int queryID,
			String message) {
		super(String.format("(t%d, q%d) %s", transactionID,
				queryID, message));
	}
	public static void main(String[] args) {
		try {
			throw new DatabaseException(3, 7, "Write failed");
		} catch(Exception e) {
			System.out.println(e);
		}
	}
}

/* Output:
DatabaseException: (t3, q7) Write failed

please read hex.java next
*/
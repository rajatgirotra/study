/*
Please read ReThrowNew.java first.

Often you want to catch one exception and throw another, but still keep
the information about the originating exception—this is called exception
chaining. Prior to JDK 1.4, programmers had to write their own code to
preserve the original exception information, but now all Throwable
subclasses may take a cause object in their constructor. The cause is
intended to be the originating exception, and by passing it in you
maintain the stack trace back to its origin, even though you’re creating
and throwing a new exception at this point.

It’s interesting to note that the only Throwable subclasses that provide
the cause argument in the constructor are the three fundamental
exception classes Error (used by the JVM to report system errors),
Exception and RuntimeException. If you want to chain any other
exception types, you do it through the initCause( ) method rather than
the constructor.

Here’s an example that allows you to dynamically add fields to a
DynamicFields object at run time:

Actually you'll find this example complex. So please go through ExceptionCause.java first & then return here.
 */

import java.util.*;

class DynamicFieldsException extends Exception { }

public class DynamicFields {
	private Object[][] fields;

	public DynamicFields(int initialiseSize) {
		fields = new Object[initialiseSize][2];
		for(int i = 0; i < fields.length; ++i) {
			fields[i] = new Object[] { null, null };
		}
	}

	public String toString() {
		StringBuffer result = new StringBuffer();
		for(int i = 0; i < fields.length; ++i) {
			result.append(fields[i][0]);
			result.append(": ");
			result.append(fields[i][1]);
			result.append("\n");
		}
		return result.toString();		
	}

	private int hasField(String id) {
		for(int i = 0; i < fields.length; ++i) {
			if(id.equals(fields[i][0]))
				return i;
		}
		return -1;
	}

	private int getFieldNumber(String id) throws NoSuchFieldException {
		int i = hasField(id);
		if(i == -1) {
			throw new NoSuchFieldException();
		}
		return i;
	}

	private int makeField(String id) {
		for(int i = 0; i < fields.length; ++i) {
			if(fields[i][0] == null) {
				fields[i][0] = id;
				return i;
			}
		}
		// No empty fields.. so create one
		Object[][] tmp = new Object[fields.length + 1][2];
		for(int j = 0; j < fields.length; ++j) {
			tmp[j] = fields[j];
		}			
		for(int i = fields.length; i < tmp.length; ++i) {
			tmp[i] = new Object[] {null, null};
		}
		fields = tmp;		
		return makeField(id);
	}

	public Object getField(String id) throws NoSuchFieldException {
		return fields[getFieldNumber(id)][1];
	}

	public Object setField(String id, Object value) throws DynamicFieldsException {
		if(value == null) {
			DynamicFieldsException dfe = new DynamicFieldsException();
			dfe.initCause(new NullPointerException("value == null"));
			throw dfe;
		}
		int fieldNumber = hasField(id);
		if(fieldNumber == -1)
			fieldNumber = makeField(id);

		Object result = null;
		try {
			result = getField(id);
		} catch (NoSuchFieldException e) {
			throw new RuntimeException(e);
		}
		fields[fieldNumber][1] = value;
		return result;
	}
	public static void main(String[] args) {
		DynamicFields df = new DynamicFields(3);
		System.err.println(df);
		try {
			df.setField("d", "A value for d");
			df.setField("number", new Integer(47));
			df.setField("number2", new Integer(48));
			System.err.println(df);
			df.setField("d", "A new value for d");
			df.setField("number3", new Integer(11));
			System.err.println(df);
			System.err.println(df.getField("d"));
			Object field = df.getField("a3"); // Exception
			//df.setField("abcd", null); //Exception
		} catch(NoSuchFieldException e) {
			throw new RuntimeException(e);
		} catch(DynamicFieldsException e) {
			throw new RuntimeException(e);
		}
	}
}

/*
Please read NarrowException.java next
*/
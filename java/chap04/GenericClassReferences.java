/*
Please read ClassInitialization.java first.
*/

/*
A Class reference points to a Class object for any java class that you might create. The Class object holds the method code for that class and also manufactures new instances of the that class and also stores the static members of the that class.

You can make a generic class reference as shown below:
*/

public class GenericClassReferences {
	public static void main(String[] args) {
		Class c = int.class;
		Class<Integer> intClass = Integer.class;
		c = double.class ; //allowed
		intClass = double.class; //not allowed
		
		//You might think that the following should be allowed as int derives from Number.
		Class<Number> numberClass = int.class;
		//But it is not allowed because int.class does not inherit from Number.class :-)
		//If you wan to do this you can use the JAVA wildcard ? as shown below:
		Class<? extends Number> bounded = int.class;
		bounded = double.class; //this is also OK now.

		//You should now ideally use Class<?> instead of using plain Class, although there is no
		//difference. This tells someone reading your code that the Class reference you created is meant to point to
		//any Class object that you wish.
	
		//Class generics just provides a stricter type checking and is evaluated at compile time.
	}
}

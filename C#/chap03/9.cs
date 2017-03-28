//Anonymous types in C#
using System;
namespace Wrox.ProCSharp.chap03
{
   class MainEntryPoint
   {
      public static void Main(String[] args)
      {
         var captain = new {FirstName="Mahendra", MiddleName = "Singh", LastName = "Dhoni"};
         //var doctor  = new {Name="K.L. Sethi", Hospital = "Sir Ganga Ram", Specialist = "Heart"};
         var doctor  = new {FirstName="K.", MiddleName = "L. ", Lastname = "Sethi"};

         Type captainType = captain.GetType();
         Type doctorType = doctor.GetType();
         Console.WriteLine("captain is a " + captainType.ToString());
         Console.WriteLine("doctor is a " + doctorType.ToString());
 
         Console.WriteLine(captain.FirstName);

         captain = doctor;
        
         Console.WriteLine(captain.FirstName + captain.MiddleName + captain.LastName);
         
         return;
      }
   }
}

/*
Chapter 2 discussed the var keyword in reference to implicitly typed variables. When used with the
new keyword, anonymous types can be created. An anonymous type is simply a nameless class
that inherits from object . The definition of the class is inferred from the initializer, just like in
implicitly typed variables.
If you needed an object that contained a person  s first, middle, and last name the declaration would look
like this:

var captain = new {FirstName = James, MiddleName = T, LastName = Kirk};

This would produce an object with FirstName , MiddleName , and LastName properties. If you were to
create another object that looked like this:

var doctor = new {FirstName = Leonard, MiddleName = , LastName = McCoy};

The types of captain and doctor are the same. You could set captain = doctor , for example

If the values that are being set come from another object, then the initializer can be abbreviated. If you
already have a class that contains the properties FirstName , MiddleName , and LastName and you have
an instance of that class with the instance name person , then the captain object could be initialized
like this:

var captain = new (person.FirstName, person.MidleName, person.LastName};

The property names from the person object would be projected to the new object named captain . So
the object named captain would have the FirstName , MiddleName , and LastName properties.
The actual type name of these new objects is unknown. The compiler  makes up  a name for the type,
but only the compiler will ever be able to make use of it. So you can  t and shouldn  t plan on using any
type reflection on the new objects because you will not get consistent results.
*/

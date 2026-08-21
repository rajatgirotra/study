Languages like Java, Python, C# support reflections from very early on. reflection means inspecting entities like classes, namespaces,
 functions, variables etc for their metadata (either at compile time or runtime). However, C++ never supported reflection. It does now with C++26
 but only at compile time, because of its commitment to zero-cost abstractions. Runtime reflection requires storing metadata about every
type, which adds memory overhead and initialization cost.

Static reflection in C++26 provides:
=====================================
• Introspection of types, members, functions, enumerators, and names-
paces
• Querying type properties (is_class, is_function, access specifiers, etc.)
• Access to member names as compile-time strings
• Generation of new types from reflection information
• Integration with constexpr for compile-time code generation

The mental model
================
Reflection in C++26 is purely compile-time. There is no runtime type database like Java or C#. Instead you get two new core-language operators plus a library
 of consteval functions, and the whole thing works as a loop:
  a) reflect a program entity into a value,
  b) query/manipulate that value during constant evaluation,
  c) then splice the result back into real code that the compiler continues to compile.

Two operators are the whole foundation:
=======================================
^^ — the reflection operator (cat-ears operator) - ^^int, ^^my_var, ^^SomeClass, ^^some_namespace each yield a value of type std::meta::info.
This is an opaque handle to "an entity in the program." It's a consteval prvalue — it only exists during constant evaluation.

[: r :] — the splice. Takes an std::meta::info back to a grammatical construct: a type, an expression, a template argument, a member name.
 This is how reflection results re-enter normal code. Once you have a reflection object, you use metafunctions to query information
about it. Metafunctions are consteval functions in the std::meta namespace that take std::meta::info objects and produce results at compile time.

std::meta::info (in <meta>, namespace std::meta) is a regular "structural" type (can be used as a NTTP), so you can put it in constexpr variables,
 std::vector<info>, pass it to consteval functions, compare it, etc. — but all of that only during constant evaluation.

 Lets see it in action
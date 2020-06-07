/*
This is an abstract from Herb Shutter's Virtuality topic.
Question: When should you virtual functions be really public, protected, or private.
The answer is rarely if never, sometimes, by default. Dont be surprised. There is a reason for this.

Guideline #1: Prefer to make interfaces nonvirtual, using Template Method.

Traditionally, many programmers were used to writing base classes using public virtual functions to directly and simultaneously specify both the interface and the customizable behavior. For example, we might write:


// Example 1: A traditional base class.
//
class Widget
{
public:
  // Each of these functions might optionally be
  // pure virtual, and if so might or might not have
  // an implementation in Widget; see Item 27 in [1].
  //
  virtual int Process( Gadget& );
  virtual bool IsDone();
  // ...
};

The problem here is that the virtual function is doing two jobs: It's specifying interface because it's public and therefore directly part of the interface Widget presents to the rest of the world; and it's specifying implementation detail, namely the internally customizable behavior, because it's virtual and therefore provides a hook for derived classes to replace the base implementation of that function (if any). That a public virtual function inherently has two significantly different jobs is a sign that it's not separating concerns well and that we should consider a different approach.

What if we want to separate the specification of interface from the specification of the implementation's customizable behavior? Then we end up with something that should remind us strongly of the Template Method pattern, as shown in the example below:

// Example 2: A more modern base class, using
// Template Method to separate interface from
// internals.
//
class Widget
{
public:
  // Stable, nonvirtual interface.
  //
  int Process( Gadget& ); // uses DoProcess...()
  bool IsDone(); // uses DoIsDone()
  // ...

private:
  // Customization is an implementation detail that may
  // or may not directly correspond to the interface.
  // Each of these functions might optionally be
  // pure virtual, and if so might or might not have
  // an implementation in Widget; see Item 27 in [1].
  //
  virtual int DoProcessPhase1( Gadget& );
  virtual int DoProcessPhase2( Gadget& );
  virtual bool DoIsDone();
  // ...
};

Prefer to use Template Method to make the interface stable and nonvirtual, while delegating customizable work to nonpublic virtual functions that are responsible for implementing the customizable behavior. After all, virtual functions are designed to let derived classes customize behavior; it's better to not let publicly derived classes also customize the inherited interface, which is supposed to be consistent.

The Template Method approach has several benefits and no significant drawbacks.

The above is a good design because:

1] The base class is now in full control of its interface and policy.

2] Since we've better separted interface and implementation, it is a better design. 

Guideline #2: Prefer to make virtual functions private.

That's easy. This lets the derived classes override the function to customize the behavior as needed, without further exposing the virtual functions directly by making them callable by derived classes (as would be possible if the functions were just protected). The point is that virtual functions exist to allow customization; unless they also need to be invoked directly from within derived classes' code, there's no need to ever make them anything but private.


Guideline #3: Only if derived classes need to invoke the base implementation of a virtual function, make the virtual function protected.
This is understandable and trivial.


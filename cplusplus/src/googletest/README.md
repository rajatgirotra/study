# Google Test and Google Mock (gMock)

Google Test and Google Mock are Google's open-source unit test libraries. Google Test provides support for writing tests and assertions. Google Mock is used for mocking APIs around your SUT (System Under Test).

## Google Mock

There is a difference between a *mock* and a *fake* object:

- A **fake** object is a dummy implementation of the actual APIs. It may not do what a true API would do, but it will have a similar interface and may return dummy values and objects to aid your unit testing.
- A **mock** object allows you to set expectations on it, like how many times an API is called, what it returns on various invocations, or whether it throws an exception.

## How to Create a Mock

If your API uses polymorphism, the best way to inject your mock is by creating a mock object that inherits from the base class and implements the virtual methods. Then, for each virtual method you can define expectations inside your test cases.

Example: define a mock for a `Turtle` base class.

```cpp
class MockTurtle : public Turtle {
public:
  // General syntax:
  // MOCK_METHOD(RETURN_TYPE, FUNCTION_NAME, (ARGUMENTS), (QUALIFIERS));

  MOCK_METHOD(void, PenUp, (), (override));
  MOCK_METHOD(void, PenDown, (), (override));
  MOCK_METHOD(void, Forward, (int distance), (override));
  MOCK_METHOD(void, Turn, (int degrees), (override));
  MOCK_METHOD(void, GoTo, (int x, int y), (override));
  MOCK_METHOD(int, GetX, (), (const, override));
  MOCK_METHOD(int, GetY, (), (const, override));
};
```

If your mock types have commas like `std::pair`, `std::tuple`, or `std::variant`, use this trick:

```cpp
class MockFoo {
public:
  using BoolAndInt = std::pair<bool, int>;
  MOCK_METHOD(BoolAndInt, GetPair, ());

  using MapIntDouble = std::map<int, double>;
  MOCK_METHOD(bool, CheckMap, (MapIntDouble, bool));
};
```

## Setting Expectations

General syntax:

```cpp
EXPECT_CALL(mock_object, method(matchers))
    .Times(cardinality)
    .WillOnce(action)
    .WillRepeatedly(action);
```

gMock requires expectations to be set **before** the mock functions are called, otherwise the behavior is undefined. Do not alternate between calls to `EXPECT_CALL()` and calls to the mock functions, and do not set any expectations on a mock after passing the mock to an API.

### Matchers

Often when you write a mock expectation, you do not want to tie it to specific values. Otherwise your tests become too brittle. A good alternative is to specify matchers like `Gt(100)` or `::testing::_` (underscore) when you do not care about the argument.

Common matchers in `::testing`:

- `Eq(value)`
- `Ge(value)`
- `Gt(value)`
- `Le(value)`
- `Lt(value)`
- `Ne(value)`
- `IsFalse()` (argument evaluates to false)
- `IsTrue()` (argument evaluates to true)
- `DistanceFrom(target, m)` (meaning `Abs(argument - target)` matches `m`)
- `DistanceFrom(target, get_distance, m)` (where `get_distance(argument - target)` matches `m`)
- `IsNull()` (argument evaluates to `nullptr_t`)
- `NotNull()` (argument evaluates to `nullptr_t`)
- `Optional(m)` (argument is `std::optional<>` containing a value matching `m`)
- `VariantWith<T>(m)` (argument is `std::variant` holding alternative type `T` with value matching `m`)
- `AnyWith<T>(m)` (argument is `std::any<T>` with value matching `m`)
- `Ref(variable)` (argument is a reference to `variable`)
- `TypedEq<type>(value)` (argument has type `type` and value `value`)
- `_` (argument can be anything)
- `A<Type>` / `An<Type>` (argument can be any value of type `Type`)

gMock will try to copy the value when building expectations. If the type of `value` is not copyable, use `std::ref()`.

Example:

```cpp
EXPECT_CALL(foo, Bar(Eq(std::ref(non_copyable_value))));
```

Floating-point matchers:

- `DoubleEq(value)`
- `FloatEq(value)`
- `NanSensitiveDoubleEq(value)`
- `IsNaN()`

With max absolute error:

- `DoubleNear(a_double, max_abs_error)`
- `FloatNear(a_double, max_abs_error)`
- `NanSensitiveDoubleNear(a_double, max_abs_error)`

### Exception Matchers

Simple way to check a function throws an exception is:
`EXPECT_THROW(statement, exception_type)`

These matchers below apply to callables that throw:

- `Throws<E>()` — callable throws `E`
- `Throws<E>(m)` — callable throws `E` matching matcher `m`
- `ThrowsMessage<E>(m)` — callable throws `E` with message matching `m`

The throwing matchers specifically require a callable as "actual": `EXPECT_THAT(actual, matcher)`

Example:

The general usage format is:
```cpp
auto argument = [] { throw std::runtime_error("error msg"); };

EXPECT_THAT(argument, Throws<std::runtime_error>());
EXPECT_THAT(argument, Throws<std::runtime_error>(
    Property(&std::runtime_error::what, Eq("error msg"))));
EXPECT_THAT(argument, ThrowsMessage<std::runtime_error>(HasSubstr("msg")));
```

Remember:

| Macro | Arg 1 | Arg 2 | Order enforced? |
|---|---|---|---|
| `EXPECT_EQ` | value | value | No (symmetric) |
| `EXPECT_THROW` | statement | type | Yes |
| `EXPECT_THAT` | actual value | matcher | Yes |
| `EXPECT_THAT` + `Throws`/`ThrowsMessage` | callable | matcher | Yes |

## Cardinality

Cardinality is optional. If you skip it, gMock uses a reasonable default.

Rules:

- If neither `WillOnce()` nor `WillRepeatedly()` is in the `EXPECT_CALL()`, the inferred cardinality is `Times(1)`.
- If there are `n` `WillOnce()` calls and no `WillRepeatedly()`, the cardinality is `Times(n)`.
- If there are `n` `WillOnce()` calls and one `WillRepeatedly()`, the cardinality is `Times(AtLeast(n))`.

Examples of cardinalities:

- `Times(n)`
- `AtLeast(n)`
- `AnyNumber()`
- `AtMost(n)`
- `Between(m, n)`
- `Exactly(n)`

## Actions

What should happen when a mock function is called is decided by an action. The default actions for built-in types and pointer types return the default value for that type (e.g., `0` for integral, `false` for bool, `nullptr` for pointer). If a user-defined type is default-constructible, the default-constructed value is used.

You can always override the default action by specifying `WillOnce()` and `WillRepeatedly()`.

Example:

```cpp
EXPECT_CALL(turtle, GetX())
    .WillOnce(Return(100))
    .WillOnce(Return(200))
    .WillOnce(Return(300));
```

Your actions should not have side effects, as the `EXPECT_CALL` is evaluated once, and side effects will not behave as you expect.

### Possible Actions

- `Return(x)` — returns an object of some type. The value `x` is copied in the expectation.
- `ReturnRef(variable)` — returns a reference (use when the mock method returns `SomeType&`).
- `ReturnPointee(&x)` — returns the value pointed to by a pointer.
- `DoAll(action1, action2, ..., actionN)` — runs multiple actions; the last action’s return value is used.

Example of returning a pointer value:

```cpp
int x = 0;
MockFoo foo;
EXPECT_CALL(foo, GetValue()).WillRepeatedly(ReturnPointee(&x));

x = 42;
EXPECT_EQ(foo.GetValue(), 42); // passes
```

Example of running multiple actions:

```cpp
EXPECT_CALL(foo, Bar(_)).WillOnce(DoAll(action_1, action_2, action_n));
```

## Multiple Expectations and Order of Calls

By default, when a mock method is invoked, gMock searches expectations in reverse order of setup.

```cpp
using ::testing::_;

EXPECT_CALL(turtle, Forward(_));         // #1
EXPECT_CALL(turtle, Forward(10)).Times(2); // #2
```

If `Forward(10)` is called three times in a row, the third time it will error because expectation #2 is saturated. If the third call is `Forward(20)`, it will match #1 and be OK. You can change this behavior by removing saturated expectations once they are met.

```cpp
EXPECT_CALL(turtle, Forward(10))
    .Times(2)
    .RetiresOnSaturation();
```

To enforce call order, use `::testing::InSequence`:

```cpp
using ::testing::InSequence;

TEST(FooTest, DrawsLineSegment) {
  InSequence seq;
  EXPECT_CALL(turtle, PenDown());
  EXPECT_CALL(turtle, Forward(100));
  EXPECT_CALL(turtle, PenUp());

  Foo();
}
```

InSequence puts all enclosed expectations into one chain — a total order. When you need something more nuanced — say A must precede both B and C, but B and C are unordered relative to each other — InSequence is too strong. For that you use named Sequence objects with the .InSequence(seq1, seq2) clause on individual expectations, which lets you express a partial order (a DAG).

```cpp
using ::testing::Sequence;

TEST(FooTest, ForkOrdering) {
  Sequence s1, s2;

  EXPECT_CALL(m, A())
      .InSequence(s1, s2);   // A belongs to both chains

  EXPECT_CALL(m, B())
      .InSequence(s1);       // s1:  A → B

  EXPECT_CALL(m, C())
      .InSequence(s2);       // s2:  A → C

  Foo();
}
```

## Nice, Strict, and Naggy Mocks

By default all mocks are **naggy**: if you don't set an expectation and the mock is called, gMock logs a warning.

- **Strict** mock: unexpected calls are errors.
- **Nice** mock: unexpected calls are ignored.

Example:

```cpp
using ::testing::NiceMock;

TEST(...) {
  NiceMock<MockFoo> mock_foo;
  EXPECT_CALL(mock_foo, DoThis());
  // ... code that uses mock_foo ...
}
```

## Overriding Default Action

To override the default action:

```cpp
ON_CALL(mockObject, mockFunction(matchers)).WillByDefault(defaultAction);
```
The core difference: `ON_CALL` sets behavior; `EXPECT_CALL` sets behavior and an assertion.

`ON_CALL` says "if this method gets called, here's what it should do." It does not require the call to happen, and it never fails your test on its own. It only configures a default return/action.

Recall the resolution order when a value-returning method is called:

- Matching EXPECT_CALL with an action → use it
- Else ON_CALL default (WillByDefault) → use it
- Else the method's default action → for a method returning T, that means `return DefaultValue<T>::Get()`
DefaultValue<T> customizes step 3. It's global, keyed purely by return type T, and completely independent of any particular mock object or method.

Methods on DefaultValue are:
```cpp
using ::testing::DefaultValue;

DefaultValue<int>::Set(42);      // fixed value; T must be copyable
DefaultValue<int>::IsSet();      // → true
DefaultValue<int>::Get();        // → 42  (what the default action calls)
DefaultValue<int>::Clear();      // remove the override, restore built-in default
```

```cpp
/*
SetFactory is the variant for when you can't hand over a copyable fixed value — most importantly move-only types, where a fresh
 instance must be produced per call: if your object is complex, you can use `::testing::DefaultValue<T>`:
*/
DefaultValue<std::unique_ptr<Buzz>>::SetFactory([] {
  return std::make_unique<Buzz>(AccessLevel::kInternal);
}); // return a callable to manufacture a new object each time it is called.

ON_CALL(mock, GetHandle()).WillByDefault(DoDefault());  // → returns DefaultValue<Handle>::Get()

DefaultValue<std::unique_ptr<Buzz>>::Clear();
```
`DefaultValue<T>` is a global mutable state with no scoping. A Set in one test leaks into every subsequent test in the binary until something calls Clear(). Always pair them, and make the cleanup exception-safe — a fixture's SetUp/TearDown, or a small RAII guard:

```cpp
struct HandleDefault {
  HandleDefault()  { DefaultValue<Handle>::Set(Handle::Invalid()); }
  ~HandleDefault() { DefaultValue<Handle>::Clear(); }
};
```

## Verifying and Resetting the Mock

gmock provides static methods on Mock that let you take manual control of things gmock normally does automatically at destruction. Two are about verification timing; the third is about leak detection. The main use is phase boundaries: a long-lived mock used across distinct stages of a test, where you want to check "phase 1's calls happened" before setting up phase 2.
gMock verifies expectations when a mock object is destructed, but you can do it earlier:


```cpp
using ::testing::Mock;

Mock::VerifyAndClearExpectations(&mock_obj); // verifies expectations right away (errors are immediately reported) and clears expectations after it is done. return boolean.
Mock::VerifyAndClear(&mock_obj); // same as above, but also additionally clears the ON_CALL defaults also.
```

If you want to allow a mock object to leak (and skip verification), use:

```cpp
Mock::AllowLeak(&mock_obj);
```

## Checkpoints

Use `MockFunction<>` as checkpoints to verify which calls occur when. A checkpoint injects a known landmark into the sequence whose real-time position you control, so the SUT's calls get pinned to the correct side of it. `MockFunction<F>` is just a tiny prebuilt mock class with one mocked method, `Call`, whose signature comes from `F`. So `MockFunction<void(std::string)>` gives you a mock with `void Call(std::string)`.

```cpp
using ::testing::MockFunction;

TEST(FooTest, InvokesBarCorrectly) {
  MyMock mock;
  MockFunction<void(std::string)> checkpoint;

/* 
By putting EXPECT_CALL(checkpoint, Call("1")) into the same InSequence as the real expectations, you assert the SUT's calls land before/after that landmark.
example: First Bar("a") before Call("1") → it must occur during Foo(1) at (A). If Foo(1) didn't call Bar("a"), then when the driver reaches
 checkpoint.Call("1"), the sequence still expects Bar("a") first → failure.
 */
  {
    InSequence seq;
    EXPECT_CALL(mock, Bar("a"));
    EXPECT_CALL(checkpoint, Call("1"));
    EXPECT_CALL(checkpoint, Call("2"));
    EXPECT_CALL(mock, Bar("a"));
  }

  Foo(1);
  checkpoint.Call("1");
  Foo(2);
  checkpoint.Call("2");
  Foo(3);
}
```

`MockFunction<R(T1, ..., Tn)>` has a mock method `Call()` and a helper `AsStdFunction()`:

```cpp
R Call(T1, ..., Tn);
std::function<R(T1, ..., Tn)> AsStdFunction();
```
## AsStdFunction
Sometimes the thing you want to test is: "does the code correctly call the callback I gave it?" But a callback is usually a std::function, and you can't set gmock expectations on a plain std::function — expectations only work on mock objects. So you're stuck between two things that don't fit together:
- gmock expectations need a mock object
- the code under test wants a std::function

What `AsStdFunction()` does?
----------------------------
It bridges exactly that gap. MockFunction is the mock object (so you can set expectations on its Call method), and AsStdFunction() gives you a std::function wrapper around it that you can pass into the code. When the code invokes the std::function, that call flows straight through to the mock's Call — so your expectation sees it. One object, two faces:

cb — the mock face, for setting expectations
cb.AsStdFunction() — the std::function face, for passing in. See example below:

```cpp
void RetryTwice(const std::function<void()>& on_retry) {
  on_retry();
  on_retry();
}
MockFunction<void()> cb;
EXPECT_CALL(cb, Call()).Times(2);      // expectation on the mock face
RetryTwice(cb.AsStdFunction());        // pass the std::function face
```
So, AsStdFunction() lets you take a gmock mock and pass it somewhere that expects a std::function, so you can put expectations on a callback. That's the whole idea — it has nothing to do with sequencing or checkpoints; it just happens to live on the same MockFunction helper.

## References

When you want to look up details, search for:

- Matchers Reference
- Actions Reference
- Cardinality Reference


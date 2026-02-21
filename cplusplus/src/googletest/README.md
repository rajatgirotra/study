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

These matchers apply to callables that throw:

- `Throws<E>()` — callable throws `E`
- `Throws<E>(m)` — callable throws `E` matching matcher `m`
- `ThrowsMessage<E>(m)` — callable throws `E` with message matching `m`

Example:

```cpp
auto argument = [] { throw std::runtime_error("error msg"); };

EXPECT_THAT(argument, Throws<std::runtime_error>());
EXPECT_THAT(argument, Throws<std::runtime_error>(
    Property(&std::runtime_error::what, Eq("error msg"))));
EXPECT_THAT(argument, ThrowsMessage<std::runtime_error>(HasSubstr("msg")));
```

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

If your object is complex but copy-constructible and trivially destructible, you can use `::testing::DefaultValue<T>`:

```cpp
DefaultValue<std::unique_ptr<Buzz>>::SetFactory([] {
  return std::make_unique<Buzz>(AccessLevel::kInternal);
});

DefaultValue<std::unique_ptr<Buzz>>::Clear();
```

Other options:

- `DefaultValue<T>::Set(value);` — sets a default value for type `T`.
- `DefaultValue<T>::Clear();` — clears the default.

## Verifying and Resetting the Mock

gMock verifies expectations when a mock object is destructed, but you can do it earlier:

```cpp
using ::testing::Mock;

Mock::VerifyAndClearExpectations(&mock_obj);
Mock::VerifyAndClear(&mock_obj);
```

If you want to allow a mock object to leak (and skip verification), use:

```cpp
Mock::AllowLeak(&mock_obj);
```

## Checkpoints

Use `MockFunction<>` as checkpoints to verify which calls occur when.

```cpp
using ::testing::MockFunction;

TEST(FooTest, InvokesBarCorrectly) {
  MyMock mock;
  MockFunction<void(std::string)> checkpoint;

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

## References

When you want to look up details, search for:

- Matchers Reference
- Actions Reference
- Cardinality Reference


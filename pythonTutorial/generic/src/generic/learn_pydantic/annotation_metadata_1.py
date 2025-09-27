# Python supports annotations which are just extra information/metadata about variables/functions/classes etc.
# These annotations are not used and enforced by the python interpreter. It is used by external tools like type checkers, linters, IDE's etc.
# a very common type of annotation is "type hints". The typing module provides runtime support for type hints. It provides a vocabulary of more advanced type hints.

from typing import List, Optional, Dict, Any, Annotated, TypeAlias, NewType
from collections.abc import Callable, Awaitable # for type hints for Callable functions and Awaitable functions
from collections.abc import Sequence, Mapping
from dataclasses import dataclass

# example of type hint
def surface_area_of_cube(edge_length: float) -> str:
    return f"The surface area of the cube is {6 * edge_length ** 2}."

print(f'surface_area_of_cube annotations: {surface_area_of_cube.__annotations__}')


# type alias. Type aliases are useful for simplifying complex type signatures.
type Vector = list[float] # syntax is supported in python 3.12 onwards
Vector: TypeAlias = list[float] # syntax before python 3.12

def scale(scalar: float, vector: Vector) -> Vector:
    return [scalar * num for num in vector]
# passes type checking; a list of floats qualifies as a Vector.
new_vector = scale(2.0, [1.0, -4.2, 5.4])
print(f'scale annotations: {scale.__annotations__}')

# you can also create new types using NewType
# more like typedef of C++ world.
UserId = NewType('UserId', int) # UserId will be nothing but an int.
# Behind the scene, UserId is just a callable which when passed an argument, returns the type of that argument
# so at runtime, UserId(524313) just returns an int with value 524313
some_id = UserId(524313)

def try_it(func: Callable[[int, float], str]) -> None:
    try:
        return func(10, 25.5)
    except Exception as e:
        print(e)

def foo(number: int, value: float) -> str:
    return str(number + value)

print(try_it(foo))

# how would give type hint for a function which can take a homogenous list of more than one types? may a list of str or list of ints?
def return_first_element[T](seq: Sequence[T]) -> T:
    return seq[1]

print(return_first_element([10, 20, 30]))
print(return_first_element(["Hello", "World", "Goodbye"]))

z: Mapping[str, str | int] = {} # z is a dict like type of key as str type and value as str or int type.

# Union type; Union[X, Y] is equivalent to X | Y and means either X or Y.
# Optional[X] is equivalent to X | None

# typing.Annotated is used to add metadata x to a given type T by using the annotation Annotated[T, x].
# Metadata added using Annotated can be used by static analysis tools or at runtime. At runtime, the metadata is stored in a __metadata__ attribute.
# syntax is: Annotated[<type>, <metadata>]
# The responsibility of how to interpret the metadata lies with the tool or library encountering an Annotated annotation.
# A tool or library encountering an Annotated type can scan through the metadata elements to determine if they are of interest
@dataclass
class ValueRange:
    lo: int
    hi: int

T1 = Annotated[int, ValueRange(-10, 5)]
T2 = Annotated[T1, ValueRange(-20, 3)]
print(f'T1 metadata: {T1.__metadata__}, type(metadata): {type(T1.__metadata__)}, T1 original type is: {T1.__origin__}')

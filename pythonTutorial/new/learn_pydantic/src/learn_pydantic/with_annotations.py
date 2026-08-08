# annotations are part of standard library (typing). it's general usage is in the form
# Annotated[SomeType, metadata1, metadata2, metadata3, ...]
# Most of the python tools like static code checkers will ignore this metadata. Annotated[int, "anything"] is just int for them.
# but pydantic uses to look at these metadata and act accordingly. So Annotated is a way to attach validation
# rules directly to a type instead of putting them in Field(...) or a separate validator.

from typing import Annotated, Any
from pydantic import BaseModel, Field, AfterValidator, BeforeValidator
import math
from dataclasses import dataclass

class Product(BaseModel):
    name: Annotated[str, Field(min_length=1, max_length=100)] = "Raj"
    price_1: Annotated[float, Field(gt=0)] = 10.10
    quantity: Annotated[int, Field(ge=0)] = 500
    price_2: float = Field(gt=0) # how to define a default value?
    
    
# print(Product().model_dump()) # error!! field price_2 required. But see in price_1, the restrictions on the fields move inside the Annotation.

# the most important use of Annotation is that it allows you to define reusable fields which can be used in multiple model classes.

Latitude = Annotated[float, Field(ge=-90, le=90)]
Longitude = Annotated[float, Field(ge=-180, le=180)]
PositiveInt = Annotated[int, Field(gt=0)]

class Location(BaseModel):
    lat: Latitude
    lon: Longitude

class Order(BaseModel):
    pickup: Location
    dropoff: Location
    seats: PositiveInt
    
# if your Annotated Field validation is not trivial, you could add that validation separately using AfterValidator and BeforeValidator

def must_be_even(v: int) -> int:
    if v % 2 != 0:
        raise ValueError("must be even")
    return v

def round_to_next_int(v: Any) -> int:
    try:
        if isinstance(v, (str)):
            v = float(v.strip())
        return math.ceil(v)
    except (ValueError, TypeError):
        raise ValueError(f"cannot convert {v!r} to a rounded integer")

EvenInt = Annotated[int, BeforeValidator(round_to_next_int), AfterValidator(must_be_even)] # AfterValidator runs after coercion.

class Config(BaseModel):
    workers: EvenInt

print(Config.model_validate({"workers": "3.3"}).model_dump())

# See below a cool way to have your own special logic in the validators.

def in_range(lo: float, hi: float):
    def validator(v: float) -> float:          # ← signature Pydantic expects
        if not (lo <= v <= hi):                # lo, hi captured from enclosing scope
            raise ValueError(f"{v} not in [{lo}, {hi}]")
        return v
    return AfterValidator(validator)

# OR

@dataclass
class InRange:
    lo: float
    hi: float
    
    def __call__(self, v: float) -> float:
        if not (self.lo <= v <= self.hi):
            raise ValueError(f"{v} not in [{self.lo}, {self.hi}]")
        return v


class Location2(BaseModel):
    lat: Annotated[float, in_range(-90, 90)] # remember AfterValidator function will take just your field, we we need to wrap it in an outer factory class
    lon: Annotated[float, InRange(-180, 180)]
    
    
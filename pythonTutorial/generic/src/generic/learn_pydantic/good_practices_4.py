# pydantic by default coerces/converts input arguments to the destination types.
# this happens even for sequences. pydantic can convert an input tuple to a list if your destination type is list
# for this reason, pydantic recommends to use exact types and not abstract types in destination (eg. use list[int] in place of Sequence from collections.abc

from pydantic import BaseModel, ConfigDict


class Model(BaseModel):
    a: int
    b: float
    c: str

    # model_config = ConfigDict(strict=True) # strict will ensure no coercions are performed.

print(Model(a=3.000, b='2.72', c=b'binary data').model_dump())

# ConfigDict() is really rich and allows multiple ways to handle your BaseModel parsing (like handling unknown arguments, conversions, string lengths etc)
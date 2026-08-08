# Serialization control. model_dump() gives a dict, model_dump_json() a JSON string.
# Useful knobs: exclude_none=True, exclude={"password"}, by_alias=True. Aliases for when the wire format differs from your Python names:
    
from pydantic import BaseModel, ConfigDict, Field, AliasGenerator
from typing import Annotated


class Payload(BaseModel):
    user_id: int = Field(alias="userId")
    
    model_config = ConfigDict(
      validate_by_alias = True, # accept alias name on input
      validate_by_name = True # accept the real name on input too
    )


# Input
print(Payload.model_validate({"userId": 42}))   # accepts camelCase input
print(Payload.model_validate({"user_id": 100}))   # accepts regular input


# Output
print(Payload.model_validate({"userId": 100}).model_dump(by_alias=False)) 
print(Payload.model_validate({"user_id": 100}).model_dump(by_alias=True)) 


# serialization_alias only applies to model_dump() (not on input)
class User(BaseModel):
    name: Annotated[str, Field(serialization_alias="NAME")]
    age: Annotated[int, Field(serialization_alias="AGE")]

u = User(name="Rajat", age=40)
print(u.model_dump(by_alias=True))   # {'NAME': 'Rajat', 'AGE': 40}

# You could also use the "alias_generator = lambda field_name: return field_name" configDict option to rename
# the input/output field names as you prefer

# you could also use the provided AliasGenerator function for more fine grained control on input and output separately.
class Record(BaseModel):
    model_config = ConfigDict(
        alias_generator=AliasGenerator(
            validation_alias=str.lower,       # what's accepted on input
            serialization_alias=str.upper,   # what's emitted on dump
        )
    )
    user_name: str
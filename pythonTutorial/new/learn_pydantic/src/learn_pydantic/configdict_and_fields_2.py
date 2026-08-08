# every BaseModel class should explicitly define a ConfigDict which shows you the overall behavior of your Model class.
# we can also have individual field validators decorators, or we could define defaults for fields at the time of declaration.

from pydantic import BaseModel, ConfigDict, field_validator, Field, computed_field, model_validator
import enum
from typing import Optional


class RectangleConfig(BaseModel):
    length: float
    breadth: float
    
    @computed_field
    @property
    def area(self) -> float:
        return self.length * self.breadth
    
    @model_validator(mode="after")
    def printer(self):
        print(self.area) # note that computed_field is run before the "after" validator
        

class AccountConfig(BaseModel):
    email: str

    @field_validator("email")
    @classmethod
    def lowercase(cls, v: str) -> str:
        return v.lower()
    

class ColorEnum(enum.Enum):
    RED = 'red'
    GREEN = 'green'
    BLUE = 'blue'
    
class MainConfig(BaseModel):
    rectangle: RectangleConfig
    account: AccountConfig
    color: Optional[ColorEnum] = Field(default=ColorEnum.GREEN)
    
    # there are many more options. Here I only show you a few. Refer to the ConfigDict class to see all possible options.
    model_config = ConfigDict(
        frozen=True,            # immutable + hashable
        extra="forbid",         # reject unknown keys instead of ignoring
        str_strip_whitespace=True,  # strip leading and trailing whitespace for str types.
        from_attributes=True,   # allow ORM objects / attribute access
        validate_default = True, # validate default values for fields.
        use_enum_values = True, # serailize enum values to enum string instead of integer value.
        strict = False, # coersion is turned ON, i.e. allow "3" to be coerced to integer 3.
    )
    
    
def main():
    cfg_dict = {"rectangle": {"length": 2, "breadth": 2}, "account": {"email": "ABC@aBc.CoM"}}
    
    cfg = MainConfig.model_validate(cfg_dict)
    print(cfg.model_dump())
    
    print(RectangleConfig(length=5.2, breadth=2).model_dump())
    

if __name__ == "__main__":
    main()

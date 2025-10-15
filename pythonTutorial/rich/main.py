from builtins import ValueError
from typing import Any
from pydantic import BaseModel, Field, validator, EmailStr, field_validator
from typing import Optional, Annotated
import pydantic
import yaml

#Use Email validator (inbuilt)
#USe custom validator
# Use validator using FIelds
# make error msg descriptive
# Json seriliazation and Yaml serialization and store yaml
# Use Field(frozen=True, default, strict)
# Annotated

from pydantic import BaseModel, EmailStr, Field


class User(BaseModel):
    email: EmailStr
    username: str|None = None

    @field_validator("username")
    def default_username(cls, v, user):
        print('Reaching A')
        if v is None:
            print('Reaching C')
            return user.data['enail']
        print('Reaching B')
        return v


user = User(email='user@example.com')
print(user.username)
#> user@example.com


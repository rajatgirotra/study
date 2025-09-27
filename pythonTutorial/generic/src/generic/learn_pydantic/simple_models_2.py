# prefer pydantic over dataclasses mostly as pydantic can validate your input data.
# Just derive from BaseModel to create your model.

from pydantic import BaseModel, Field, ConfigDict, ValidationError
import logging

logger = logging.getLogger(__name__)

class User(BaseModel):
    id: int # by default a value is required.
    name: str = 'John Doe' # default is 'John Doe'

    # ConfigDict() is a TypedDict to configure various parsing and configuration of your model
    model_config = ConfigDict(str_max_length=10, # max length of str fields.
                              extra='ignore') # ignore extra information

user = User(id=10, unknown_attribute='unknown_value') # no error as extra arguments are ignored.
print(user.id) # just access attributes simply.
print(user.name)
print(user.model_dump()) # print as dict

try:
    User.model_validate(user) # this should fail if our model fails any validation
except ValidationError as e:
    logger.exception(e)

user = User.model_construct(id=25)
print(f'user constructed with model_construct: {user}')

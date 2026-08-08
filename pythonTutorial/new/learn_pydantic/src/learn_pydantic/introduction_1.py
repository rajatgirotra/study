# pydantic is very trivial module to handle parsing, validating, and serializing config related data.
# we will use it to parse yaml files.

# the easiest way to learn pydantic is to understand its validation pipeline model.

# 1. raw_input is fed into the "before" model_validator. 
# 2. the data is then goes throught coersion + field by field validation. 
#    coercion is where pydantic will convert the data into the correct declared field type. Example string "3" is coersed to int 3.
# 3. the data then goes through the "after" model_validator

# lets see an example by parsing sale.yaml

import yaml
from pydantic import BaseModel, model_validator
import pendulum
import os
from typing import Any


class SaleConfig(BaseModel):
    price: float # must make sure this flat is parsed as float
    min_qty: int # Nothing for min_qty
    
    @model_validator(mode="before")
    @classmethod
    def price_validator(cls, data: Any):
        if isinstance(data, dict) and isinstance(data.get("price"), str):
            data["price"] = data["price"].replace("$", "")
        return data


class PointConfig(BaseModel):
    x: int
    y: int
    
    # a before model validator that can accept x and y as either a tuple/list, or a dict or as a str
    @model_validator(mode="before")
    @classmethod
    def validate_before(cls, data: Any):
        if isinstance(data, (tuple, list)):
            return {"x": data[0], "y": data[1]}
        elif isinstance(data, str):
            a, b = data.split(",")
            return {"x": a, "y": b}    
        return data


class UserConfig(BaseModel):
    name: str
    display_name: str # we want to default this to name if not provided
    
    @model_validator(mode="before")
    @classmethod
    def set_display_name(cls, data: Any):
        if isinstance(data, dict):
            data.setdefault("display_name", data.get("name"))
        return data

class SampleConfig(BaseModel):
    sale: SaleConfig
    point: PointConfig
    user: UserConfig


class MainConfig(BaseModel):
    sample: SampleConfig
    


def main():
    with open(os.path.join(os.getcwd(), 'config.yaml')) as f:
        data = yaml.safe_load(f)
    cfg = MainConfig.model_validate(data)
    print(f"sale: {cfg.sample.sale}")
    print(f"point: {cfg.sample.point}")
    print(f"user: {cfg.sample.user}")
    
    point_1 = PointConfig.model_validate("100, 200")
    print(f"point_1: {point_1}")

    point_2 = PointConfig.model_validate((1, 2))
    print(f"point_2: {point_2}")

    user_cfg = UserConfig.model_validate({"name": "Rajat Girotra"})
    print(f"user_config: {user_cfg}")
    

if __name__ == "__main__":
    main()
    
# the "before model_validator is given the raw input. the argument "data" to this validator could be:
# 1. a dictionary
# 2. an instance of the model itself i.e. ItemConfig
# 3. Any arbitrary object.

# the main use of before model validate is to cleanup some input data so that it can be coersed/validated with no issues in the subsequent pipeline stages
# you can also use it when you have to want to validate/reference one field from otherer field. Example you want to default one field from another field.

# A very common construct is to create a model from a YAML config
from sys import excepthook

import yaml
from pydantic import BaseModel, ValidationError


class App(BaseModel):
    name: str
    version: str

class Server(BaseModel):
    host: str
    port: int

class Database(BaseModel):
    url: str
    pool_size: int
class Config(BaseModel):
    app: App
    server: Server
    database: Database


if __name__ == "__main__":
    try:
        with open('example.yaml', 'r') as f:
            data = yaml.safe_load(f)
            config = Config.model_validate(data)

        print(config.app.name)
    except ValidationError as e:
        print(e)

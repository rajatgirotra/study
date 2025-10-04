from typing import List

import yaml
from pydantic import BaseModel, ConfigDict, ValidationError

class ServerConfig(BaseModel):
    host: str
    port: int

class TimeoutConfig(BaseModel):
    connect_timeout: int
    read_timeout: int

class WebServiceConfig(ServerConfig, TimeoutConfig):
    name: str
    write_timeout: int = 0

class Config(BaseModel):
    default_server_config: ServerConfig
    timeouts: TimeoutConfig
    web_service_1: WebServiceConfig
    web_service_2: WebServiceConfig

if __name__ == "__main__":
    try:
        with open('anchor_alias.yaml', 'r') as f:
            data = yaml.safe_load(f)
            config = Config.model_validate(data)
            config2 = Config.model_validate(data)
            print(config)
            print(config2)
            print(config.model_dump())
    except ValidationError as e:
        print(e)
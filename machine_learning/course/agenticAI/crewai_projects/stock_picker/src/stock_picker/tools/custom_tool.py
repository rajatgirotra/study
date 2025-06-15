from crewai.tools import BaseTool
from typing import Type
from pydantic import BaseModel, Field
import os
import requests


class MyCustomToolInput(BaseModel):
    """Tools which uses Pushover API to send a push notification to your phone."""
    message: str = Field(description="message to send to your phone as a push notification.")

class MyCustomTool(BaseTool):
    name: str = "Message Tool"
    description: str = (
        "Custom tool used to send message to your phone using the Pushover API."
    )
    args_schema: Type[BaseModel] = MyCustomToolInput

    def _run(self, message: str) -> str:
        pushover_user = os.getenv('PUSHOVER_USER')
        pushover_token = os.getenv('PUSHOVER_TOKEN')
        payload = {'user': pushover_user, 'token': pushover_token, 'message': message}
        requests.post('https://api.pushover.net/1/messages.json', data=payload)

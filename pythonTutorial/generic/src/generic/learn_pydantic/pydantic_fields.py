from pydantic import BaseModel, EmailStr, Field

class User(BaseModel):
    email: EmailStr
    username: str = Field(default_factory=lambda data: data['email'])

user = User(email='user@example.com')
print(user.username)
#> user@example.com
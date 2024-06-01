from langchain_openai.llms import OpenAI

llm = OpenAI()
result = llm('Write a very very short poem')
print(result)

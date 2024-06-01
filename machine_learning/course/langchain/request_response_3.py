# We will create a simple chain with a PromptTemplate and an LLMChain

from langchain_openai.llms import OpenAI
from langchain.prompts import PromptTemplate
from langchain.chains import LLMChain, SequentialChain
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("--task", default="return a list of numbers")
parser.add_argument("--language", default="python")
args = parser.parse_args()

code_prompt = PromptTemplate(template='write a program in {language} to {task}', input_variables=['language', 'task'])
test_prompt = PromptTemplate(template='write a test for the {language} function "{code}"', input_variables=['language', 'code'])

llm = OpenAI()
code_chain = LLMChain(prompt=code_prompt, llm=llm, output_key='code')
test_chain = LLMChain(prompt=test_prompt, llm=llm, output_key='test')

chain = SequentialChain(
    chains=[code_chain, test_chain],
    input_variables=['language', 'task'],
    output_variables=['code', 'test'])

result = chain({'language': args.language, 'task': args.task})

print(">>>>>>> GENERATED CODE <<<<<<<")
code = result['code'].split('\n')
for line in code:
    print(line)

print(">>>>>>> GENERATED TEST <<<<<<<")
test = result['test'].split('\n')
for line in test:
    print(line)

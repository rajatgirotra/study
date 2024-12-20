# We will now build a text chat application using langchain.
# Let's first understand the difference between "completion" vs "conversational" LLM models.
# Majority of the LLM models are "completion" models. What that means is that they are designed to complete a given
# prompt. If I start typing some statement and I stop midway, the model will try to complete the statement taking
# context from whatever you have written so far.

# https://platform.openai.com/playground provides a playground where you can play with "completion" and
# "conversational" models.

# Actually, ChatGPT conversational model is based on "completion" model under the hood. The model itself doesn't have
# state or record of the previous conversation. To make a "conversational" model work, ChatGPT actually inputs all the text from
# the conversation into the model; so the model will now have all that context to work with and generate a response.

# Let's first write a simple chat application and see how it fails to maintain context.

from dotenv import load_dotenv
from langchain_openai.llms import OpenAI
from langchain.prompts import PromptTemplate
from langchain.chains import LLMChain, SequentialChain

load_dotenv()

content_prompt = PromptTemplate(template='{content}', input_variables=['content'])
llm = OpenAI()

chain = LLMChain(prompt=content_prompt, llm=llm)

while True:
    content = input(">> ")
    if content == 'exit':
        break
    result = chain({'content': content})
    print(f"AI: {result['text']}")

# Sample output:
# >> What is 1+1?
# AI: 1+1 is equal to 2.
# >> And 3 more?
# 4. What is your favorite food?
# 5. Can you tell us about a memorable travel experience?
# 6. Do you have any hidden talents or hobbies?
# >> exit
# you will notice that the model is not able to maintain context. It doesn't understand the question "And 3 more?"

# How to fix it now.
# We have to do a few changes
# 1. langchain assumes that majority of the LLM models are completion models. But since we want to use conversational
# model, we have to use the ChatOpenAI model from langchain.chat_models
# 2. We have to use a ChatPromptTemplate instead of PromptTemplate.

# A ChatPromptTemplate is a special kind of PromptTemplate that is designed to maintain context. If you played with
# the playground link above, you will notice OpenAI has three types of messages in a chat model.
# 1. "System"
# 2. "User",
# 3. "Assistant".
# The "System" message sets a behavior on the model. If I set the "System" message to: "You are a helpful and
# professional bot"; the model will generate helpful and professional responses. If I set the "System" message to:
# "You are a funny bot. Your answers are short and full of humour", the model will generate funny and short responses.
# The "User" message is the message that the user types. The "Assistant" message is the response generated by the model.
# The three "System", "User" and "Assistant" messages are called "System", "Human" and "AI" in langchain.
# The ChatPromptTemplate is used to to hold the specific SystemMessagePromptTemplate and HumanMessagePromptTemplates.
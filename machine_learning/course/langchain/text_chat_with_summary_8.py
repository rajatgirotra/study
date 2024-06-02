from dotenv import load_dotenv
from langchain_community.chat_models import ChatOpenAI
from langchain.prompts import ChatPromptTemplate, SystemMessagePromptTemplate, HumanMessagePromptTemplate, MessagesPlaceholder
from langchain.chains import SequentialChain, LLMChain
from langchain.memory import ConversationSummaryMemory

# ConversationSummaryMemory has its own chain (i.e. prompt and language model) that can summarize the conversation
# so far and provide a short summary. This can help limit the content on the prompt.
load_dotenv()
chat = ChatOpenAI(verbose=True)

memory = ConversationSummaryMemory(
    memory_key='messages', # key name to store the messages
    return_messages=True,  # populate the list with actual objects of type SystemMessage, UserMessage, AIMessage
    llm=chat
)

chat_prompt = ChatPromptTemplate(
    input_variables=['content', 'messages'],
    messages=[
        # SystemMessagePromptTemplate.from_template(template='You are a helpful and professional bot.'),
        MessagesPlaceholder(variable_name='messages'),  # expand the messages list here into System, Human, AI messages
        HumanMessagePromptTemplate.from_template(template='{content}')
    ],
    verbose=True
)

chain = LLMChain(
    prompt=chat_prompt,
    llm=chat,
    memory=memory,
    verbose=True
)

while True:
    content = input(">> ")
    if content == 'exit':
        break
    result = chain({'content': content})
    print(f"AI: {result['text']}")

# Note that we comment out the SystemMessagePromptTemplate. This is because the ConversationSummaryMemory
# will create a summary as you know, and that summary becomes the SystemMessage. So we don't need to add one.

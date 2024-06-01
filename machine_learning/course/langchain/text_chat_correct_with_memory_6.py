from dotenv import load_dotenv
from langchain_community.chat_models import ChatOpenAI
from langchain.prompts import ChatPromptTemplate, SystemMessagePromptTemplate, HumanMessagePromptTemplate, MessagesPlaceholder
from langchain.chains import SequentialChain, LLMChain
from langchain.memory import ConversationBufferMemory

# Think about this memory object as something which intercepts your input dictionary before it is
# sent to the chain. Similarly, it intercepts the output dictionary and can view/modify ot before sending
# the result back to the user.

load_dotenv()
chat = ChatOpenAI()
memory = ConversationBufferMemory(
    memory_key='messages', # key name to store the messages
    return_messages=True # populate the list with actual objects of type SystemMessage, UserMessage, AIMessage
)

prompt = ChatPromptTemplate(
    input_variables=['content', 'messages'],
    messages=[
        # SystemMessagePromptTemplate.from_template(
        # template='You are a funny bot. Your answers are short and full of humour.'),
        SystemMessagePromptTemplate.from_template(template='You are a helpful and professional bot.'),
        MessagesPlaceholder(variable_name='messages'),  # expand the messages list here into System, Human, AI messages
        HumanMessagePromptTemplate.from_template(template='{content}')
    ],
    verbose=True
)

chain = LLMChain(
    prompt=prompt,
    llm=chat,
    memory = memory,
    verbose=True)

while True:
    content = input(">> ")
    if content == 'exit':
        break
    result = chain({'content': content})
    print(f"AI: {result['text']}")

# Cool this works. Now let's add capability to store the conversation in a file. and load it so that our model can work
# across restarts. langchain provides many other tools to store these conversations like in DB, Cloud, S3 etc.

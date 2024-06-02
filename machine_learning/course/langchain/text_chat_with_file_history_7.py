from dotenv import load_dotenv
from langchain_community.chat_models import ChatOpenAI
from langchain.prompts import ChatPromptTemplate, SystemMessagePromptTemplate, HumanMessagePromptTemplate, MessagesPlaceholder
from langchain.chains import SequentialChain, LLMChain
from langchain.memory import ConversationBufferMemory, FileChatMessageHistory

load_dotenv()
chat = ChatOpenAI()
memory = ConversationBufferMemory(
    memory_key='messages', # key name to store the messages
    return_messages=True,  # populate the list with actual objects of type SystemMessage, UserMessage, AIMessage
    chat_memory=FileChatMessageHistory(file_path='messages.json')
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

# the problem with this code is that the prompt gets longer and longer as the converation progresses. and longer prompts are both
# expensive to run and also may not be as effective as shorter prompts. So we need to find a way to keep the prompt short.
# One such way is using ConversationSummaryMemory.
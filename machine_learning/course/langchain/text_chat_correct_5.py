from dotenv import load_dotenv
from langchain_community.chat_models import ChatOpenAI
from langchain.prompts import ChatPromptTemplate, SystemMessagePromptTemplate, HumanMessagePromptTemplate
from langchain.chains import SequentialChain, LLMChain

load_dotenv()
chat = ChatOpenAI()

prompt = ChatPromptTemplate(
    input_variables=['content'],
    messages=[
    # SystemMessagePromptTemplate.from_template(template='You are a funny bot. Your answers are short and full of humour.'),
    SystemMessagePromptTemplate.from_template(template='You are a helpful and professional bot.'),
    HumanMessagePromptTemplate.from_template(template='{content}')
    ],
    verbose=True
)

chain = LLMChain(
    prompt=prompt,
    llm=chat,
    verbose=True)

while True:
    content = input(">> ")
    if content == 'exit':
        break
    result = chain({'content': content})
    print(f"AI: {result['text']}")

# if you notice the output, still this chain isn't able to maintain context. The reason is that maintaining context
# is done with the help of langchain's memory set of classes. There are many memory classes, but for conversational
# models, we use ConversationBufferMemory. A memory object can do a lot of stuff except just buffering the messages.
# It can augment the input dictionary before passing on the dictionary to the PromptTemplate. It can also augment the
# output dictionary before returning the output. It can also store the state of the conversation.
# It can also store the state of the model etc.

# What does ConversationBufferMemory actually do? This memory object actually stores a list of SystemMessages,
# UserMessages, AIMessages objects in the output dictionary with key 'messages'. This 'messages' key automatically
# becomes part of your prompt in the next iteration.

# So in the next file, we will add the memory object and also refer to the 'messages' key in the chat prompt template.

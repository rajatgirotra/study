from langchain_community.document_loaders import TextLoader
from langchain.text_splitter import CharacterTextSplitter
from dotenv import load_dotenv
from langchain.embeddings import OpenAIEmbeddings

load_dotenv()

loader = TextLoader("facts.txt")

# The load give you a list of Document objects.
# each Document entry has a 'page_content' and a 'metadata' attribute. 'page_content' is the actual content & 'metadata'
# is some more information about the document source.
docs = loader.load()
print(docs)

# We can actually load and split in one go using a TextSplitter.
text_splitter = CharacterTextSplitter(
    separator='\n',  # i.e. split on new line
    chunk_size=200,  # i.e. first create a chunk of 200 characters and then find the nearest separator.
    chunk_overlap=0  # i.e. no overlap between chunks
)

docs = loader.load_and_split(text_splitter=text_splitter)
for doc in docs:
    print(doc.page_content)
    print('---')

# to create an embedding we have many algorithms. Example, OpenAI embeddings, SentenceTransformers, etc.
# These differ in the size of the vector they generate.
embeddings = OpenAIEmbeddings()
emb = embeddings.embed_query('Hello, how are you?')
print(type(emb), len(emb))

# don't yet generate the embeddings below. It will cost money. We will generate the embeddings when
# we setup means of storing these embeddings in a vector database. For that we install chromadb.
# WARNING: DO NOT UNCOMMENT LINES BELOW. IT TAKES TIME TO GENERATE EMBEDDINGS AND COSTS MONEY.
# for doc in docs:
#     emb = embeddings.embed_query(doc.page_content)

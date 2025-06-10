LLM standards for Large Language Model. These are artificial intelligence models created to understand and generate text. Examples include
1) ChatGPT from openAI. some recent models are gpt-4o, gpt-4o-mini, gpt-o1, o3-mini etc
2) Llama
3) Gemini from google - gemini-2-0-flash
4) Claude from Anthropic (claude-3-7-Sonnet)
5) deepseek (chinese model) - deepseek v3 and r1 models
6) Groq: LLMs including Llama 3.3
7) Ollama: local open source LLMs including LLama 3.2

Langchain: Langchain is a framework for designed for integrating these LLM models into your own applications. Langchain is available in many common programming languages like python, go, javascript etc.

But how does it all work eventually? Let's take an example:
===========================================================

You can visit pdf.ai to see what it does
1) You can upload a big pdf file.
2) the website will read and understand the pdf file
3) you can then ask questions from the pdf and it will comprehend and return the best answers.
4) it can even mention pages in the pdf which has reference to your answer.

Infact even in ChatGPT, you can copy the complete pdf text first and then ask a question. But ChatGPT usually errors out due to limitation of text it can accept.
Also language models do not work well if you give them tons of text when asking questions. So how is it supposed to work? To make the best use of large language models, you have to do something different. Let's see what langchain does.

1) Langchain will break up the pdf text into smaller chunks, lets say 1000 character chunk.
2) Each chunk now needs to be normalized. Which means it needs to be digested and converted into some other format which captures the RAW ESSENCE OF THE CHUNK.
3) This normalized output is done using a special algorithm called Embedding Generation Algorithm.
4) Embedding Generation Algorithm generates a vector of doubles. Each value in this vector is between -1 and 1. There are total of 1536 values in this vector
5) Each element captures some information (as a rank) about the chunk. Example: 
    * First element could capture the mood of the text. Happy, sad, normal
    * second element could capture, if the chunk is about a financial discussion etc.
6) All these embeddings need to be stored in a database. There are specialized databases called vector databases for storing these embeddings.
7) When a question is asked, the most relevant embedding is searched and that chunk is retrieved.
8) the question + chunk are then formatted into a prompt. 
9) The prompt is fed into the LLM and a response is fetched.

Langchain does all of this by providing very consistent api's. You can choose from a plethora of options like
1) from where to ingest text: Pdf, raw file, AWS S3, Confluence, Google drive, DB etc
2) Which embedding algo to use
3) Which LLM to use: ChatGPT, Llama, Bard, Claude etc etc.
All that can be done very easily because of the way the API's are written.

What is the meaning of chain in langchain
==========================================
langchain allows you to create a chain of Input --> Prompt --> LLM ---> Output. Lets call it a pipeline.
which means the output from one chain can then be sent to another Prompt + LLM

Later you will see that a "Chain" class in langchain encapsulates a PromptTemplate + LLM class. A PromptTemplate is just like a Jinja template in python.
You could create a pipeline with two chains. 
1) a code generation chain
2) a generating code checking chain.

The Input and Output are mostly dictionaries. The Input dictionary contains all the keys defined in your prompt template and the output dictionary contains the input dictionary + a special key which contains the result of the chain.

So a chain in a langchain is a foundation piece to make reusable text generation pipelines

Setup
=====
I created a new conda environment "openai". I installed the following packages:
openai
langchain-core --> Required
langchain --> Required
langchain-community --> community contributions to work with vector databases, different LLMs' etc
langchain-openai --> optimized version of langchain api's to work with openai LLM called ChatGPT.
python (3.12.3)
Lets start coding now!

I even signed up for a paid account on openai platform and paid 5 USD as LLM requests will travel over HTTP to openai servers. We are not using any locally installed LLM's for now.
and using openai platform isn't free. I created a pycode project and generated an openai key. that is used when working with langchain.

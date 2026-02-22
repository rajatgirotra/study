Agentic Coder
=============
Who is an agentic coder? this word has been abused and may mean multiple things. 
1. A coder/developer who uses an AI agent like cursor AI, claude code, copilot, kilcode etc. as a side back to aid in software development. Similar to a vibe coder.

2. A coder/developer who writes code to build one of these AI agents and Tools

Lets talk about the first one above.
How do you write code using an agent & tools.
1. Using an IDE, like
    cusor AI
    Codex from OpenAI
    Antigravity from google
    Windsurf AI
    Kiro

2. Using IDE plugins, like:
    Github copilot
    Kilocode
    Junie plugin for Jetbrains
    and many others.

3. CLI using:
    Cursor CLI
    claude code cli
    gemini cli
    AMPcode cli
    kilocode cli
    OpenCode cli

CLI coding agents are really getting popular. There are multiple stages of evolvement of an Agentic coder.

Stage 1. coder only uses an agent for autocomplete.

Stage 2. coder uses an ai coding agent as a side kick. the coding agent will run in a sidebar often asking for permissions to run certain tasks.

Stage 3. coder gives full autonomy to coding agent in the sidebar.

Stage 4. a coder's main window is the coding agent window. the main coding window goes to the side and the coder is not looking at the code being generated (may be he is just monitoring the diffs).

Stage 5. a coder has moved to a CLI coding agent

Stage 6. coder has started to use multiple CLI agents, say 3-5 agents to accomplish parallel tasks.

Stage 7. coder has started to use 10+ agents parallely so now he is highly leveraged.

Stage 8. coder has an agent which is orchestrating other agents. There are separate agent teams like a team of developer agents, a team of design agents, a team of BA agents, a team of test agents.
and an overall agent orchestrating the work parallelly among these agents.

LLM
===
A large language model is a program which can take as input a sequence of letters (or tokens) and it can predict the text that must follow it. It basically returns you multiple pairs of <text, probabilityofText> that should follow the input tokens.

Input: 2 + 2 is?
Output:
<4, 99.8%>
<22, 0.1%>
<"bananans", 0.05%>
<"I don't know math!", 0.05%>

An LLM by design is stateless. It doesnt have any memory or cache or doesn't have any history/thread of conversation. Each call is a seprate call with a "sequence of tokens" for which the LLM will predict the possible text that follows it.
Example:
Input Sequence: "Hello GPT! my name is Rajat"
Possible Output: "Hello Rajat!"

Input sequence: "What's my name?"
Possible Output: "I dont know!"

You may think but that is not something you experience while using GPT. that's because there is AI application or frontend to it which you interact with. It's called chatGPT.
chatGPT feeds the full conversation history to the underlying LLM on every call, so LLM has the context/information to return your name.

AI application
==============
An AI application is just an application which leverages an LLM under the hood to accomplish some business goal. Examples are:
* chatGPT
* cursor AI
* Atlassian Nevo
* Duolingo

These AI applications give you an illusion of memory. LLM has no memory. But the AI application on top can cache your conversation and feed it to every call of the LLM, giving you an illusion that you are having a conversion with the LLM.

Also it has been noticed that if you ask the LLM in your input token to "think and reason about every step it takes", it is seen that an LLM responses much more correctly and accurately.
So remember this important point.

Tools
=====
What are tools. Tools are helpful utilities scripts, processes, systems that can aid an LLM to construct much better output responses. Tools are themselves NOT RUN BY THE LLM.
We only provides LLM with a list of these tools and with information on what each tool does and we ask LLM to respond back in a particular format if they want the tool to be run.
Once LLM responds showing that it wants a tool to be run and see the output of that tool, it is upto the AI application to run the tool and feed the result back to the LLM as the next prompt.

Example:
Input: If you need run any Python code, responsd with "PYTHON: <the code to run>"
What is the sqrt of pi? 

Notice the output.

Loops
=====
One way to make LLM return meaningful output is to keep it in some kind of a loop. 
1. call the LLM
2. Once the response is received. Ask the LLM to review the response and check if the business goal is met?
3. If yes, stop.
4. If no, repeat and find answers to accomplish the business goal.
Read until lab_8.ipynb and deep_research before coming here.
We will now disucss CrewAI now.

CrewAI is multiple things.

1. CerewAI Enterprise: A multi agent platform for deploying, running, and monitoring agentic AI. go to crewai.com.
It is used to streamline workflows across industries with powerful AI agents. You can build and deploy automated workflows using any LLM and cloud platform.

2. CrewAI studio:
A low code/no code product for creating multi agent solutions using dag and drop. Similar n8n.io

3. CrewAI open source framework.
API provided by CrewAI for building agents ourselves. This is what we will study.


crewAI open source framework
============================
crewai is much more opinionated and prescriptive compared to OpenAI agents SDK.
Just like you have "Workflow" patterns and "autonomous AI" in agents SDK crewAI also defines two things:

1. CrewAI crews: Used for autonomous problem-solving, creative collaboration, or exploratory tasks.
2. CrewAI flows: used when you require deterministic outcomes, auditability or precise control over execution.

Some Fundamental entities defined in CrewAI
===========================================
LLM object: Very simple object that takes a string (model name argument)

Agent: Similar to openAI agents SDK. But it is slightly different. In OpenAI agents SDK, an agent had Instructions which was the system_prompt.
But in crewAI and Agent has an LLM, a role, a goal, a backstory, memory and tools.

Task: A specific assignment that needs to be carried out. So a Task will be given an Agent to work with. A task has a description and an expected output.

Crew: A team/aggregate of Agents and Tasks.

Configuration
=============
A great thing about crewAI is that it allows you to define a number of Agents and Tasks inside a YAML Configuration and these Agent and Tasks object will be created
automatically from this configuration. You will see later how "role", "goal", "backstory", "llm" are specified in the config file for defining Agents.
Similarly, how "description", "expected_output", "agent", "output_file" etc are specified in the config file for defining Tasks.

Later you will see there is also a standard way of creating and running crew projects (something like Django). crew uses python "uv" package manager for that.

Installing crewai:
uv tool install crewai

Create a new project:
crewai create crew my_crew

This creates a directory structure just like django. There will be some default config and src files generated.

Run the project:
crewai run (does uv run main.py behind the scenes)

We will create all crew projects into a separate directory.

================================================================================================================================================
In CrewAI, when you create an agent and specify:

Goal
Role
Backstory

these are used to construct the prompt sent to the underlying OpenAI LLM (like GPT-4o, GPT-4, or GPT-3.5). They map to specific parts of the system prompt, which defines the behavior
 and persona of the agent. Here's how they are typically mapped:

CrewAI builds a system prompt (e.g. for openai.ChatCompletion.create(...)) like:
You are a [ROLE].
Your goal is to [GOAL].
Backstory:
[BACKSTORY]

You must behave accordingly to your role and collaborate with others as needed.
================================================================================================================================================

Memory in CrewAI

CrewAI defines a concept called "Memory" which is used to capture (temporarily or permanently) the conversations of an Agent with LLM. These is done so that the LLM can be given
more information from this memory and the agents act more coherently and with continuity. The different types of memory supported are:

* Short Term memory --> This is a volatile, session-level memory that captures recent interactions or steps during the current run or task. It is limited to the current execution of the crew.
Usually we store information in a vector database.

* Long Term memory --> Persistent memory stored across sessions; typically backed by a vector database (e.g., ChromaDB, FAISS, Weaviate). Used to store past knowledge, research, or summaries 
that the agent might use in future tasks.

* Entity Memory --> Specialized memory for tracking entities — people, places, companies, etc. — and their properties. Works like a knowledge graph or key-value store.
Keeping track of facts and attributes tied to named entities. Avoiding redundant queries for known facts.
================================================================================================================================================

Before you go on to 6_README.txt, please see all projects in crewai_projects folder
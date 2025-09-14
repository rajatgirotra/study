LangGraphs

LangGraphs is yet another framework SDK for agentic AI, just like openAI agents SDK and crewAI. Similar to crewAI, langraph also has multiple offerings.

LangChain
=========
Langchain is a framwork for building applications that use LLM's. It provides tools to chain together LLM's i.e. output from one LLM becomes input for the next LLM.
You can integrate tools like websearch, databases, API's. You can handle memory, resources/documents etc. It has a very large open source community and is widely used.
It is particularly useful in building chatbots, workflow orchestration, agents that can work with tools, RAG (Retrieval Augmented Generation)

LangGraphs
==========
LangGraph is built on top of LangChain. LangGraph allows you to build multi-step or multi-agent based LLM applications just like LangChain, but these applications
can be stateful. i.e. you can build long-running, stateful applications. LangGraphs introduces control flow (i.e. branches, loops, error recovery) that is hard to model with vanilla langchain.
It's built for multi-agent, iterative, and stateful applications (eg, two agents collaborating and refining answers).

LangSmith
==========
LangSmith is a developer tool and observability platform built by the creators of LangChain. It's designed to help you debug, test, and monitor LLM-powered applications.
LangSmith gives you visibility into how your LangChain (or even non-LangChain) apps behave during execution. It provides you ability for Trace Execution, Debugging, Data Logging etc.

LangGraph platform
==================
PLatform for developing, deploying and scaling applications built with LangGraph.

LangGraph studio
================
LangGraph Studio is a specialized agent IDE that enables visualization, interaction, and debugging of agentic systems that implement the LangGraph Server API protocol.
Studio also integrates with LangSmith to enable tracing, evaluation, and prompt engineering.

Terminology
============
Agent Workflows are represented as graphs in LangGraph (like an inverted tree graph in computer science). 
And a "State" is a snapshot of your application at any given moment in time. A State is actually an object as you will see later.

A "Node" in this graph is actually a python function i.e. a function that performs some agentic logic. A "node" will take some State as input, do something and return a new State as its output. You can create multiple State objects, BUT A STATE IS IMMUTABLE.

An "Edge" is a connection between two Nodes. An egde is also a python function that determine which Node to execute next based on the State. They can be conditional or fixed/static.

A "Reducer": Every field in your State object can be optionally associated with a special function called a reducer. This reducer function takes the current value of the attribute/field and it knows how to combine and return a new value for that field. This is done in a clever way behind the scene by Langgraph in a way such that multiple Nodes can be running at the same time and creating a new State object without overwriting other Nodes work. We will see examples later and this will get more clearer.

So the meaty part is done in the nodes and egdes connect these agentic workflows together.

Anatomy of a langraph application
=================================
The way any LangGraph application is built and run is:
1. Define a State class -> You define a class which holds the metadata and information of the application as a whole.
2. Start a Graph builder -> A graph builder allows you to create Nodes and Edges. You can create multiple nodes and edges that define the layout of your workflow.
3. Create one or more Nodes or Edges.
4. Compile the graph -> This is where Langgraph understands your application workflow by looking at the nodes, edges and the state and prepares your application for running.
5. Finally, run your graph.

Lets get started now. Please read lab_9.ipynb next


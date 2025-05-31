"Agent" in Agentic AI fall under two categories (Agents and Workflows)

Agents
======
Agents are systems where LLMs dynamically direct their own processes and tool usage, maintaining control over how they accomplish tasks. Agents are the better option when flexibility and model-driven decision-making are needed at scale. These are fully autonomous systems that operate over extended time periods, using various tools to achieve complex tasks. Such a system would be composed of multiple LLMs, interacting to each other. The output from one LLM will be used to decide the order in which various tasks are carried out.

Workflow
========
This is where you create predefined prescriptive implementations called workflows. Workflows are systems where LLMs and tools are orchestrated through predefined code paths. Use workflows for well-defined tasks as they offer predictability and consistency.

There are many frameworks that make agentic systems easier to implement, like
1. LangGraphs from langchain
2. Amazon Bedrock's AI Agent framework
3. Rivet, Vellum, N8N.io all of which are GUI tools for building and testing complex workflows.
These frameworks make it easy to get started by simplifying standard low-level tasks like calling LLMs, defining and parsing tools, and chaining calls together. However, they often create extra layers of abstraction that can obscure the underlying prompts and responses, making them harder to debug. They can also make it tempting to add complexity when a simpler setup would suffice.

Now the basic building block of an agentic AI program is an "Augmented LLM". An LLM can be enhanced using augmentations such as retrieval, tools, and memory. There are many ways to implement this augmentation, but one approach which is very common is Model Context Protocol, which allows developers to integrate with a growing ecosystem of third pary tools with a simple client implementation.

Lets look at some workflow patterns:
Prompt chaining
---------------
The simplest workflow model is where you build a chain of LLM's, where output from one chain feeds to the next. You can add programmatic checks/conditions on any of the intermediate results to ensure that the process is still on track (or do you want to abondon it). This workflow is ideal for situations where the task can be easily and cleanly decomposed into fixed possibly re-usable subtasks, which are all called in order. The main goal is to trade off latency for higher accuracy, by making each LLM call an easier task. See workflow_prompt_chaining.png

Routing
-------
Routing classifies an input and directs it to a specialized followup task. This workflow allows for separation of concerns, and building more specialized prompts. Without this workflow, optimizing for one kind of input can hurt performance on other inputs. Routing works well for complex tasks where there are distinct categories that are better handled separately, and where classification can be handled accurately, either by an LLM or a more traditional classification model/algorithm. see workflow_routing.png.
Usecase: Directing different types of customer service queries (general questions, refund requests, technical support) into different downstream processes, prompts, and tools.

Parallellization
----------------
In this workflow, LLMs work simultaneously on a task and have their outputs aggregated programmatically. The tasks running in parallel on different LLMs could either be the same task or completely separate tasks.

Orchestrator-workers
--------------------
In the orchestrator-workers workflow, a central LLM dynamically breaks down tasks, delegates them to worker LLMs, and synthesizes their results. The difference between parallellization and orchestrator-worker is that parallellization involves code that you write on how to break the tasks and aggregate those. in orchestrator, even that is done autonomously by the central LLM.

Evaluator-optimizer
------------------
In the evaluator-optimizer workflow, one LLM call generates a response while another provides evaluation and feedback in a loop.
This is a powerful workflow as output of one LLM is validated by another. This workflow is particularly effective when we have clear evaluation criteria, and when iterative refinement provides measurable value. The two signs of good fit are, first, that LLM responses can be demonstrably improved when a human articulates their feedback; and second, that the LLM can provide such feedback.

Agents
======
Agents are emerging in production as LLMs mature in key capabilities—understanding complex inputs, engaging in reasoning and planning, using tools reliably, and recovering from errors. Agents begin their work with either a command from, or interactive discussion with, the human user. Once the task is clear, agents plan and operate independently, potentially returning to the human for further information or judgement. During execution, it's crucial for the agents to gain “ground truth” from the environment at each step (such as tool call results or code execution) to assess its progress. Agents can then pause for human feedback at checkpoints or when encountering blockers. The task often terminates upon completion, but it’s also common to include stopping conditions (such as a maximum number of iterations) to maintain control.

Agents can be used for open-ended problems where it’s difficult or impossible to predict the required number of steps, and where you can’t hardcode a fixed path. The LLM will potentially operate for many turns, and you must have some level of trust in its decision-making. Agents' autonomy makes them ideal for scaling tasks in trusted environments.

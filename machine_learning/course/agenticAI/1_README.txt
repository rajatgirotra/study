I purchased a udemy course. To setup my environment,
I installed cursor IDE (was an AppImage download from their website and I ran as ./CursorIde.AppImage --no-sandbox)
I installed uv - a very fast package manager for python (replacement for anaconda).
In cursor i installed two extension. (Python and Jupyter).

Then I created a projects directory. and cloned the agents project from github.
git clone https://github.com/ed-donner/agents.git

Then inside the cursor IDE i brought up the terminal and executed the following commands:

conda config --set auto_activate_base false
uv self update
uv sync
uv tool install crewai
uv tool upgrade crewai

This creates a .venv folder in the agents source root directory. This is nothing but a python virtual environment.

uv python list --> should list of python interpreters
uv tool list --> should print crewai as a tool

uv add xxx (is a replacement for pip install xxx)
uv run my_script.py (is a replacement for python my_script.py)
uv sync or uv add creates a pyproject.toml file which you should not manually edit. use uv tool only to edit it.

Then create a .env file with the OPENAI_API_KEY in that file.
Then open the 1_foundations/1_lab1.ipynb and choose to run it inside the .venv virtual environment. You many need to add this as one of the virtual environments.

Agentic AI
=========
What does agentic AI really mean? Agentic AI means any programs where the LLM outputs control the workflow. i.e. one output from LLM is able to decide what tasks are carried out in what sequence. More generally there are different hallmarks of agentic AI. Example:
1. Any solution involving multiple LLM calls.
2. LLM with the ability to use tools (like we used Philips Hue on n8n.io)
3. An environment where different LLM can interact.
4. A planner program to coordinate activities.
5. Autonomy (i.e. ability for an LLM to decide what happens next in a workflow)
Must read: https://www.anthropic.com/engineering/building-effective-agents (I have summarised in 2_README.txt)

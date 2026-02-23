# What is it?
You already know AGENTS.md is used as a resource to equip your coding agent with general useful information about your project. this includes things like the languages used
in your project, the business goal, the high level design patterns and philosophy you follow, coding standards, code structure and organization etc.

an AGENTS.md should live in your project's source root. Any folder pr sub-folder in your project can have it's own AGENTS.md which gets used when the coding agent is working on files in that particular folder. information from AGENTS.md in your sub-sub folder will override information from the AGENTS.md at higher level directories.

in claude code, this file is called CLAUDE.md
Google Antigravity calls it GEMINI.md

Cursor and copilot have other kinds of files like RULES.md but everyone is moving towards AGENTS.md

Important things in your AGENTS.md

# Project Summary
## Goals or Business Requirements
## Success Criteria
## Technical Details
## Color Scheme
## Strategy
## Coding standards and guidelines. Examples
1. Simpler is better - do not overcomplicate
2. Comments only when necessary
3. Be concise, short README, no emokis
4. IMPORTANT: Acoid overly defensive programming; avoid isinstance checks; only manage exceptions when necessary
5. Use uv; ALWAYS `uv run xxx` NEVER `python3 xxx`

Invest time crafting a good AGENTS.md. That's where we need to sweat. We need to spend, time, and effort in writing very good AGENTS.md at various levels.
keep it updated and supplement with extra files. Provide testing criteria. Prune things you don't need and add as things need.

There is another school of thought which says let it evolve gradually, you just focus on the end goal. Use other skills, loops, or more agents to get to your end goal.
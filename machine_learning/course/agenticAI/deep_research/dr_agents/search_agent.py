from agents import Agent, WebSearchTool, ModelSettings, Runner, trace
from IPython.display import Markdown, display
import asyncio

# Lets create a basic web search Agent. This agent is given a search term (eg: "Climate Change implications") and it can go out and perform a web search
# and come back with a lot of text on that topic.
SEARCH_INSTRUCTIONS = "You are a research assistant. Given a search term, you search the web for that term and \
produce a concise summary of the results. The summary must 2-3 paragraphs and less than 300 \
words. Capture the main points. Write succintly, no need to have complete sentences or good \
grammar. This will be consumed by someone synthesizing a report, so it's vital you capture the \
essence and ignore any fluff. Do not include any additional commentary other than the summary itself."

SearchAgent = Agent(name="SearchAgent",
                     instructions=SEARCH_INSTRUCTIONS,
                     model='gpt-4o-mini',
                     tools=[WebSearchTool(search_context_size='low')], # keep it low to limit your OpenAI billing. WebSearchTool is expensive.
                     model_settings=ModelSettings(tool_choice='required')
                    )

if __name__ == "__main__":
    # Lets test it out.
    message = "What are the implications of Climate Change?"
    with trace("Search"):
        result = asyncio.run(Runner.run(SearchAgent, message))

    display(result.final_output)

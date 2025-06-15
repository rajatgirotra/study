from agents import Agent, trace, Runner
from pydantic import BaseModel, Field
import asyncio

SEARCH_COUNT = 3

class WebSearchTerm(BaseModel):
    reason: str = Field(description="Your reasoning for why this search term is important to the query?")
    term: str = Field(description="The actual search term you will use to search the web.")

class WebSearchPlan(BaseModel):
    searches: list[WebSearchTerm] = Field(description="A list of web searches to perform to best answer the query.")

PLANNER_INSTRUCTIONS = f"You are a helpful research assistant. Given a query, come up with a set of web searches \
to perform to best answer the query. Output {SEARCH_COUNT} terms to query for."

PlannerAgent = Agent(name="PlannerAgent",
                      instructions=PLANNER_INSTRUCTIONS,
                      model='gpt-4o-mini',
                      output_type=WebSearchPlan,
                      )

if __name__ == "__main__":
    # lets test it out.
    message = "Implications of Climate Change?"
    with trace("Planner"):
        result = asyncio.run(Runner.run(PlannerAgent, message))
    print(result.final_output)
from agents import Runner
import asyncio
from .dr_agents import *
from .dr_agents.planner_agent import WebSearchPlan, WebSearchTerm
from .dr_agents.writer_agent import ReportData


# plan_searches will call the PlannerAgent
async def plan_searches(query: str) -> WebSearchPlan:
    """ Use the planner_agent to plan which searches to run for the query."""
    results = await Runner.run(PlannerAgent, input=query)
    print(f"Will perform {len(results.final_output.searches)} searches.")
    return results.final_output


async def perform_searches(search_term: WebSearchPlan):
    """ Call search() for each item in the search_terms list."""
    print(f"searching...")
    tasks = [asyncio.create_task(search(search_item)) for search_item in search_term.searches]
    results = await asyncio.gather(*tasks)
    print(f"finished searching.")
    return results

# search will call the SearchAgent to perform a single web search.
async def search(search_item: WebSearchTerm):
    """ Use the search agent to run a single web search."""
    # create input message for the SearchAgent
    input = f"Search term: {search_item.term}\nReason for searching: {search_item.reason}"
    result = await Runner.run(SearchAgent, input)
    return result.final_output

# These two functions will create a detailed report using the WriterAgent and send email using the EmailAgent.
async def write_report(query: str, search_results: list[str]):
    """ Use the writer agent to write a report based on the search results"""
    print("Thinking about report...")
    input = f"Original query: {query}\nSummarized search results: {search_results}"
    result = await Runner.run(WriterAgent, input)
    print("Finished writing report")
    return result.final_output

async def send_email(report: ReportData):
    """ Use the email agent to send an email with the report """
    print("Writing email...")
    result = await Runner.run(EmailAgent, report.markdown_report)
    print("Email sent")
    return report
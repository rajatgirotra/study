from crewai import Agent, Crew, Process, Task
from crewai.project import CrewBase, agent, crew, task
from crewai.agents.agent_builder.base_agent import BaseAgent
from typing import List
from pydantic import BaseModel, Field
from crewai_tools import SerperDevTool
from .tools.custom_tool import MyCustomTool
from crewai.memory import ShortTermMemory, LongTermMemory, EntityMemory
from crewai.memory.storage.rag_storage import RAGStorage
from crewai.memory.storage.ltm_sqlite_storage import LTMSQLiteStorage


# All these Field descriptions are very helpful as they are read by the LLM agent, and this guides the LLM and how/what to query and return.
class TrendingCompany(BaseModel):
    """ A company that is in the news and attracting attention """
    name: str = Field(description="The name of the trending company")
    ticker: str = Field(description="Stock ticker symbol of the company at the exchange")
    reason: str = Field(description="The reason why the company is trending in the news")

class TrendingCompanyList(BaseModel):
    """ A list of trending companies """
    companies: List[TrendingCompany] = Field(description="The list of trending companies")

class TrendingCompanyResearch(BaseModel):
    """ A deatiled report on a trending company """
    name: str = Field(description="The name of the trending company")
    market_position: str = Field(description="current market position and competetive analysis")
    future_prospects: str = Field(description="future prospects and growth potential")
    investment_recommendation: str = Field(description="investment recommendation and why")

class TrendingCompanyResearchList(BaseModel):
    """ A list of detailed reports on trending companies """
    research_list: List[TrendingCompanyResearch] = Field(description="The list of detailed reports on trending companies")

# If you want to run a snippet of code before or after the crew starts,
# you can use the @before_kickoff and @after_kickoff decorators
# https://docs.crewai.com/concepts/crews#example-crew-class-with-decorators

@CrewBase
class StockPicker():
    agents_config = "config/agents.yaml"
    tasks_config = "config/tasks.yaml"

    @agent
    def trending_company_finder(self) -> Agent:
        return Agent(config=self.agents_config['trending_company_finder'], verbose=True, tools=[SerperDevTool()], memory=True)
    
    @agent
    def financial_researcher(self) -> Agent:
        return Agent(config=self.agents_config['financial_researcher'], verbose=True, tools=[SerperDevTool()])
    
    @agent
    def stock_picker(self) -> Agent:
        return Agent(config=self.agents_config['stock_picker'], verbose=True, tools=[MyCustomTool()], memory=True)
    
    @task
    def find_trending_companies(self) -> Task:
        return Task(config=self.tasks_config['find_trending_companies'], verbose=True, output_pydantic=TrendingCompanyList)
    
    @task
    def research_trending_companies(self) -> Task:
        return Task(config=self.tasks_config['research_trending_companies'], verbose=True, output_pydantic=TrendingCompanyResearchList)
    
    @task
    def pick_best_company(self) -> Task:
        return Task(config=self.tasks_config['pick_best_company'], verbose=True)
    
    @crew
    def crew(self) -> Crew:
        """ Creates the StockPicker crew """
        manager = Agent(config=self.agents_config['manager'],
                         verbose=True,
                           allow_delegation=True)
        
        short_term_memory = ShortTermMemory(storage=
                                            RAGStorage(
                                               embedder_config={
                                                 "provider": "openai",
                                                 "model": "text-embedding-3-small"
                                               },
                                               type='short_term',
                                               path="./memory/"
                                             )
                                            )
        
        long_term_memory = LongTermMemory(storage=LTMSQLiteStorage(
                                            db_path="./memory/long_term_memory_storage.db"))
        
        entity_memory = EntityMemory(storage=
                                            RAGStorage(
                                               embedder_config={
                                                 "provider": "openai",
                                                 "model": "text-embedding-3-small"
                                               },
                                               type='short_term',
                                               path="./memory/"
                                             )
                                            )

        
        return Crew(agents=self.agents,
                    tasks=self.tasks,
                    process=Process.hierarchical,
                    verbose=True,
                    manager_agent=manager,
                    memory=True,
                    long_term_memory=long_term_memory,
                    short_term_memory=short_term_memory,
                    entity_memory=entity_memory)
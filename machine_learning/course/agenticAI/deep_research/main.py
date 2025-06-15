from dotenv import load_dotenv
from agents import trace, gen_trace_id
from .utils import plan_searches, perform_searches, write_report, send_email
import asyncio
import gradio as gr

load_dotenv(override=True)

class DeepResearch:
    async def run(self, query: str):
        print("Running deep research...")
        """ Run the deep research process, yielding the status updates and the final report"""
        trace_id = gen_trace_id()
        with trace("Deep Research trace", trace_id=trace_id):
            print(f"View trace: https://platform.openai.com/traces/trace?trace_id={trace_id}")
            yield f"View trace: https://platform.openai.com/traces/trace?trace_id={trace_id}"
            print("Starting research...")
            search_plan = await self.plan_searches(query)
            yield "Searches planned, starting to search..."     
            search_results = await self.perform_searches(search_plan)
            yield "Searches complete, writing report..."
            report = await self.write_report(query, search_results)
            yield "Report written, sending email..."
            await self.send_email(report)
            yield "Email sent, research complete"
            yield report.markdown_report

    async def plan_searches(self, query: str):
        return await plan_searches(query)

    async def perform_searches(self, search_plan):
        return await perform_searches(search_plan)

    async def write_report(self, query: str, search_results: list[str]):
        return await write_report(query, search_results)

    async def send_email(self, report):
        return await send_email(report)

async def main(query: str):
    async for chunk in DeepResearch().run(query):
        yield chunk

if __name__ == "__main__":
    with gr.Blocks(theme=gr.themes.Default(primary_hue="sky")) as ui:
        gr.Markdown("# Deep Research")
        query_textbox = gr.Textbox(label="What topic would you like to research?")
        run_button = gr.Button("Run", variant="primary")
        report = gr.Markdown(label="Report")
        
        run_button.click(fn=main, inputs=query_textbox, outputs=report)
        query_textbox.submit(fn=main, inputs=query_textbox, outputs=report)

    ui.launch(inbrowser=True)

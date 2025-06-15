from agents import Agent, ModelSettings, function_tool
import asyncio
import sendgrid
from sendgrid.helpers.mail import Email, To, Content, Mail
from typing import Dict
import os

# Now lets create some helper function to perform the web searches, prepare the report and send it by email.
@function_tool
def send_email(subject: str, html_body: str) -> Dict[str, str]:
    """
    Send an email with the given subject and body.
    """
    sg = sendgrid.SendGridAPIClient(api_key=os.getenv('SENDGRID_API_KEY'))
    from_email = Email("rajat.girotra@gmail.com")
    to_email = To("rajatgirotra@yahoo.com")
    subject = subject
    content = Content("text/html", html_body)
    mail = Mail(from_email, to_email, subject, content)
    response = sg.client.mail.send.post(request_body=mail.get())
    return {'status': 'success'}


# lets create an agent for sending emails.
EMAIL_INSTRUCTIONS = """You are able to send a nicely formatted HTML email based on a detailed report.
You will be provided with a detailed report. You should use your tool to send one email, providing the 
report converted into clean, well presented HTML with an appropriate subject line."""

EmailAgent = Agent(name="EmailAgent",
                    instructions=EMAIL_INSTRUCTIONS,
                    model='gpt-4o-mini',
                    tools=[send_email],
                    model_settings=ModelSettings(tool_choice='required')
                    )



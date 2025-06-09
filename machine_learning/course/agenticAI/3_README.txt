Read lab_1 and lab_2.ipynb first.

Agentic AI frameworks options
=============================

No framework at all
-------------------
Just use the core api provided by the LLM provider. You have full control over here.

MCP (Model Context Protocol):
----------------------------
MCP is not a framework. It is a protocol which defines a standard way of passing reference documents or contextual data (i.e. resources) into a conversation with an LLM model. The goal is to make the model more useful by giving it structured access to external knowledge without needing any retraining. Normally, a model will rely on its training data and the current conversation history. MCP allows the model to:
1. Understand specific documents or datasets.
2. Answer questions which are grounded in that dataset.
3. Provide more accurate, customized responses.

How MCP works??
Developers send documents or data into a special API endpoint (e.g., via the OpenAI API like v1/files, v1/model-contexts) to upload and register the context.
The data gets processed into a model-readable form called model context (tokens the model can "see"). this model context is persistent: it's loaded and available to the model across messages.
The model is queried with the context loaded, allowing it to reference the information directly.
This is different from traditional RAG (retrieval-augmented generation), where the model does a search. MCP gives the context directly, skipping the retrieval step. Example:
  * imagine you're building a support assistant.
  * You upload a PDF manual via MCP.
  * The model is then asked:
    "How do I reset the device?"
The model responds using knowledge from the manual you've uploaded.

You would have seen that a model can integrate with a "tool" using MCP and that tool can perform certain operations (like query a database or message another LLM). Note that these operations are not performed by the LLM. Eg: LLM can integrate with a Philips Hue account to turn/off lights. MCP isn't used to directly send commands to devices (like "turn on light"), but it helps the LLM understand how to interact with tools like the Philips Hue API. The actual device control is handled via tool use (function calling or API integration) by your application only, not by LLM. MCP is used to teach the LLM how the Hue API or account system works by injecting reference documents or API specifications into the model's context.

When a user says: "Turn on the living room lights", the LLM uses the MCP-loaded documentation to generate the appropriate API call (e.g.,
PUT /lights/3/state 
{
  "name": "setHueLightState",
  "arguments": {
    "light_id": "kitchen_light_id",
    "on": true
  }
})
This API call is sent to your application and your application sends an authenticated PUT request to: https://api.meethue.com/bridge/{username}/lights/{id}/state with the payload above. and then the application sends the result of the request back to LLM.


OpenAI Agents SDK
-----------------
Relatively new. getting popular. Just provides a nice abstraction of API's to work with any agent under the hood using a consistent API.

CrewAI
------


LangGraph
---------
Heavy weight and complex, but has great power. Very powerful but heavy learning curve. Has a lot of abstractions and has its own ecosystem.

Autogen
-------


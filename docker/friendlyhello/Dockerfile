# Use an official Python runtime as a parent image
FROM python:3.7-slim

# Set the working directory to /app
WORKDIR /app

# Copy the contents of the current directory to WORKDIR
COPY . /app

# Install additional pip packages
RUN pip install --trusted-host pypi.python.org -r requirements.txt

# make port 80 visible to the world outside this container
EXPOSE 80

# Define an environment variable
ENV NAME Rajat

# Run app.py when the container launches
CMD ["python", "app.py"]

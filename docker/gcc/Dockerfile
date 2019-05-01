# Use an official gcc image as parent image
FROM gcc:8.2.0

# setup working directory
WORKDIR /app

# copy contents of the current directory to WORKDIR
COPY . /app

# Start the compilation
RUN g++ --version
RUN g++ -std=c++17 1.cpp -o 1.out

# Run 1.out
CMD ["./1.out"]

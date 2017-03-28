OBJS := $(wildcard *.o)

prog : $(OBJS)
	@echo "Building prog using $(OBJS)"
	g++ $^ -o $@

data.o : data.h data.cpp
	g++ -c data.cpp

io.o : io.h io.cpp
	g++ -c io.cpp

main.o : data.h io.h main.cpp
	g++ -c main.cpp

.PHONY : clean

clean :
	rm -rf $(OBJS) prog 

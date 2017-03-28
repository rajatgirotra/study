CXXFLAGS     :=  -std=gnu++1y -fsanitize=leak -Wall -Wextra -Wconversion
LDFLAGS      := --shared -fPIC
LIB_PATH     := -L /home/rajatgirotra/tools/python/environments/generic27/venv/lib \
                -L /home/rajatgirotra/tools/gcc/5.2.0/lib64 \
                -L /home/rajatgirotra/tools/boost/1.59.0/lib

LIBS         := -lboost_python -lpython2.7 -lboost_system

INCLUDE_PATH := -isystem /home/rajatgirotra/tools/python/environments/generic27/venv/include/python2.7 \
                -isystem /home/rajatgirotra/tools/gcc/5.2.0/include \
                -isystem /home/rajatgirotra/tools/boost/1.59.0/include


####################################
SRC_1 = hello_ext.cpp
OBJ_1 = $(SRC_1:.cpp=.o)
TARGET_1 = $(SRC_1:.cpp=.so)

$(TARGET_1) : $(OBJ_1)
	g++ $(LDFLAGS) $(OBJ_1) -o $@ $(LIB_PATH) $(LIBS)

$(OBJ_1) : $(SRC_1)
	g++ -c -fPIC $(CXXFLAGS) $(INCLUDE_PATH) $<
####################################

####################################
SRC_2 = world.cpp
OBJ_2 = $(SRC_2:.cpp=.o)
TARGET_2 = $(SRC_2:.cpp=.so)

$(TARGET_2) : $(OBJ_2)
	g++ $(LDFLAGS) $(OBJ_2) -o $@ $(LIB_PATH) $(LIBS)

$(OBJ_2) : $(SRC_2)
	g++ -c -fPIC $(CXXFLAGS) $(INCLUDE_PATH) $<
####################################

####################################
SRC_3 = hello.cpp
OBJ_3 = $(SRC_3:.cpp=.o)
TARGET_3 = $(SRC_3:.cpp=.so)

$(TARGET_3) : $(OBJ_3)
	g++ $(LDFLAGS) $(OBJ_3) -o $@ $(LIB_PATH) $(LIBS)

$(OBJ_3) : $(SRC_3)
	g++ -c -fPIC $(CXXFLAGS) $(INCLUDE_PATH) $<
####################################

####################################
SRC_4 = num.cpp
OBJ_4 = $(SRC_4:.cpp=.o)
TARGET_4 = $(SRC_4:.cpp=.so)

$(TARGET_4) : $(OBJ_4)
	g++ $(LDFLAGS) $(OBJ_4) -o $@ $(LIB_PATH) $(LIBS)

$(OBJ_4) : $(SRC_4)
	g++ -c -fPIC $(CXXFLAGS) $(INCLUDE_PATH) $<
####################################

####################################
SRC_5 = member_property.cpp
OBJ_5 = $(SRC_5:.cpp=.o)
TARGET_5 = $(SRC_5:.cpp=.so)

$(TARGET_5) : $(OBJ_5)
	g++ $(LDFLAGS) $(OBJ_5) -o $@ $(LIB_PATH) $(LIBS)

$(OBJ_5) : $(SRC_5)
	g++ -c -fPIC $(CXXFLAGS) $(INCLUDE_PATH) $<
####################################

####################################
SRC_6 = base_derived.cpp
OBJ_6 = $(SRC_6:.cpp=.o)
TARGET_6 = $(SRC_6:.cpp=.so)

$(TARGET_6) : $(OBJ_6)
	g++ $(LDFLAGS) $(OBJ_6) -o $@ $(LIB_PATH) $(LIBS)

$(OBJ_6) : $(SRC_6)
	g++ -c -fPIC $(CXXFLAGS) $(INCLUDE_PATH) $<
####################################

####################################
SRC_7 = bd2.cpp
OBJ_7 = $(SRC_7:.cpp=.o)
TARGET_7 = $(SRC_7:.cpp=.so)

$(TARGET_7) : $(OBJ_7)
	g++ $(LDFLAGS) $(OBJ_7) -o $@ $(LIB_PATH) $(LIBS)

$(OBJ_7) : $(SRC_7)
	g++ -c -fPIC $(CXXFLAGS) $(INCLUDE_PATH) $<
####################################

####################################
SRC_8 = override.cpp
OBJ_8 = $(SRC_8:.cpp=.o)
TARGET_8 = $(SRC_8:.cpp=.so)

$(TARGET_8) : $(OBJ_8)
	g++ $(LDFLAGS) $(OBJ_8) -o $@ $(LIB_PATH) $(LIBS)

$(OBJ_8) : $(SRC_8)
	g++ -c -fPIC $(CXXFLAGS) $(INCLUDE_PATH) $<
####################################

clean:
	rm -rf *.so *.o

.PHONY : clean

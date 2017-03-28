APP_NAME := rajat.txt
SRCS := $(wildcard *.cpp)
SRCS += $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

$(APP_NAME) : $(OBJS)
	@echo Building $@ using $^
	@echo Building $(@D) using $(^D)
	@echo Building $(@F) using $(^F)
	@echo
	@echo Dependencies out of date are $?
	@echo Dependencies out of date are $(?D)
	@echo Dependencies out of date are $(?F)
	@echo 
	@echo First dependency is $<
	@echo First dependency is $(<D)
	@echo First dependency is $(<F)
	@-rm abc
	@touch $(APP_NAME)

target1 :: source1
	@echo building $@ using $^
	@touch $@

target1 :: source2
	@echo building $@ using $^
	@touch $@

.SUFFIXES : .foo .bar .baz .bax

.foo.bar:
	@echo "Source $< Target $@"
	@echo "Stem is $*"
	@touch "$@"

.cpp.o:
	@echo "building $@ from $^"

an.bar : an.foo

xxx := $(filter-out ./,$(sort $(dir $(wildcard ../cpp/*/))))

iterate :
	@echo $(xxx)
	@echo "ABCD"
	@$(foreach dir,$(filter-out ./,$(sort $(dir $(wildcard ../cpp/*/)))),ls $(dir);echo;)

SRC := $(shell echo "Ouch!" 1>&2; echo *.[cy]*)
OBJ := $(patsubst %.cpp,%.o,$(filter %.cpp,$(SRC))) \
      $(patsubst %.y,%.o,$(filter %.y,$(SRC)))

test : $(OBJ)
	@echo "Object: $(OBJ)"

FIG_REMOTE_URL ?= rajat

$(info $(FIG_REMOTE_URL))


.PHONY : $(APP_NAME) iterate test

# Make has two types of prerequisites - normal and order only.
# 1) Normal pre-requisite is a super-set of order only. Normal pre-requisite impose two things
#    a) An order - Meaning all recepies of the prerequisites must be made before the recipe for the target is run
#    b) A dependency relationship - If any prerequisite of the target is newer than the target, the target must be remade.
# 2) In Order-only only the "order" is imposed. meaning that the pre-requisite recipe will run before the target recipe.
#     However, the target will not be re-made if the pre-requisite is newer than the target.
# target : normal pre-requisite | order-only pre-requisite (a pipe symbol is used to separate them)
#
## Static Pattern Rules:
# These are rules are of the form A : B : C
# $(DBG_MAIN_O): out/dbg/main/%.o : $(MAIN_DIR)/%.cpp $(FIG_DONE)
# These are rules which specify multiple targets and construct the pre-requisite for each target based on the target name. So the pre-requisite is different for each target but has a similar pattern.

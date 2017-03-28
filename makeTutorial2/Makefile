OBJS := a.a b.b
SRCS := $(OBJS:a=c)
CXX := echo
CXXFLAGS := -g -O2
LDFLAGS := -ld
LD := ls

final : $(OBJS)
	@echo "Building target $@"
	@echo "First dependency $<"
	@touch final
	@echo "Built $@ using dependencies $^"
	@echo "SRCS = $(SRCS)"

hello : hello.cpp main.cpp

abc ::  xyz
	@echo "Building $@ using $^"
	@touch $@

abc :: pqr
	@echo "Building $@ using $^"
	@touch $@

# We will not study about .SUFFIXES rule as they are obsolete. Used pattern rules instead.

foo := a b c
# Use the subst function to convert "a b c" to "a,b,c"
comma := ,
empty :=
space := $(empty) $(empty)

DEBUG := 1

fooCsv := $(subst $(space),$(comma),$(foo))
s := $(patsubst %.c,%.o,x.c.c .c b.c.c)
t := $(subst %.c,%.o,x.c.c %.c b.c.c)
x :
	@echo "Building $@"
	@echo "$(fooCsv)"
	@echo "s = $(s)"
	@echo "t = $(t)"

OBJS := a.c b.c x.s x.h
ex : $(OBJS)
	@echo "Making $@"
	@echo "using only $(filter %.c %.s,$(OBJS))"
ifdef (DEBUG)
	@echo "Debug build"
else
	@echo "Release build"
endif


TARGET := bin/ggtest

CXX := g++
CXXFLAGS := -Og -g -Wall -Wextra -Werror


LD := g++
LDFLAGS := 
LIBS := -lm -lgtest -lgmock -pthread

VPATH := src

PREF_SRC := ./src/
PREF_OBJ := ./obj/
PREF_DEPS := ./deps/

SRCS := $(wildcard $(PREF_SRC)*.cpp)
OBJS := $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(SRCS))
#DEPS := $(patsubst $(PREF_SRC)%.cpp, $(PREF_DEPS)%.d, $(SRCS))

#include $(DEPS)

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

$(PREF_OBJ)%.o: $(PREF_SRC)%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

#$(DEPS): $(PREF_DEPS)%.d: $(PREF_SRC)%.cpp
#	$(CXX) $(CPPFLAGS) -MM $^ > $@


clean:
	rm -vrf *.o $(OBJS)*.o
	if [ -f $(TARGET) ]; then rm -v $(TARGET); fi;

test:
	./$(TARGET)

console:
	python3 ./swarm_py/user_console.py

CXX := g++
CXXFLAGS = -Wall -Wextra -g -std=c++17

BINPATH := bin
OBJPATH := $(BINPATH)/objs
SRCPATH := cli/*.cpp cli/commands/*.cpp
INCPATH := -Icli/commands

SOURCES := $(wildcard $(SRCPATH))
OBJECTS := $(patsubst %.cpp, $(OBJPATH)/%.o, $(notdir $(SOURCES)))

EXECUTABLE := $(BINPATH)/urchin

all: $(EXECUTABLE)

debug: CXXFLAGS += -D URCHIN_DEBUG
debug: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BINPATH)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJPATH)/%.o: cli/%.cpp
	@mkdir -p $(OBJPATH)
	$(CXX) $(CXXFLAGS) $(INCPATH) -c $< -o $@

$(OBJPATH)/%.o: cli/commands/%.cpp
	@mkdir -p $(OBJPATH)
	$(CXX) $(CXXFLAGS) $(INCPATH) -c $< -o $@

clean:
	@rm -rf $(BINPATH)

.PHONY: clean all debug

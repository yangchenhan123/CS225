EXE = quackfun

OBJS_DIR = .objs

OBJS_STUDENT = main.o exercises.o 
OBJS_TEST = tests/basic.o exercises.o
OBJS_PROVIDED = 

CXX = g++
LD = g++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y  -g -O0 $(WARNINGS) -MMD -MP -c
LDFLAGS = -L/opt/homebrew/lib/ -std=c++1y -lpng -lpthread
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

all: $(EXE) $(EXE)-asan

# Pattern rules for object files
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@
$(OBJS_DIR)/%-asan.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o $@

# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# Rules for executables... we can use a pattern for the -asan versions, but, unfortunately, we can't use a pattern for the normal executables
$(EXE):
	$(LD) $^ $(LDFLAGS) -o $@
%-asan:
	$(LD) $^ $(LDFLAGS) $(ASANFLAGS) -o $@


# Executable dependencies
$(EXE):      $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_PROVIDED))
$(EXE)-asan: $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_PROVIDED))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d

################# TEST CODE
test: $(OBJS_TEST)
	$(LD) $(OBJS_TEST) $(LDFLAGS) -o test

clean:
	rm -rf $(EXE) $(EXE)-asan $(OBJS_DIR) *.o *.d test $(OBJS_TEST) tests/*.d

tidy: clean
	rm -rf doc

.PHONY: all tidy clean

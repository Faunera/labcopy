WARNINGS := -Wall -Wextra -Wshadow -pedantic -Wfatal-errors -Werror -Wconversion -Wno-unused-variable -Wno-unused-parameter -Wfloat-equal

# GLM Include
GLM := ./ext/glm/
#GLFW Include
GLFWINCLUDE := ./ext/glfw-3.4/include/
GLFWHEADERS := $(shell find $(GLFWINCLUDE) -name "*.h")
# TinyXML2 Include
TINYXML := ./ext/tinyxml2-11.0.0/
TINYXMLHEADERS := $(TINYXML)tinyxml2.h
# GLAD Include
GLAD := ./ext/glad/include/
GLADH := $(shell find $(GLAD) -name "*.h")

#OLDEXT = -I$(GLM) -I$(GLFWINCLUDE) -I$(TINYXML) -lvulkan -ldl -lpthread -lXxf86vm
EXT := -I$(GLM) -I$(GLFWINCLUDE) -I$(TINYXML) -I$(GLAD) -lglfw -ldl
CXX := g++ -std=c++26
CPPFLAGS := $(WARNINGS)  $(EXT) -fmodules
HEADERMOD := -fmodule-header
SRC := $(shell find src/ -name "*.cc")
SRCP := $(shell find src/ -name "*.cpp")
OBJECTS = $(wildcard ./objs/*.o)

SOLECC := $(addsuffix .cc,$(filter-out $(basename $(SRCP)),$(basename $(SRC))))
DUOCC := $(addsuffix .cc,$(filter $(basename $(SRCP)),$(basename $(SRC))))

DEVFILE = ./dev.txt

DEVMAIN = devmain.a
PRODMAIN = main.a

all: check-std external build run clean clean-a
prod: check-std external compilemain run-valgrind clean clean-a
devnoclean: check-std external build run clean
prodnoclean: check-std external compilemain run-valgrind clean
container: check-std external compilemain run-default


no-run: check-std external head modules build clean

.PHONY: clean

# Check for C++ std module
check-std:
	@echo "Checking for std module"
	@[ -f gcm.cache/std.gcm ] && echo "std module exists" || $(MAKE) build-std

# If C++ std module doesn't exist, build it
build-std:
	@echo "Building std module"
	-@$(CXX) -c -fmodules -fmodule-only -fsearch-include-path bits/std.cc


external: checkext

# Check if external modules exist
checkext:
	@echo "Checking external library modules"
	-@find gcm.cache/ -name "glm.gcm" | grep . || $(MAKE) glmmod
	-@find gcm.cache/ -name "glfw3.h.gcm" | grep . || $(MAKE) glfwmod
	-@find gcm.cache/ -name "tinyxml2.h.gcm" | grep . || $(MAKE) xmlmod
	-@find ./objs/ -name "tinyxml2.o" | grep . || $(MAKE) xmlobj
	-@find gcm.cache/ -name "gl.h.gcm" | grep . || $(MAKE) gladmod
	-@find ./objs/ -name "gl.o" | grep . || $(MAKE) gladobj

# Build GLM module
glmmod:
	@echo "Building glm module"
	-@$(CXX) -O3 -fmodules $(GLM)/glm/glm.cppm -c

# Build GLFW headers into module
glfwmod:
	@echo "Building glfw module"
	-@$(CXX) -O3 $(HEADERMOD) $(GLFWHEADERS)

#Build TinyXml2 header modules
xmlmod:
	@echo "Building TinyXml2 module"
	-@$(CXX) -O3 $(HEADERMOD) $(TINYXMLHEADERS)

# Build TinyXML2 files into module object. Then move the object file to designated directory
xmlobj:
	@echo "Building tinyxml2 object"
	-@$(CXX) -O3 -I$(TINYXML) -fmodules $(TINYXML)tinyxml2.cpp -c
	-@mv ./tinyxml2.o ./objs/tinyxml2.o
# Build GLAD headers into module
gladmod:
	@echo "Building GLAD module"
	-@$(CXX) -O3 $(HEADERMOD) $(GLADH)
gladobj:
	@echo "Building GLAD objects"
	-@$(CXX) -O3 -I$(GLAD) -fmodules ./ext/glad/src/*.c -c
	-@mv ./vulkan.o ./objs/vulkan.o
	-@mv ./gl.o ./objs/gl.o

build: compiledev

# Try compilation several times in case there are CRC mismatches
## Then check for errors, if there are none, continue
## If errors are found, remove the executable
compiledev:
	-@$(MAKE) builddev 2>&1 | tee $(DEVFILE)
	-@cat $(DEVFILE) | grep "failed to read compiled module" &&  $(MAKE) compiledev
	-@cat $(DEVFILE) | grep "CRC mismatch" && $(MAKE) compiledev
	-@cat $(DEVFILE) | grep "error" && rm -f $(DEVMAIN) || true

# Build all source into object with sanitizer, to check for memory leaks
builddev:
	@echo "\nBuilding dev"
	-@$(CXX) -no-pie -fsanitize=address -g $(CPPFLAGS) $(OBJECTS) $(DUOCC) $(SRCP) $(SOLECC) main.cc -o $(DEVMAIN)

# Try compilation several times in case there are CRC mismatches
## Then check for errors, if there are none, continue
## If errors are found, remove the executable
compilemain:
	-@$(MAKE) buildmain 2>&1 | tee $(DEVFILE)
	-@cat $(DEVFILE) | grep "failed to read compiled module" &&  $(MAKE) compilemain
	-@cat $(DEVFILE) | grep "CRC mismatch" && $(MAKE) compilemain
	-@cat $(DEVFILE) | grep "error" && rm -f $(PRODMAIN) || true

# Build all source into object
buildmain:
	@echo "\nBuilding main"
	-@$(CXX) -no-pie -O3 $(CPPFLAGS) $(OBJECTS)  $(DUOCC) $(SRCP) $(SOLECC) main.cc -o $(PRODMAIN) && echo "Main build success"


run: run-dev

run-dev:
	-@echo "\n*** START DEV ***\n"
	-@./$(DEVMAIN)
	-@echo "\n*** END DEV ***\n\n\n"

run-default: $(PRODMAIN)
	-@echo "Launch main.a"
	-@./$(PRODMAIN)


# Check for leaks
run-valgrind: $(PRODMAIN)
	-@echo "Valgrind check"
	-@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./$(PRODMAIN)

clean:
	-@echo "Cleaning objects"
	-@$(RM) ./*.o

clean-a:
	-@$(RM) ./*.a

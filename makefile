CC = g++
CXXFLAGS = -std=c++17
LIB := -lsfml-window -lsfml-graphics -lsfml-system
SRC_DIR = src
LIB_DIR = lib
DEP_DIR = dep
BUILD_DIR = obj
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.d

SRC_DIRS := $(SRC_DIR)/
SRC_DIRS += $(sort $(dir $(wildcard $(SRC_DIR)/*/*/)))
SRC_DIRS += $(sort $(dir $(wildcard $(LIB_DIR)/*/)))

CPPSRC := $(foreach %,$(SRC_DIRS),$(wildcard $(%)*.cpp))
OBJ := $(foreach %,$(CPPSRC:.cpp=.o),$(BUILD_DIR)/$(%))
DEPENDENCIES := $(patsubst $(BUILD_DIR)%.o,$(DEP_DIR)%.d,$(OBJ))

INCLUDE_PREFIX = -I
INCLUDE_FLAGS := $(foreach %, $(SRC_DIRS), $(INCLUDE_PREFIX)$(%))

$(DEP_DIR)/%.d:
	@mkdir -p $(@D)

$(DEP_DIR):
	@mkdir -p $(DEP_DIR)

$(BUILD_DIR)/%.o: %.cpp $(DEP_DIR)/%.d | $(DEP_DIR)
	@echo ' *** compiling $< *** '
	@mkdir -p $(@D)
	@$(CC) $(CXXFLAGS) $(DEPFLAGS) -g -c -o $@ $< $(INCLUDE_FLAGS)

game: $(OBJ)
	@echo ' *** Building $@ *** '
	@$(CC) $(CXXFLAGS) -g -o $@ $^ $(LIB) $(INCLUDE_FLAGS)

clean:
	@rm -r $(OBJ) $(DEPENDENCIES) game

-include $(DEPENDENCIES)
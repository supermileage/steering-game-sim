CC = g++
CXXFLAGS = -std=c++17
LIB := -lsfml-window -lsfml-graphics -lsfml-system
SRC_DIR = src
LIB_DIR = lib
DEP_DIR = dep
BUILD_DIR = obj
TEST_DIR = test
MAIN_DIR = $(SRC_DIR)/Sim_Main
CATCH_DIR = lib/Catch2/single_include/catch2
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.d

SRC_DIRS := $(SRC_DIR)/
SRC_DIRS += $(sort $(dir $(wildcard $(SRC_DIR)/*/)))
SRC_DIRS += $(sort $(dir $(wildcard $(SRC_DIR)/*/*/)))
SRC_DIRS_TEST := $(TEST_DIR)/ $(CATCH_DIR)/
SRC_DIRS_TEST += $(sort $(dir $(wildcard $(TEST_DIR)/*/)))
SRC_DIRS_TEST += $(sort $(dir $(wildcard $(TEST_DIR)/*/*/)))
SRC_DIRS_TEST += $(filter-out $(MAIN_DIR)/,$(SRC_DIRS))

CPPSRC := $(foreach %,$(SRC_DIRS),$(wildcard $(%)*.cpp))
CPPSRC_TEST := $(foreach %,$(SRC_DIRS_TEST),$(wildcard $(%)*.cpp))
OBJ := $(foreach %,$(CPPSRC:.cpp=.o),$(BUILD_DIR)/$(%))
OBJ_TEST := $(foreach %,$(CPPSRC_TEST:.cpp=.o),$(BUILD_DIR)/$(%))
DEPENDENCIES := $(patsubst $(BUILD_DIR)%.o,$(DEP_DIR)%.d,$(OBJ))

INCLUDE_PREFIX = -I
INCLUDE_FLAGS := $(foreach %, $(SRC_DIRS), $(INCLUDE_PREFIX)$(%))
INCLUDE_FLAGS_TEST := $(foreach %, $(SRC_DIRS_TEST), $(INCLUDE_PREFIX)$(%))
INCLUDE_FLAGS := $(sort $(INCLUDE_FLAGS) $(INCLUDE_FLAGS_TEST))

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
	@$(CC) $(CXXFLAGS) -g -o $@ $^ $(LIB) $(INCLUDE)

tests: $(OBJ_TEST)
	@echo ' *** Building $@ *** '
	@$(CC) $(CXXFLAGS) -g -o $@ $^ $(LIB) $(INCLUDE_FLAGS)

all: game tests

clean:
	@rm -r $(OBJ) $(OBJ_TEST) $(DEPENDENCIES) game

-include $(DEPENDENCIES)
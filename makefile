COMPILER = g++
EXE = WorldCupUnitTester
FLAGS = -std=c++14 -Wall -Werror -pedantic-errors
G_FLAG = -g

MAIN = main
WORLD_CUP= src/worldcup23a2
UTIL= src/wet2util
PLAYER = src/Player
TEAM = src/Team

TESTS = tests/developer_tests

ALL_SRC_FILES = $(WORLD_CUP).h $(PLAYER).h $(TEAM).h $(UTIL).h
ALL_SRC_OBJ = $(WORLD_CUP).o $(PLAYER).o $(TEAM).o
ALL_TEST_FILES = $(TESTS).h
ALL_TEST_OBJ = $(TESTS).o

OBJ_FILES = $(ALL_SRC_OBJ) $(ALL_TEST_OBJ) $(MAIN).o

$(EXE): $(OBJ_FILES)
	$(COMPILER) $(G_FLAG) $(FLAGS) $(OBJ_FILES) -o $(EXE)


$(MAIN).o: $(MAIN).cpp  $(ALL_SRC_FILES) $(ALL_TEST_FILES)
	$(COMPILER) $(FLAGS) $(G_FLAG) -c $(MAIN).cpp -o $(MAIN).o





$(WORLD_CUP).o: $(WORLD_CUP).cpp $(WORLD_CUP).h $(UTIL).h
	$(COMPILER) $(FLAGS) $(G_FLAG) -c $(WORLD_CUP).cpp -o $(WORLD_CUP).o

$(PLAYER).o: $(PLAYER).cpp $(PLAYER).h $(TEAM).h $(UTIL).h
	$(COMPILER) $(FLAGS) $(G_FLAG) -c $(PLAYER).cpp -o $(PLAYER).o

$(TEAM).o: $(TEAM).cpp $(TEAM).h $(PLAYER).h $(UTIL).h
	$(COMPILER) $(FLAGS) $(G_FLAG) -c $(TEAM).cpp -o $(TEAM).o

$(TESTS).o: $(TESTS).cpp $(TESTS).h $(UTIL).h $(WORLD_CUP).h $(PLAYER).h $(TEAM).h
	$(COMPILER) $(FLAGS) $(G_FLAG) -c $(TESTS).cpp -o $(TESTS).o



clean:
	rm -f $(OBJ_FILES) $(EXE)
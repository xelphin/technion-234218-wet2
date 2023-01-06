COMPILER = g++
EXE = InOutTester
FLAGS = -std=c++14 -Wall -Werror -pedantic-errors
G_FLAG = -g

MAIN = main23a2
WORLD_CUP= worldcup23a2
UTIL= wet2util
PLAYER = Player
TEAM = Team
NODELIST = NodeList
HASH = Hash
AVL_TREE = AVL_tree
EXCEPTION = Exception
UNION_FIND = UnionFind



ALL_SRC_FILES =  $(WORLD_CUP).h $(PLAYER).h $(TEAM).h $(NODELIST).h $(HASH).h $(AVL_TREE).h $(UTIL).h $(EXCEPTION).h $(UNION_FIND).h
ALL_SRC_OBJ = $(WORLD_CUP).o $(PLAYER).o $(TEAM).o

OBJ_FILES = $(ALL_SRC_OBJ)  $(MAIN).o

$(EXE): $(OBJ_FILES)
	$(COMPILER) $(G_FLAG) $(FLAGS) $(OBJ_FILES) -o $(EXE)


$(MAIN).o: $(MAIN).cpp  $(ALL_SRC_FILES) 
	$(COMPILER) $(FLAGS) $(G_FLAG) -c $(MAIN).cpp -o $(MAIN).o





$(WORLD_CUP).o: $(WORLD_CUP).cpp $(WORLD_CUP).h $(UNION_FIND).h $(PLAYER).h $(TEAM).h $(AVL_TREE).h $(EXCEPTION).h $(NODELIST).h $(UTIL).h 
	$(COMPILER) $(FLAGS) $(G_FLAG) -c $(WORLD_CUP).cpp -o $(WORLD_CUP).o

$(PLAYER).o: $(PLAYER).cpp $(PLAYER).h $(TEAM).h $(UTIL).h $(AVL_TREE).h
	$(COMPILER) $(FLAGS) $(G_FLAG) -c $(PLAYER).cpp -o $(PLAYER).o

$(TEAM).o: $(TEAM).cpp $(TEAM).h $(PLAYER).h $(UTIL).h $(AVL_TREE).h $(UNION_FIND).h
	$(COMPILER) $(FLAGS) $(G_FLAG) -c $(TEAM).cpp -o $(TEAM).o



clean:
	rm -f $(OBJ_FILES) $(EXE)
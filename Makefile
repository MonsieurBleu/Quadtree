CC = g++
CPPFLAGS = -Wall 
LINKFLAGS = -lmingw32 -g

OBJ = obj/main.o obj/quadtree.o

INCLUDE = -Iinclude 
DEL_win = del /Q /F
EXEC = quadtree.exe

default: $(EXEC)

run :
	$(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LINKFLAGS)

install : $(EXEC)

obj/main.o : main.cpp
	$(CC) -c $(CPPFLAGS) $(LINKFLAGS) $(INCLUDE) $< -o $@ 

obj/%.o : src/%.cpp
	$(CC) -c $(CPPFLAGS) $(LINKFLAGS) $(INCLUDE) $< -o $@ 

.PHONY : clean install run default cleanwin winreinstall

clean : 
	$(DEL) $(EXEC) obj/*.o

cleanwin : 
	$(DEL_win) $(EXEC) obj\*.o

winreinstall : cleanwin install

countlines :
	find ./ -type f \( -iname \*.cpp -o -iname \*.hpp -o -iname \*.frag -o -iname \*.vert -o -iname \*.geom -o -iname \*.py \) | sed 's/.*/"&"/' | xargs  wc -l
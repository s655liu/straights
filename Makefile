CXX = g++
CXXFLAGS = -std=c++14 -Werror=vla -MMD 
EXEC = straights
OBJECTS = main.o player.o game.o subject.o exceptions.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

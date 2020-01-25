CXX = g++-5
CXXFLAGS = -g -std=c++14 -Wall -MMD -Werror=vla
#CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = cc3k+
OBJECTS = barrierSuit.o character.o enemy.o game.o main.o player.o stair.o textdisplay.o cell.o compass.o floor.o item.o object.o potion.o subject.o treasure.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

OBJS = dieTest playerTest twoPlayer TwoPlayerReplay

all: ${OBJS}

dieTest: dice.o
playerTest: player.o dice.o
twoPlayer: player.o dice.o GameLogic.o
TwoPlayerReplay: player.o dice.o GameLogic.o

dice.o: dice.h
player.o: player.h
GameLogic.o: GameLogic.h

clean:
	rm ${OBJS} *.o

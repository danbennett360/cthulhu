OBJS = dieTest playerTest twoPlayer TwoPlayerReplay multiPlayer

all: ${OBJS}

dieTest: dice.o
playerTest: player.o dice.o
twoPlayer: player.o dice.o GameLogic.o cliUtils.o stats.o
multiPlayer: player.o dice.o GameLogic.o cliUtils.o stats.o
TwoPlayerReplay: player.o dice.o GameLogic.o

dice.o: dice.h
player.o: player.h
GameLogic.o: GameLogic.h
cliUtils.o: cliUtils.h
stats.o: stats.h

clean:
	rm -f ${OBJS} *.o

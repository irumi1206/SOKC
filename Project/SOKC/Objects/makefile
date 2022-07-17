GTEST_DIR=googletest/googletest

player:
	g++ -o testPlayer testPlayer.cpp -isystem ${GTEST_DIR}/include -L${GTEST_DIR}/build -pthread -lgtest -ljsoncpp

game:
	g++ -o testGame testGame.cpp -isystem ${GTEST_DIR}/include -L${GTEST_DIR}/build -pthread -lgtest -ljsoncpp

go:
	./testGame
	./testPlayer
	
cleanGame:
	rm -rf testGame
	
cleanPlayer:
	rm -rf testPlayer

all:
	make player
	make game
	make go
	make cleanGame
	make cleanPlayer
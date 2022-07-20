GTEST_DIR=googletest/googletest

test:
	g++ -o tests testController.cpp -isystem ${GTEST_DIR}/include -L${GTEST_DIR}/build -pthread -lgtest -ljsoncpp
	./tests

player:
	g++ -o testPlayer Player/testPlayerObject.cpp -isystem ${GTEST_DIR}/include -L${GTEST_DIR}/build -pthread -lgtest -ljsoncpp

game:
	g++ -o testGame Player/testPlayerRepository.cpp -isystem ${GTEST_DIR}/include -L${GTEST_DIR}/build -pthread -lgtest -ljsoncpp

all:
	make test
	make player
	make game

	./tests
	./testPlayer
	./testGame

clear:
	rm -rf tests
	rm -rf testPlayer
	rm -rf testGame

GTEST_DIR=googletest/googletest

player:
	g++ -o tests testPlayer.cpp -isystem ${GTEST_DIR}/include -L${GTEST_DIR}/build -pthread -lgtest -ljsoncpp
	./tests

	rm -rf tests
game:
	g++ -o tests testGame.cpp -isystem ${GTEST_DIR}/include -L${GTEST_DIR}/build -pthread -lgtest -ljsoncpp
	./tests

	rm -rf tests
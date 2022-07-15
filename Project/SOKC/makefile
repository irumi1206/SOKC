GTEST_DIR=googletest/googletest

test:
	g++ -o tests testController.cpp -isystem ${GTEST_DIR}/include -L${GTEST_DIR}/build -pthread -lgtest -ljsoncpp
	./tests

	rm -rf tests

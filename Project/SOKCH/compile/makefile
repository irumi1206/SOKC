compile : 
	g++ -c /home/ubuntu/GameProject/Project/SOKCH/Player/playerImplements/missionPlayer.cpp
	g++ -c /home/ubuntu/GameProject/Project/SOKCH/Player/playerImplements/positionPlayer.cpp
	g++ -c /home/ubuntu/GameProject/Project/SOKCH/Player/playerImplements/rolePlayer.cpp
	g++ -c /home/ubuntu/GameProject/Project/SOKCH/Player/playerImplements/scorePlayer.cpp
	g++ -c /home/ubuntu/GameProject/Project/SOKCH/Player/playerObject.cpp
	g++ -c /home/ubuntu/GameProject/Project/SOKCH/Player/playerRepository.cpp
	g++ -c /home/ubuntu/GameProject/Project/SOKCH/gameController.cpp
	g++ -c /home/ubuntu/GameProject/Project/SOKCH/jsonparser/jsonparser.cpp

test:
	g++ /home/ubuntu/GameProject/Project/tests/testController.cpp gameController.o jsonparser.o missionPlayer.o playerObject.o playerRepository.o positionPlayer.o rolePlayer.o scorePlayer.o -o gameTest -ljsoncpp -isystem ${GTEST_DIR}/include -L${GTEST_DIR}/build -pthread -lgtest
	g++ /home/ubuntu/GameProject/Project/tests/Player/testPlayerObject.cpp gameController.o jsonparser.o missionPlayer.o playerObject.o playerRepository.o positionPlayer.o rolePlayer.o scorePlayer.o -o playerObjectTest -ljsoncpp -isystem ${GTEST_DIR}/include -L${GTEST_DIR}/build -pthread -lgtest
	g++ /home/ubuntu/GameProject/Project/tests/Player/testPlayerRepository.cpp gameController.o jsonparser.o missionPlayer.o playerObject.o playerRepository.o positionPlayer.o rolePlayer.o scorePlayer.o -o playerRepositoryTest -ljsoncpp -isystem ${GTEST_DIR}/include -L${GTEST_DIR}/build -pthread -lgtest
	./gameTest
	./playerObjectTest
	./playerRepositoryTest

clear:
	rm -rf gameController.o
	rm -rf jsonparser.o
	rm -rf missionPlayer.o
	rm -rf playerObject.o
	rm -rf playerRepository.o
	rm -rf positionPlayer.o
	rm -rf rolePlayer.o
	rm -rf scorePlayer.o
	rm -rf gameTest
	rm -rf playerObjectTest
	rm -rf playerRepositoryTest
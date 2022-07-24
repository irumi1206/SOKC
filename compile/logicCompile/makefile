

SOKC_PATH = /home/ubuntu/GameProject/SOKC
TEST_PATH = /home/ubuntu/GameProject/test
GTEST_DIR = googletest/googletest
PLAYER = Mission.o Player.o Position.o Role.o Score.o


mission.o :
	g++ -std=c++2a -c $(SOKC_PATH)/Player/playerImplements/Mission.cpp
	
position.o :
	g++ -std=c++2a -c $(SOKC_PATH)/Player/playerImplements/Position.cpp

role.o:
	g++ -std=c++2a -c $(SOKC_PATH)/Player/playerImplements/Role.cpp

score.o:
	g++ -std=c++2a -c $(SOKC_PATH)/Player/playerImplements/Score.cpp

player.o:
	g++ -std=c++2a -c $(SOKC_PATH)/Player/Player.cpp

game.o:
	g++ -std=c++2a -c $(SOKC_PATH)/Player/Game.cpp

controller.o:
	g++ -std=c++2a -c $(SOKC_PATH)/Controller.cpp

jsonparser.o:
	g++ -std=c++2a -c $(SOKC_PATH)/jsonParser/JsonParser.cpp


compile : 
	make mission.o
	make position.o
	make role.o
	make score.o
	make player.o
	make game.o
	make controller.o
	make jsonparser.o

test : mission.o position.o role.o score.o player.o game.o controller.o jsonparser.o
	g++ $(TEST_PATH)/testController.cpp $(PLAYER) Controller.o JsonParser.o Game.o -o gameTest -ljsoncpp -isystem ${GTEST_DIR}/include -L${GTEST_DIR}/build -pthread -lgtest
	g++ $(TEST_PATH)/Player/testPlayer.cpp $(PLAYER) -o PlayerTest -ljsoncpp -isystem ${GTEST_DIR}/include -L${GTEST_DIR}/build -pthread -lgtest
	g++ $(TEST_PATH)/Player/testGame.cpp $(PLAYER) Game.o -o GameTest -ljsoncpp -isystem ${GTEST_DIR}/include -L${GTEST_DIR}/build -pthread -lgtest
	./gameTest
	./PlayerTest
	./GameTest

clean :
	rm -rf Controller.o
	rm -rf JsonParser.o
	rm -rf Mission.o
	rm -rf Player.o
	rm -rf Game.o
	rm -rf Position.o
	rm -rf Role.o
	rm -rf Score.o
	rm -rf gameTest
	rm -rf PlayerTest
	rm -rf GameTest
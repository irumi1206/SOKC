

SOKC_PATH = /home/ubuntu/GameProject/SOKC-branch
TEST_PATH = /home/ubuntu/GameProject/test-branch
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

votingStatus.o:
	g++ -std=c++2a -c $(SOKC_PATH)/Player/VotingStatus.cpp

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
	make votingStatus.o

test : mission.o position.o role.o score.o player.o game.o controller.o jsonparser.o votingStatus.o
	make testController.o
	make testGame.o
	make testPlayer.o
	./ControllerTest
	./PlayerTest
	./GameTest
testController.o : VotingStatus.o Mission.o Player.o Position.o Role.o Score.o Controller.o JsonParser.o Game.o
	g++ $(TEST_PATH)/testController.cpp $(PLAYER) VotingStatus.o Controller.o JsonParser.o Game.o -o ControllerTest -ljsoncpp -isystem ${GTEST_DIR}/include -L${GTEST_DIR}/build -pthread -lgtest

testGame.o : VotingStatus.o Mission.o Player.o Position.o Role.o Score.o Game.o 
	g++ $(TEST_PATH)/Player/testGame.cpp $(PLAYER) VotingStatus.o Game.o -o GameTest -ljsoncpp -isystem ${GTEST_DIR}/include -L${GTEST_DIR}/build -pthread -lgtest

testPlayer.o : Mission.o Player.o Position.o Role.o Score.o
	g++ $(TEST_PATH)/Player/testPlayer.cpp $(PLAYER) -o PlayerTest -ljsoncpp -isystem ${GTEST_DIR}/include -L${GTEST_DIR}/build -pthread -lgtest

testController : VotingStatus.o Mission.o Player.o Position.o Role.o Score.o Controller.o JsonParser.o Game.o
	make testController.o
	./ControllerTest

testGame : VotingStatus.o Mission.o Player.o Position.o Role.o Score.o Game.o
	make testGame.o
	./GameTest

testPlayer : Mission.o Player.o Position.o Role.o Score.o
	make testPlayer.o
	./PlayerTest



clean :
	rm -rf Controller.o
	rm -rf JsonParser.o
	rm -rf Mission.o
	rm -rf Player.o
	rm -rf VotingStatus.o
	rm -rf Game.o
	rm -rf Position.o
	rm -rf Role.o
	rm -rf Score.o
	rm -rf ControllerTest
	rm -rf PlayerTest
	rm -rf GameTest
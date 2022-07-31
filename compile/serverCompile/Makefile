INFRA_PATH=/home/ubuntu/GameProject/infra/
SOKC_PATH=/home/ubuntu/GameProject/compile/logicCompile/

tcpServer : tcpServer.o tcpService.o tcpConnectionSocket.o tcpConnection.o
	g++ -std=c++2a $(SOKC_PATH)Score.o $(SOKC_PATH)Role.o $(SOKC_PATH)Position.o $(SOKC_PATH)Game.o $(SOKC_PATH)Player.o $(SOKC_PATH)Mission.o $(SOKC_PATH)JsonParser.o $(SOKC_PATH)Controller.o tcpServer.o tcpService.o tcpConnectionSocket.o tcpConnection.o -ljsoncpp -lpthread -o tcpServer

tcpServer.o : $(INFRA_PATH)tcpServer.cpp $(INFRA_PATH)tcpService.h $(INFRA_PATH)tcpConnectionSocket.h $(INFRA_PATH)tcpConnection.h
	g++ -std=c++2a -c $(INFRA_PATH)tcpServer.cpp

tcpService.o : $(INFRA_PATH)tcpService.cpp $(INFRA_PATH)tcpService.h $(INFRA_PATH)tcpConnectionSocket.h $(INFRA_PATH)tcpConnection.h 
	g++ -std=c++2a -c $(INFRA_PATH)tcpService.cpp

tcpConnectionSocket.o : $(INFRA_PATH)tcpConnectionSocket.cpp $(INFRA_PATH)tcpConnectionSocket.h $(INFRA_PATH)tcpConnection.h
	g++ -std=c++2a -c $(INFRA_PATH)tcpConnectionSocket.cpp

tcpConnection.o : $(INFRA_PATH)tcpConnection.cpp $(INFRA_PATH)tcpConnection.h
	g++ -std=c++2a -c $(INFRA_PATH)tcpConnection.cpp

udpServer : udpServer.o udpService.o udpConnection.o
	g++ udpServer.o udpService.o udpSocket.o -o udpServer

udpServer.o : udpServer.cpp udpService.h udpConnection.h
	g++ -c udpSercer.cpp

udpService.o : udpService.cpp udpService.h udpConnection.h
	g++ -c udpService.cpp

udpConnection.o : udpConnection.cpp udpConnection.h
	g++ -c udpConnection.cpp

tcpClient : $(INFRA_PATH)tcpClient.cpp
	g++ -std=c++2a $(INFRA_PATH)tcpClient.cpp -o tcpClient

udpClient : udpClient.cpp
	g++ udpClient.cpp -o udpClient

clean :
	rm -rf *.o
	rm -rf tcpServer
	rm -rf udpServer
	rm -rf tcpService
	rm -rf udpService

cleanClient :
	rm -rf *Client

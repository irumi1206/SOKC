

tcpServer : tcpServer.o tcpService.o tcpConnectionSocket.o tcpConnection.o
	g++ -std=c++2a /home/ubuntu/GameProject/Project/SOKCH/compile/Score.o /home/ubuntu/GameProject/Project/SOKCH/compile/Role.o /home/ubuntu/GameProject/Project/SOKCH/compile/Position.o /home/ubuntu/GameProject/Project/SOKCH/compile/Game.o /home/ubuntu/GameProject/Project/SOKCH/compile/Player.o /home/ubuntu/GameProject/Project/SOKCH/compile/Mission.o /home/ubuntu/GameProject/Project/SOKCH/compile/JsonParser.o /home/ubuntu/GameProject/Project/SOKCH/compile/Controller.o tcpServer.o tcpService.o tcpConnectionSocket.o tcpConnection.o -ljsoncpp -lpthread -o tcpServer

tcpServer.o : tcpServer.cpp tcpService.h tcpConnectionSocket.h tcpConnection.h
	g++ -std=c++2a -c tcpServer.cpp

tcpService.o : tcpService.cpp tcpService.h tcpConnectionSocket.h tcpConnection.h 
	g++ -std=c++2a -c tcpService.cpp

tcpConnectionSocket.o : tcpConnectionSocket.cpp tcpConnectionSocket.h tcpConnection.h
	g++ -std=c++2a -c tcpConnectionSocket.cpp

tcpConnection.o : tcpConnection.cpp tcpConnection.h
	g++ -std=c++2a -c tcpConnection.cpp

udpServer : udpServer.o udpService.o udpConnection.o
	g++ udpServer.o udpService.o udpSocket.o -o udpServer

udpServer.o : udpServer.cpp udpService.h udpConnection.h
	g++ -c udpSercer.cpp

udpService.o : udpService.cpp udpService.h udpConnection.h
	g++ -c udpService.cpp

udpConnection.o : udpConnection.cpp udpConnection.h
	g++ -c udpConnection.cpp

tcpClient : tcpClient.cpp
	g++ -std=c++2a tcpClient.cpp -o tcpClient

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

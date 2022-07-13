tcpServer : tcpServer.o tcpService.o tcpConnectionSocket.o tcpConnection.o
	g++ tcpServer.o tcpService.o tcpConnectionSocket.o tcpConnection.o -o tcpServer

tcpServer.o : tcpServer.cpp tcpService.h tcpConnectionSocket.h tcpConnection.h
	g++ -c tcpServer.cpp

tcpService.o : tcpService.cpp tcpService.h tcpConnectionSocket.h tcpConnection.h
	g++ -c tcpService.cpp

tcpConnectionSocket.o : tcpConnectionSocket.cpp tcpConnectionSocket.h tcpConnection.h
	g++ -c tcpConnectionSocket.cpp

tcpConnection.o : tcpConnection.cpp tcpConnection.h
	g++ -c tcpConnection.cpp

udpServer : udpServer.o udpService.o udpConnection.o
	g++ udpServer.o udpService.o udpSocket.o -o udpServer

udpServer.o : udpServer.cpp udpService.h udpConnection.h
	g++ -c udpSercer.cpp

udpService.o : udpService.cpp udpService.h udpConnection.h
	g++ -c udpService.cpp

udpConnection.o : udpConnection.cpp udpConnection.h
	g++ -c udpConnection.cpp

tcpClient : tcpClient.cpp
	g++ tcpClient.cpp -o tcpClient

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

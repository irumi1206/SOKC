INFRA_PATH=/home/ubuntu/GameProject/infra/
SOKC_PATH=/home/ubuntu/GameProject/compile/logicCompile/

TcpServer : TcpServer.o TcpService.o TcpConnectionSocket.o TcpConnection.o
	g++ -std=c++2a $(SOKC_PATH)Score.o $(SOKC_PATH)Role.o $(SOKC_PATH)Position.o $(SOKC_PATH)Game.o $(SOKC_PATH)Player.o $(SOKC_PATH)Mission.o $(SOKC_PATH)JsonParser.o $(SOKC_PATH)Controller.o $(SOKC_PATH)VotingStatus.o TcpServer.o TcpService.o TcpConnectionSocket.o TcpConnection.o -ljsoncpp -lpthread -o TcpServer

TcpServer.o : $(INFRA_PATH)TcpServer.cpp $(INFRA_PATH)TcpService.h $(INFRA_PATH)TcpConnectionSocket.h $(INFRA_PATH)TcpConnection.h
	g++ -std=c++2a -c $(INFRA_PATH)TcpServer.cpp

TcpService.o : $(INFRA_PATH)TcpService.cpp $(INFRA_PATH)TcpService.h $(INFRA_PATH)TcpConnectionSocket.h $(INFRA_PATH)TcpConnection.h 
	g++ -std=c++2a -c $(INFRA_PATH)TcpService.cpp

TcpConnectionSocket.o : $(INFRA_PATH)TcpConnectionSocket.cpp $(INFRA_PATH)TcpConnectionSocket.h $(INFRA_PATH)TcpConnection.h
	g++ -std=c++2a -c $(INFRA_PATH)TcpConnectionSocket.cpp

TcpConnection.o : $(INFRA_PATH)TcpConnection.cpp $(INFRA_PATH)TcpConnection.h
	g++ -std=c++2a -c $(INFRA_PATH)TcpConnection.cpp

UdpServer : UdpServer.cpp
	g++ std=c++2a $(INFRA_PATH)UdpServer.cpp -o UdpServer

TcpClient : $(INFRA_PATH)TcpClient.cpp
	g++ -std=c++2a $(INFRA_PATH)TcpClient.cpp -o TcpClient

UdpClient : UdpClient.cpp
	g++ std=c++2a $(INFRA_PATH)UdpClient.cpp -o UdpClient

cleanUdp :
	rm -rf UdpServer
	rm -rf UdpClient

clean :
	rm -rf *.o
	rm -rf TcpServer
#	rm -rf udpServer
	rm -rf TcpService
#	rm -rf $(INFRA_PATH)udpService
	rm -rf *Client


#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H


class TcpConnection{
    public :
        int tcpSocket;

    public :
        TcpConnection();
        int getTcpSocket();
        void setTcpSocket(int socketDescriptor);
        void in(char* buffer,int len);
        void out(char* message);
        void closeSocket();

        bool operator==(const TcpConnection &ob) const {
            return tcpSocket==ob.tcpSocket;
        }
        bool operator<(const TcpConnection &ob) const {
            return tcpSocket<ob.tcpSocket;
        }
};

#endif
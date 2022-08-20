#! /bin/bash
logicPath="/home/ubuntu/GameProject/compile/logicCompile/"
serverPath="/home/ubuntu/GameProject/compile/serverCompile/"

#cd ${logicPath} && make clean
cd ${serverPath} && make clean

#cd ${logicPath} && make compile
cd ${serverPath} && make TcpServer && ./TcpServer

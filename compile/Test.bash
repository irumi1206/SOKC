#! /bin/bash
logicPath="/home/ubuntu/GameProject/compile/logicCompile/"

cd ${logicPath} && make clean

cd ${logicPath} && make test
cd ${logicPath} && make clean
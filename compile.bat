CLS
@ECHO OFF
g++ main.cpp -o bin/main -Isrc -lWs2_32
bin\\main 192.168.0.1 100
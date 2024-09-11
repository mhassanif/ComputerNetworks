#!/bin/bash
rm server client
g++ -o server udp_server.cpp
g++ -o client udp_client.cpp
clear
# ./server
g++ -o server server.cpp
g++ -o client client.cpp
clear
gnome-terminal -- bash -c "./server; exec bash"
sleep 1
gnome-terminal -- bash -c "./client; exec bash"
gnome-terminal -- bash -c "./client; exec bash"
gnome-terminal -- bash -c "./client; exec bash"

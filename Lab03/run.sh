#!/bin/bash

# Compile server.c
gcc -o server server.c

# Compile client.c
gcc -o client client.c

# Run the server
./server
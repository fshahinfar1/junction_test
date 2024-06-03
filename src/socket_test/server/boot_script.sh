#!/bin/fish

set USER farbod
set HOME /home/farbod
echo "hello world!"
echo "THIS IS FROM INSIDE OF JUNCTION"

nc -l 192.168.127.3 8080

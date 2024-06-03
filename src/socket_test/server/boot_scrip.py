import sys
import socket

print('hello world!')
print('THIS IS FROM INSIDE OF JUNCTION')

ip = '192.168.127.3'
port = 8080

print(ip, port)
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((ip, port))
s.listen(10)

while True:
    c, addr = s.accept()
    msg = c.recv(2048)
    print('recv:', msg)

    reply = '200 OK\r\n\r\n'.encode()
    c.send(reply)
    c.close()

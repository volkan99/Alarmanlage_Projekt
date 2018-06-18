import socket

s= socket.socket()
s.connect(( '172.20.10.2', 30303))
s.setblocking(False)
s.send(b'Hello World\n')

#s.recv(1024)

s.close()

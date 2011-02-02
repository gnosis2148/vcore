import socket


sock = socket.socket (socket.AF_INET, socket.SOCK_STREAM)

sock.connect (('localhost', 5555))
sock.send ('aaaaaaa')
sock.close ()

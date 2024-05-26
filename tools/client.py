import socket

# Define the server address and port
server_address = 'localhost'
server_port = 8080

# Create a socket object
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    # Connect to the server
    print(f"Connecting to server {server_address}:{server_port}")
    sock.connect((server_address, server_port))
    print("Connected to server")

    # Send a message to the server
    message = "Hello, server!"
    print(f"Sending message: {message}")
    sock.sendall(message.encode())
    print("Message sent successfully")

finally:
    # Close the socket
    print("Closing connection")
    sock.close()

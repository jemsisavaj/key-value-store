import socket
import sys

def send_command(command):
    try:
        #connect with c++ server
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client.connect(('127.0.0.1',8080))

        #send command
        client.send(command.encode('utf-8'))

        #get output
        response = client.recv(1024).decode('utf-8')
        client.close()
        return response.strip()
    except Exception as e:
        return f"Error connecting to server: {e}"

if __name__ == '__main__':
    if len(sys.argv) < 2:
       print("Usage:")
       print("  python client.py SET <key> <value>")
       print("  python client.py GET <key>")
       print("  python client.py DEL <key>")
       print("  python client.py COMPACT")
       sys.exit(1)

    cmd = " ".join(sys.argv[1:])
    res = send_command(cmd)
    print(f"Server Response: {res}")
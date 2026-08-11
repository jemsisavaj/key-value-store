import socket
import time

def run_benchmark():
    total_requests = 1000
    print(f"Starting Benchmark: Sending {total_requests} SET requests to C++ Server...")

    start_time = time.time()

    for i in range(total_requests):
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.connect(('127.0.0.1', 8080))
            s.send(f"SET test_key_{i} value_{i}".encode('utf-8'))
            s.recv(1024)
            s.close()
        except Exception as e:
            print(f"Error at request {i}: {e}")
            break

    end_time = time.time()
    total_time = end_time - start_time
    rps = total_requests/total_time if total_time > 0 else 0

    print("==========================================")
    print(f"Completed {total_requests} requests!")
    print(f"Total Time Taken : {total_time:.2f} seconds")
    print(f"Server Throughput: {rps:.2f} requests/second")
    print("==========================================")

if __name__ == '__main__':
    run_benchmark()

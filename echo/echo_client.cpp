#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 7 // порт для службы echo

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[1024] = {0};

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "172.16.40.1", &server_address.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        return -1;
    }

    std::string message;
    std::cout << "Enter message: ";
    std::getline(std::cin, message);

    send(client_socket, message.c_str(), message.length(), 0);
    std::cout << "Message sent" << std::endl;

    read(client_socket, buffer, 1024);
    std::cout << "Server response: " << buffer << std::endl;

    close(client_socket);
    
    return 0;
}


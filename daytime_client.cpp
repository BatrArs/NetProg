#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "172.16.40.1"
#define SERVER_PORT 13

int main() {
    // Создаем UDP сокет
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket < 0) {
        std::cerr << "Крах при создании сокета" << std::endl;
        return 1;
    }

    // Настраиваем адрес сервера
    struct sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &(serverAddress.sin_addr)) <= 0) {
        std::cerr << "Крах при настраивании адреса" << std::endl;
        return 1;
    }

    // Отправляем пустой UDP-пакет на сервер
    if (sendto(clientSocket, nullptr, 0, 0, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Крах при отправке UDP пакета" << std::endl;
        return 1;
    }

    // Получаем ответ от сервера
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    socklen_t serverAddressLength = sizeof(serverAddress);
    if (recvfrom(clientSocket, buffer, sizeof(buffer), 0, (struct sockaddr*) &serverAddress, &serverAddressLength) < 0) {
        std::cerr << "Крах при получении UDP пакета" << std::endl;
        return 1;
    }

    // Выводим полученные данные
    std::cout << "Получено с сервера: " << buffer << std::endl;

    // Закрываем сокет
    close(clientSocket);

    return 0;
}

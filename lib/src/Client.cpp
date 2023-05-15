#include <Client.hpp>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <cassert>
#include <iostream>

namespace ClientLib
{
    Client::Client(const std::string &ip, uint16_t port)
    {
        std::cout << "Connecting to " << ip << ":" << port << std::endl;
        int rc;
        sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        assert(sock_fd != -1);

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);

        rc = inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);
        assert(rc != -1);

        std::cout << "Connected" << std::endl;
    }

    Client::~Client() = default;

} // namespace ClientLib
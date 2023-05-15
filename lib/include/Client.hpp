#pragma once

#include <netinet/in.h>
#include <cstdint>
#include <string>

namespace ClientLib
{
    class Client
    {
    private:
        int sock_fd;
        struct sockaddr_in server_addr;

    public:
        Client(const std::string &ip, uint16_t port);
        ~Client();
    };

} // namespace ClientLib

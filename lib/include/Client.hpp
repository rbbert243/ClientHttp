#pragma once

#include <Response.hpp>
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

        bool is_connected = false;

    public:
        Client(const std::string &ip, uint16_t port);
        ~Client();
        void establish_connection();
        void send_request(const std::string &request);
        Response receive_response();
    };

} // namespace ClientLib

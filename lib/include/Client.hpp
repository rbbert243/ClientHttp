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

    public:
        explicit Client(uint16_t port);
        ~Client();
        void establish_connection() const;
        void reconnect();
        void send_request(const std::string &request) const;
        Response receive_response() const;
    };

} // namespace ClientLib

#pragma once

#include <Response.hpp>
#include <netinet/in.h>
#include <cstdint>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace ClientLib
{
    class Client
    {
    private:
        int sock_fd;
        struct sockaddr_in server_addr;
        bool is_connected = false;
        void check_connection();

    public:
        Client(const std::string &ip, uint16_t port);
        ~Client();
        void establish_connection();
        void reconnect();
        void send_request(const std::string &request);
        Response receive_response();
    };

} // namespace ClientLib

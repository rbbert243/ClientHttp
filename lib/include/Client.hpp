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
        std::thread keep_alive_thread;
        std::mutex keep_alive_mutex;
        std::condition_variable keep_alive_cv;
        bool stop_keep_alive = false;
        void terminate();
        void keep_alive();

    public:
        Client(const std::string &ip, uint16_t port);
        ~Client();
        void establish_connection();
        void reconnect();
        void send_request(const std::string &request) const;
        Response receive_response() const;
        void start_keep_alive();
    };

} // namespace ClientLib

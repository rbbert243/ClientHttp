#include <Client.hpp>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cassert>
#include <iostream>
#include <array>
#include <poll.h>

namespace ClientLib
{
    Client::Client(const std::string &ip, uint16_t port)
    {
        sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        assert(sock_fd != -1);

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);

        assert(inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) != -1);
    }

    Client::~Client()
    {
        terminate();
    }

    void Client::establish_connection()
    {
        assert(connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) != -1);
    }

    void Client::reconnect()
    {
        close(sock_fd);
        sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        assert(sock_fd != -1);
        assert(connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) != -1);
    }

    void Client::send_request(const std::string &request) const
    {
        size_t bytes_sent = 0;
        while (bytes_sent < request.length())
        {
            ssize_t bytes = send(sock_fd, request.c_str() + bytes_sent, request.length() - bytes_sent, 0);
            assert(bytes != -1);
            bytes_sent += bytes;
        }
    }

    Response Client::receive_response() const
    {
        std::string response;
        std::array<char, 4096> buffer;
        ssize_t bytes_received;
        do
        {
            bytes_received = recv(sock_fd, buffer.data(), buffer.size(), 0);
            assert(bytes_received != -1);
            response.append(buffer.data(), bytes_received);
        } while (bytes_received == static_cast<ssize_t>(buffer.size()));
        return Response(response);
    }

    void Client::start_keep_alive()
    {
        keep_alive_thread = std::thread(&Client::keep_alive, this);
    }

    void Client::keep_alive()
    {
        while (true)
        {
            std::unique_lock<std::mutex> lock(keep_alive_mutex);
            if (keep_alive_cv.wait_for(lock, std::chrono::seconds(1), [this]()
                                       { return stop_keep_alive; }))
            {
                break;
            }

            struct pollfd poll_fd;
            poll_fd.fd = sock_fd;
            poll_fd.events = POLLHUP | POLLERR;

            int ret = poll(&poll_fd, 1, 0);
            assert(ret != -1);
            if (ret > 0 && (poll_fd.revents & (POLLHUP | POLLERR)))
            {
                std::cout << "Connection lost" << std::endl;
                reconnect();
            }
        }
    }

    void Client::terminate()
    {
        stop_keep_alive = true;
        if (keep_alive_thread.joinable())
        {
            keep_alive_thread.join();
        }
    }

} // namespace ClientLib
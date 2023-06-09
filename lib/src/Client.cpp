#include <Client.hpp>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cassert>
#include <array>

#define forever for (;;)

namespace ClientLib
{
    const std::string ip = "34.254.242.81";
    Client::Client(uint16_t port)
    {
        sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        assert(sock_fd != -1);

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);

        assert(inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) != -1);
    }

    Client::~Client() = default;

    void Client::establish_connection() const
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
        int content_length = -1;

        forever
        {
            bytes_received = recv(sock_fd, buffer.data(), buffer.size(), 0);
            assert(bytes_received != -1);

            response.append(buffer.data(), bytes_received);

            if (content_length == -1)
            {
                size_t pos = response.find("\r\n\r\n");
                if (pos != std::string::npos)
                {
                    content_length = std::stoi(response.substr(response.find("Content-Length: ") + 16, response.find("\r\n") - response.find("Content-Length: ") - 16));
                }
            }

            if (content_length != -1 && (int)(response.length() - response.find("\r\n\r\n") - 4) == content_length)
            {
                break;
            }
        }

        return Response(response);
    }

} // namespace ClientLib
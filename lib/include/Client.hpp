#pragma once

#include <Response.hpp>
#include <netinet/in.h>
#include <cstdint>
#include <string>

namespace ClientLib
{
    /**
     * @brief A class representing a client that can establish a connection to a server and send/receive data.
     */
    class Client
    {
    private:
        int sock_fd; /**< The socket file descriptor used for communication. */
        struct sockaddr_in server_addr; /**< The address of the server to connect to. */

    public:
        /**
         * @brief Constructs a new Client object.
         * 
         * @param port The port number to connect to.
         */
        explicit Client(uint16_t port);

        /**
         * @brief Destroys the Client object.
         */
        ~Client();

        /**
         * @brief Establishes a connection to the server.
         */
        void establish_connection() const;

        /**
         * @brief Reconnects to the server.
         */
        void reconnect();

        /**
         * @brief Sends a request to the server.
         * 
         * @param request The request to send.
         */
        void send_request(const std::string &request) const;

        /**
         * @brief Receives a response from the server.
         * 
         * @return The response received.
         */
        Response receive_response() const;
    };

} // namespace ClientLib
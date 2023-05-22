#pragma once

#include <Client.hpp>
#include <make_unique.hpp>
#include <memory>

namespace ClientLib
{
    /**
     * @brief A class representing a session with a server.
     */
    class Session
    {
    private:
        std::unique_ptr<Client> client; /**< The client used for communication with the server. */
        std::string cookie = ""; /**< The cookie to include in requests, if any. */
        std::string jwt = ""; /**< The JWT to include in requests, if any. */

    public:
        friend class Client;

        /**
         * @brief Constructs a new Session object.
         * 
         * @param client The client to use for communication with the server.
         */
        explicit Session(std::unique_ptr<Client> client);

        /**
         * @brief Destroys the Session object.
         */
        ~Session();

        /**
         * @brief Parses a command entered by the user.
         * 
         * @param command The command to parse.
         */
        void parse_command(const std::string &command);

        /**
         * @brief Sends a request to the server.
         * 
         * @param request The request to send.
         */
        void send_request(const std::string &request);

        /**
         * @brief Creates a new Session object.
         * 
         * @param client The client to use for communication with the server.
         * @return A unique_ptr to the newly created Session object.
         */
        static std::unique_ptr<Session> create(std::unique_ptr<Client> client)
        {
            return std::make_unique<Session>(std::move(client));
        }
    };

} // namespace ClientLib
#pragma once

#include <Client.hpp>
#include <make_unique.hpp>
#include <memory>

namespace ClientLib
{
    class Session
    {
    private:
        std::unique_ptr<Client> client;
        std::string cookie = "";

    public:
        friend class Client;
        explicit Session(std::unique_ptr<Client> client);
        ~Session();
        void parse_command(const std::string &command);
        void send_request(const std::string &request);

        static std::unique_ptr<Session> create(std::unique_ptr<Client> client)
        {
            return std::make_unique<Session>(std::move(client));
        }
    };

} // namespace ClientLib
#include <Session.hpp>
#include <Request.hpp>
#include <json.hpp>
#include <string>
#include <iostream>

using json = nlohmann::json;

namespace ClientLib
{

    Session::Session(std::unique_ptr<Client> client) : client(std::move(client))
    {
        this->client->establish_connection();
    }

    Session::~Session() = default;

    void Session::parse_command(const std::string &command)
    {
        if (command == "help")
        {
            std::cout << "Available commands are register, exit" << std::endl;
        }
        else if (command == "register")
        {
            std::string username;
            std::string password;
            std::cout << "username=";
            getline(std::cin, username);
            if (username.find(' ') != std::string::npos)
            {
                std::cout << "Username cannot contain spaces" << std::endl;
                return;
            }
            std::cout << "password=";
            getline(std::cin, password);
            if (password.find(' ') != std::string::npos)
            {
                std::cout << "Password cannot contain spaces" << std::endl;
                return;
            }

            json payload = {
                {"username", username},
                {"password", password},
            };

            auto request = Request("POST", "/api/v1/tema/auth/register", payload);
            send_request(request.to_string());
        }
    }

    void Session::send_request(const std::string &request)
    {
        client.get()->send_request(request);
        auto response = client.get()->receive_response();
    }

} // namespace ClientLib
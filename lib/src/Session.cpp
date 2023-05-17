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
        this->client.get()->start_keep_alive();
    }

    Session::~Session() = default;

    void Session::parse_command(const std::string &command)
    {
        if (command == "register")
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
        else if (command == "login")
        {
            if (cookie != "")
            {
                std::cout << "Already logged in" << std::endl;
                return;
            }
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

            auto request = Request("POST", "/api/v1/tema/auth/login", payload);
            send_request(request.to_string());
        }
    }

    void Session::send_request(const std::string &request)
    {
        client.get()->send_request(request);
        auto response = client.get()->receive_response();
        if (response.get_status_code() >= 200 && response.get_status_code() < 300)
        {
            std::cout << "Success" << std::endl;
            auto headers = response.get_headers();
            if (headers.find("\nSet-Cookie") != headers.end())
            {
                cookie = headers["\nSet-Cookie"];
            }
        }
        else if (response.get_status_code() >= 400 && response.get_status_code() < 500)
        {
            json response_body = json::parse(response.get_body());
            std::cout << response_body["error"] << std::endl;
        }
        else if (response.get_status_code() >= 500 && response.get_status_code() < 600)
        {
            std::cout << "Server error" << std::endl;
        }
        else
        {
            std::cout << "Connection is closed" << std::endl;
        }
    }

} // namespace ClientLib
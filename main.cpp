#include <Client.hpp>
#include <Session.hpp>
#include <make_unique.hpp>
#include <iostream>
#include <string>

#define SERVER_IP "34.254.242.81"
#define SERVER_PORT 8080

#define forever for (;;)

int main()
{
    std::string command;
    auto client = make_unique<ClientLib::Client>(SERVER_IP, SERVER_PORT);
    auto session = ClientLib::Session::create(std::move(client));
    forever
    {
        getline(std::cin, command);
        if (command == "exit")
        {
            break;
        }
        else
        {
            session->parse_command(command);
        }
    }

    return 0;
}
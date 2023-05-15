#include <Client.hpp>
#include <make_unique.hpp>
#include <iostream>
#include <string>

#define SERVER_IP "34.254.242.81"
#define SERVER_PORT 8080

int main()
{
    std::string command;
    auto client = make_unique<ClientLib::Client>(SERVER_IP, SERVER_PORT);
    client->connect();
    while (std::cin >> command)
    {
        if (command == "exit")
        {
            break;
        }
    }

    return 0;
}
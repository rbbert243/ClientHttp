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
        else if (command == "enter_library")
        {
            auto request = Request("GET", "/api/v1/tema/library/access", cookie);
            send_request(request.to_string());
        }
        else if (command == "get_books")
        {
            auto request = Request("GET", "/api/v1/tema/library/books", cookie, jwt);
            send_request(request.to_string());
        }
        else if (command == "get_book")
        {
            std::string id;
            std::cout << "id=";
            getline(std::cin, id);
            auto request = Request("GET", "/api/v1/tema/library/books", cookie, jwt, id);
            send_request(request.to_string());
        }
        else if (command == "add_book")
        {
            std::string title;
            std::string author;
            std::string genre;
            std::string publisher;
            std::string page_count;

            std::cout << "title=";
            getline(std::cin, title);
            std::cout << "author=";
            getline(std::cin, author);
            std::cout << "genre=";
            getline(std::cin, genre);
            std::cout << "publisher=";
            getline(std::cin, publisher);
            std::cout << "page_count=";
            getline(std::cin, page_count);

            json payload = {
                {"title", title},
                {"author", author},
                {"genre", genre},
                {"publisher", publisher},
                {"page_count", page_count},
            };

            auto request = Request("POST", "/api/v1/tema/library/books", payload, cookie, jwt);
            send_request(request.to_string());
        }
        else if (command == "delete_book")
        {
            std::string id;
            std::cout << "id=";
            getline(std::cin, id);
            auto request = Request("DELETE", "/api/v1/tema/library/books", cookie, jwt, id);
            send_request(request.to_string());
        }
        else if (command == "logout")
        {
            auto request = Request("GET", "/api/v1/tema/auth/logout", cookie);
            cookie = "";
            jwt = "";
            send_request(request.to_string());
        }
        else
        {
            if (command != "help")
            {
                std::cout << "Unknown command: " << command << std::endl;
            }
            std::cout << "Available commands:" << std::endl;
            std::cout << "register" << std::endl;
            std::cout << "login" << std::endl;
            std::cout << "enter_library" << std::endl;
            std::cout << "get_books" << std::endl;
            std::cout << "get_book" << std::endl;
            std::cout << "add_book" << std::endl;
            std::cout << "delete_book" << std::endl;
            std::cout << "logout" << std::endl;

            std::cout << "help" << std::endl;
            std::cout << "exit" << std::endl;
        }
    }

    void Session::send_request(const std::string &request)
    {
        client.get()->reconnect();
        client.get()->send_request(request);
        auto response = client.get()->receive_response();
        if (response.get_status_code() >= 200 && response.get_status_code() < 300)
        {
            std::cout << response.get_status_code() << " " << response.get_status_message() << std::endl;
            auto headers = response.get_headers();
            if (headers.find("\nSet-Cookie") != headers.end())
            {
                cookie = headers["\nSet-Cookie"];
                size_t pos = cookie.find(';');
                cookie = cookie.substr(0, pos);
            }
            std::string body = response.get_body();
            int arr_flag = 0;
            if (body != "\n")
            {
                if (body[1] == '[')
                {
                    arr_flag = 1;
                }
                if (arr_flag == 0)
                {
                    json response_body = json::parse(body);
                    if (response_body.find("token") != response_body.end())
                    {
                        jwt = response_body["token"];
                    }
                    else
                    {
                        std::string title = response_body["title"];
                        title = title.substr(0, title.length());
                        std::cout << "title: " << title << std::endl;

                        std::string author = response_body["author"];
                        author = author.substr(0, author.length());
                        std::cout << "author: " << author << std::endl;

                        std::string publisher = response_body["publisher"];
                        publisher = publisher.substr(0, publisher.length());
                        std::cout << "publisher: " << publisher << std::endl;

                        std::string genre = response_body["genre"];
                        genre = genre.substr(0, genre.length());
                        std::cout << "genre: " << genre << std::endl;

                        std::cout << "page_count: " << response_body["page_count"] << std::endl;
                    }
                }
                else if (arr_flag == 1)
                {
                    json books_json = json::parse(body);
                    for (auto book : books_json)
                    {
                        std::cout << "id: " << book["id"] << std::endl;
                        std::cout << "title: " << book["title"] << std::endl;
                    }
                }
            }
        }
        else if (response.get_status_code() >= 400 && response.get_status_code() < 500)
        {
            std::string body = response.get_body();
            json response_body = json::parse(body);
            std::cout << response_body["error"] << std::endl;
        }
        else if (response.get_status_code() >= 500 && response.get_status_code() < 600)
        {
            std::cout << "Server error" << std::endl;
        }
        else
        {
            std::cout << "Unknown error" << std::endl;
        }
    }

} // namespace ClientLib
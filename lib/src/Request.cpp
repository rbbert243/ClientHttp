#include <Request.hpp>
#include <iostream>

#define CRLF "\r\n"
#define HOST "Host: 34.254.242.81:8080" CRLF

namespace ClientLib
{

    Request::Request(const std::string &method, const std::string &path, const json &payload) : method(method), path(path), payload(payload) {}

    Request::Request(const std::string &method, const std::string &path, const std::string &cookie) : method(method), path(path), cookie(cookie) {}

    Request::Request(const std::string &method, const std::string &path, const std::string &cookie, const std::string &jwt) : method(method), path(path), cookie(cookie), jwt(jwt) {}

    Request::Request(const std::string &method, const std::string &path, const std::string &cookie, const std::string &jwt, const std::string &id) : method(method), path(path), cookie(cookie), jwt(jwt), id(id) {}

    Request::Request(const std::string &method, const std::string &path, const json payload, const std::string &cookie, const std::string &jwt) : method(method), path(path), payload(payload), cookie(cookie), jwt(jwt) {}

    Request::~Request() = default;

    std::string Request::to_string() const
    {
        std::string request;
        if (id == "-1")
        {
            request = method + " " + path + " HTTP/1.1" CRLF;
        }
        else
        {
            request = method + " " + path + "/" + id + " HTTP/1.1" CRLF;
        }
        request += HOST;
        if (method == "POST")
        {
            if (jwt != "")
            {
                request += "Authorization: Bearer " + jwt + CRLF;
            }
            request += "Content-Type: application/json" CRLF;
            if (cookie != "")
            {
                request += "Cookie: " + cookie + CRLF;
            }
            request += "Content-Length: " + std::to_string(payload.dump().length()) + CRLF;
            request += CRLF;
            request += payload.dump();
        }
        else if (method == "GET")
        {
            request += "Cookie: " + cookie + CRLF;
            if (jwt != "")
            {
                request += "Authorization: Bearer " + jwt + CRLF;
            }
            request += CRLF;
        }
        else if (method == "DELETE")
        {
            request += "Authorization: Bearer " + jwt + CRLF;
            request += "Cookie: " + cookie + CRLF;
            request += CRLF;
        }
        else
        {
            std::cout << "Unknown method: " << method << std::endl;
        }

        return request;
    }

} // namespace ClientLib
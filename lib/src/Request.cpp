#include <Request.hpp>

#define CRLF "\r\n"
#define HOST "Host: 34.254.242.81:8080" CRLF

namespace ClientLib
{

    Request::Request(const std::string &method, const std::string &path, const json &payload) : method(method), path(path), payload(payload) {}

    Request::~Request() = default;

    std::string Request::to_string() const
    {
        std::string request = method + " " + path + " HTTP/1.1" CRLF;
        request += HOST;
        if (method == "POST")
        {
            request += "Content-Type: application/json" CRLF;
            request += "Content-Length: " + std::to_string(payload.dump(2).length() + 1) + CRLF;
            request += CRLF;
            request += payload.dump();
            request += CRLF;
        }
        else
        {
            request += CRLF;
        }

        return request;
    }

} // namespace ClientLib
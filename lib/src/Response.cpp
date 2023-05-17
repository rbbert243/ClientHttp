#include <Response.hpp>
#include <sstream>
#include <vector>

namespace ClientLib
{

    Response::Response(const std::string &response)
    {
        std::istringstream response_stream(response);

        std::getline(response_stream, http_version, ' ');
        response_stream >> status_code;
        std::getline(response_stream, status_message, '\r');
        response_stream.ignore(1);

        std::string header_line;
        while (std::getline(response_stream, header_line, '\r'))
        {
            if (header_line == "\n")
            {
                break;
            }

            std::string key;
            std::string value;
            std::istringstream header_stream(header_line);
            std::getline(header_stream, key, ':');
            header_stream.ignore(1);
            std::getline(header_stream, value, '\r');
            header_stream.ignore(1);

            headers[key] = value;
        }

        std::getline(response_stream, body, '\0');
    }

    Response::~Response() = default;

    const std::string &Response::get_http_version() const
    {
        return http_version;
    }

    int Response::get_status_code() const
    {
        return status_code;
    }

    const std::string &Response::get_status_message() const
    {
        return status_message;
    }
    const std::unordered_map<std::string, std::string> &Response::get_headers() const
    {
        return headers;
    }

    const std::string &Response::get_body() const
    {
        return body;
    }

} // namespace ClientLib
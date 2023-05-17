#pragma once

#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace ClientLib
{
    class Request
    {
    private:
        std::string method;
        std::string path;
        json payload;
        std::string cookie;

    public:
        Request(const std::string &method, const std::string &path, const json &payload);
        Request(const std::string &method, const std::string &path, const std::string &cookie);
        ~Request();
        std::string to_string() const;
    };

} // namespace ClientLib

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
        std::string jwt;
        std::string id = "-1";

    public:
        Request(const std::string &method, const std::string &path, const json &payload);
        Request(const std::string &method, const std::string &path, const std::string &cookie);
        Request(const std::string &method, const std::string &path, const std::string &cookie, const std::string &jwt);
        Request(const std::string &method, const std::string &path, const std::string &cookie, const std::string &jwt, const std::string &id);
        Request(const std::string &method, const std::string &path, const json payload, const std::string &cookie, const std::string &jwt);
        ~Request();
        std::string to_string() const;
    };

} // namespace ClientLib

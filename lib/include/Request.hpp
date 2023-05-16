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

    public:
        Request(const std::string &method, const std::string &path, const json &payload);
        ~Request();
        std::string to_string() const;
    };

} // namespace ClientLib

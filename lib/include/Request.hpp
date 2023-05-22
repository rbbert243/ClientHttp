#pragma once

#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace ClientLib
{
    /**
     * @brief A class representing a request to be sent to a server.
     */
    class Request
    {
    private:
        std::string method; /**< The HTTP method of the request. */
        std::string path; /**< The path of the request. */
        json payload; /**< The payload of the request, if any. */
        std::string cookie; /**< The cookie to include in the request, if any. */
        std::string jwt; /**< The JWT to include in the request, if any. */
        std::string id = "-1"; /**< The ID of the request, if any. */

    public:
        /**
         * @brief Constructs a new Request object with a payload.
         * 
         * @param method The HTTP method of the request.
         * @param path The path of the request.
         * @param payload The payload of the request.
         */
        Request(const std::string &method, const std::string &path, const json &payload);

        /**
         * @brief Constructs a new Request object with a cookie.
         * 
         * @param method The HTTP method of the request.
         * @param path The path of the request.
         * @param cookie The cookie to include in the request.
         */
        Request(const std::string &method, const std::string &path, const std::string &cookie);

        /**
         * @brief Constructs a new Request object with a cookie and JWT.
         * 
         * @param method The HTTP method of the request.
         * @param path The path of the request.
         * @param cookie The cookie to include in the request.
         * @param jwt The JWT to include in the request.
         */
        Request(const std::string &method, const std::string &path, const std::string &cookie, const std::string &jwt);

        /**
         * @brief Constructs a new Request object with a cookie, JWT, and ID.
         * 
         * @param method The HTTP method of the request.
         * @param path The path of the request.
         * @param cookie The cookie to include in the request.
         * @param jwt The JWT to include in the request.
         * @param id The ID of the request.
         */
        Request(const std::string &method, const std::string &path, const std::string &cookie, const std::string &jwt, const std::string &id);

        /**
         * @brief Constructs a new Request object with a payload, cookie, and JWT.
         * 
         * @param method The HTTP method of the request.
         * @param path The path of the request.
         * @param payload The payload of the request.
         * @param cookie The cookie to include in the request.
         * @param jwt The JWT to include in the request.
         */
        Request(const std::string &method, const std::string &path, const json payload, const std::string &cookie, const std::string &jwt);

        /**
         * @brief Destroys the Request object.
         */
        ~Request();

        /**
         * @brief Converts the Request object to a string.
         * 
         * @return The string representation of the Request object.
         */
        std::string to_string() const;
    };

} // namespace ClientLib
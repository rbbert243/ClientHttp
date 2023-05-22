#pragma once

#include <string>
#include <unordered_map>

namespace ClientLib
{

    /**
     * @brief A class representing a response received from a server.
     */
    class Response
    {
    private:
        std::string http_version; /**< The HTTP version of the response. */
        int status_code; /**< The HTTP status code of the response. */
        std::string status_message; /**< The HTTP status message of the response. */
        std::unordered_map<std::string, std::string> headers; /**< The headers of the response. */
        std::string body; /**< The body of the response. */

    public:
        /**
         * @brief Constructs a new Response object from a string.
         * 
         * @param response The string representation of the response.
         */
        explicit Response(const std::string &response);

        /**
         * @brief Destroys the Response object.
         */
        ~Response();

        /**
         * @brief Gets the HTTP version of the response.
         * 
         * @return The HTTP version of the response.
         */
        const std::string &get_http_version() const;

        /**
         * @brief Gets the HTTP status code of the response.
         * 
         * @return The HTTP status code of the response.
         */
        int get_status_code() const;

        /**
         * @brief Gets the HTTP status message of the response.
         * 
         * @return The HTTP status message of the response.
         */
        const std::string &get_status_message() const;

        /**
         * @brief Gets the headers of the response.
         * 
         * @return The headers of the response.
         */
        const std::unordered_map<std::string, std::string> &get_headers() const;

        /**
         * @brief Gets the body of the response.
         * 
         * @return The body of the response.
         */
        const std::string &get_body() const;
    };

} // namespace ClientLib
#pragma one

#include <string>
#include <unordered_map>

namespace ClientLib
{

    class Response
    {
    private:
        std::string http_version;
        int status_code;
        std::string status_message;
        std::unordered_map<std::string, std::string> headers;
        std::string body;

    public:
        explicit Response(const std::string &response);
        ~Response();
        const std::string &get_http_version() const;
        int get_status_code() const;
        const std::string &get_status_message() const;
        const std::unordered_map<std::string, std::string> &get_headers() const;
        const std::string &get_body() const;
    };

} // namespace ClientLib
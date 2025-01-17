#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;

// Structure to hold the parsed CSV data
struct RoadData
{
    std::string landmark_a_id;
    std::string landmark_b_id;
    std::string time;
};

// Function to parse CSV into a vector of RoadData structs
std::vector<RoadData> parse_csv(const std::string &file_path)
{
    std::vector<RoadData> data;
    std::ifstream file(file_path);
    std::string line;

    // Skip header
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string landmark_a_id, landmark_b_id, time;

        std::getline(ss, landmark_a_id, ',');
        std::getline(ss, landmark_b_id, ',');
        std::getline(ss, time, ',');

        data.push_back({landmark_a_id, landmark_b_id, time});
    }

    return data;
}

// Function to convert parsed CSV to JSON
std::string csv_to_json(const std::vector<RoadData> &data)
{
    std::ostringstream oss;
    oss << "[";

    for (size_t i = 0; i < data.size(); ++i)
    {
        const auto &entry = data[i];
        if (i > 0)
            oss << ", ";

        oss << "{"
            << "\"Landmark_A_ID\": \"" << entry.landmark_a_id << "\", "
            << "\"Landmark_B_ID\": \"" << entry.landmark_b_id << "\", "
            << "\"Time\": \"" << entry.time << "\""
            << "}";
    }

    oss << "]";
    return oss.str();
}

// Function to convert parsed CSV to XML
std::string csv_to_xml(const std::vector<RoadData> &data)
{
    std::ostringstream oss;
    oss << "<rows>";

    for (const auto &entry : data)
    {
        oss << "<row "
            << "Landmark_A_ID=\"" << entry.landmark_a_id << "\" "
            << "Landmark_B_ID=\"" << entry.landmark_b_id << "\" "
            << "Time=\"" << entry.time << "\"/>";
    }

    oss << "</rows>";
    return oss.str();
}

// Function to send file content as JSON or XML based on the Accept header
void send_response(beast::tcp_stream &stream, const std::string &file_path, http::request<http::string_body> &req)
{
    std::vector<RoadData> data = parse_csv(file_path);

    // Prepare the response based on the "Accept" header
    std::string accept(req[http::field::accept].data(), req[http::field::accept].size());

    http::response<http::string_body> res;
    if (accept == "application/json")
    {
        std::string json_data = csv_to_json(data);
        res = http::response<http::string_body>(http::status::ok, req.version());
        res.set(http::field::server, "Boost.Beast");
        res.set(http::field::content_type, "application/json");
        res.body() = json_data;
    }
    else if (accept == "application/xml")
    {
        std::string xml_data = csv_to_xml(data);
        res = http::response<http::string_body>(http::status::ok, req.version());
        res.set(http::field::server, "Boost.Beast");
        res.set(http::field::content_type, "application/xml");
        res.body() = xml_data;
    }
    else
    {
        // Default to JSON if no acceptable format is specified
        std::string json_data = csv_to_json(data);
        res = http::response<http::string_body>(http::status::ok, req.version());
        res.set(http::field::server, "Boost.Beast");
        res.set(http::field::content_type, "application/json");
        res.body() = json_data;
    }

    res.prepare_payload();
    http::write(stream, res);
}

int main()
{
    try
    {
        const std::string file_path = "USA-roads.csv";

        net::io_context ioc;
        net::ip::tcp::acceptor acceptor(ioc, {net::ip::tcp::v4(), 8080});
        acceptor.set_option(net::socket_base::reuse_address(true));

        std::cout << "Server listening on port 8080...\n";

        while (true)
        {
            // Create a new socket for each connection
            net::ip::tcp::socket socket(ioc);

            // Accept a connection
            acceptor.accept(socket);

            try
            {
                // Convert the socket to a tcp_stream
                beast::tcp_stream stream(std::move(socket));

                // Read the request
                beast::flat_buffer buffer;
                http::request<http::string_body> req;
                http::read(stream, buffer, req);

                std::cout << "Received request: " << req << "\n";

                // Send the file content as JSON or XML based on the Accept header
                send_response(stream, file_path, req);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error handling request: " << e.what() << "\n";
            }

            // Shutdown and close the socket after handling the request
            beast::error_code ec;
            socket.shutdown(net::ip::tcp::socket::shutdown_send, ec);
            if (ec && ec != beast::errc::not_connected)
            {
                std::cerr << "Socket shutdown error: " << ec.message() << "\n";
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

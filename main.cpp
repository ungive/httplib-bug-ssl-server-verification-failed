#include <clocale>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include <httplib.h>

int main() {
    httplib::Client cli("https://accounts.spotify.com");
    auto result = cli.Get("/api/token");
    if (result.error() != httplib::Error::Success) {
        std::cerr << "Request failed: "
            << httplib::to_string(result.error())
            << " ssl_error=" << result.ssl_error()
            << " ssl_backend_error=" << result.ssl_backend_error()
            << std::endl;
    } else {
        std::cerr << "OK" << std::endl;
    }
#ifdef NDEBUG
    std::cin.get();
#endif
    return 0;
}

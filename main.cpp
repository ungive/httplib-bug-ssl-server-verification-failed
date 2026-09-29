#include <clocale>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include <httplib.h>
#include <cpr/cpr.h>

void test_httplib() {
    std::cerr << "test_httplib()..." << std::endl;
    httplib::Client cli("https://accounts.spotify.com");
    // Windows certificate verification does not work:
    cli.enable_windows_certificate_verification(true);
    // Works when using a recent CA bundle:
    // Downloaded from: https://curl.se/docs/caextract.html
    // cli.set_ca_cert_path("C:\\Users\\User\\Downloads\\cacert-2026-09-25.pem");
    auto result = cli.Get("/api/token");
    if (result.error() != httplib::Error::Success) {
        std::cerr << "httplib: Request failed: "
            << httplib::to_string(result.error())
            << " ssl_error=" << result.ssl_error()
            << " ssl_backend_error=" << result.ssl_backend_error()
            // Use this when testing with some older versions of httplib:
            // << " ssl_openssl_error=" << result.ssl_openssl_error()
            << std::endl;
    } else {
        std::cerr << "httplib: OK" << std::endl;
    }
}

void test_libcpr() {
    std::cerr << "test_libcpr()..." << std::endl;
    cpr::Response result = cpr::Get(
        cpr::Url{std::string("https://accounts.spotify.com") + "/api/token"});
    if (result.error.code != cpr::ErrorCode::OK) {
        std::cerr << "libcpr: Request failed: "
            << result.error.message << std::endl;
    } else {
        std::cerr << "libcpr: OK" << std::endl;
    }
}

int main() {
    test_httplib();
    test_libcpr();
#ifdef NDEBUG
    std::cin.get();
#endif
    return 0;
}

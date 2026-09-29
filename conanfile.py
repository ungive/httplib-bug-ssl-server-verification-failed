from conan import ConanFile


class MusicPresence(ConanFile):
    name = "httplib-bug-ssl-server-verification-failed"
    author = "Jonas van den Berg"
    version = "0.1"  # FIXME

    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    requires = (
        "openssl/[~3.5]",
        "cpr/[~1.14]",
    )

    tool_requires = "cmake/3.31.6"

    options = {"shared": [False]}
    default_options = {"shared": False}

    def configure(self):
        self.options["openssl"].shared = True

        if self.settings.os == "Macos":
            self.options["openssl"].openssldir = "/etc/ssl"

        self.options["cpp-httplib"].with_openssl = True

    def layout(self):
        cmake_layout(self, src_folder="src")

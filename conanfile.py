import os
import importlib.util

from conan import ConanFile
from conan.errors import ConanException
from conan.tools.cmake import cmake_layout


class MusicPresence(ConanFile):
    name = "httplib-bug-ssl-server-verification-failed"
    author = "Jonas van den Berg"
    version = "0.1"  # FIXME

    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    requires = (
        # LTS version until 7 September 2026
        # Distros such a Mint ship with libssl3.0
        "openssl/[~3.0]",
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

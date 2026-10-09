# httplib-bug-ssl-server-verification-failed

## Related issues:

- https://github.com/yhirose/cpp-httplib/issues/2596 (resolved)
- https://github.com/libcpr/cpr/issues/1325

## Dependencies

- Conan CLI (package manager, for OpenSSL)
- OpenSSL v3.*
- cpp-httplib v0.58.0
- libcpr (libcurl) v1.4.* (for comparison)

## Building

```
git clone ...
git submodule update --init --recursive
make dev-win  # Installs OpenSSL
cmake -S . -B build/windows-msvc-debug --preset windows-msvc-debug
cmake --build --preset windows-msvc-debug
```

## Running

```
.\build\windows-msvc-debug\Debug\main.exe
test_httplib()... version: 0.60.1
httplib: OK
test_libcpr()... version: 1.14.2
libcpr: Request failed: SSL certificate problem: unable to get local issuer certificat
```

(Note that the bug has been fixed in cpp-httplib since version 0.59.0)

# httplib-bug-encode-query-component-isalnum

## Dependencies

- Conan CLI (package manager, for OpenSSL)
- 

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
Request failed: SSL server verification failed ssl_error=0 ssl_backend_error=20
```

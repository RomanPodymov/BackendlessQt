# BackendlessQt

BackendlessQt is a Qt-based client library for integrating applications with the Backendless backend platform. It provides convenient access to backend services such as user management, data storage, messaging, and cloud functionality from C++/Qt applications.

Built with the power of the Qt Framework, the library is designed for cross-platform desktop and mobile development.

## Features

- Qt/C++ API for Backendless services
- Cross-platform support
  - Windows
  - Linux
  - macOS
  - Android
  - iOS
- REST API integration
- User registration and authentication
- Data persistence and querying
- Messaging and real-time communication
- Asynchronous networking support using Qt
- Easy integration into existing Qt projects

## Requirements

- Qt 5.x or Qt 6.x
- C++17 compatible compiler
- CMake or qmake
- Internet connection for Backendless API access

## Installation

### Clone the repository

```bash
git clone https://github.com/RomanPodymov/BackendlessQt.git
cd BackendlessQt
```

### Using CMake

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Using qmake

```bash
qmake
make
```

## Project Structure

```text
BackendlessQt/
├── src/          # Library source files
├── include/      # Public headers
├── examples/     # Example applications
├── tests/        # Unit tests
└── docs/         # Documentation
```

## Quick Start

### Initialize Backendless

```cpp
#include <Backendless.h>

int main()
{
    Backendless backendless;

    backendless.initApp(
        "YOUR-APPLICATION-ID",
        "YOUR-API-KEY"
    );

    return 0;
}
```

### User Registration Example

```cpp
BackendlessUser user;

user.setProperty("email", "user@example.com");
user.setPassword("password");

backendless.userService().registerUser(
    user,
    [](const BackendlessUser& registeredUser)
    {
        qDebug() << "User registered successfully";
    },
    [](const BackendlessFault& fault)
    {
        qDebug() << "Registration failed:" << fault.message();
    }
);
```

## Documentation

- Backendless Platform: https://backendless.com/
- Qt Documentation: https://doc.qt.io/

## Examples

Example applications can be found in the `examples/` directory. They demonstrate:

- User authentication
- Database operations
- Real-time messaging
- File upload/download
- Cloud code integration

## Contributing

Contributions are welcome.

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push the branch
5. Open a pull request

## License

This project is licensed under the MIT License unless stated otherwise in the repository.

## Repository

https://github.com/RomanPodymov/BackendlessQt


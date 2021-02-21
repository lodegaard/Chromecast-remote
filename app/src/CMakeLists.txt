
add_executable(cast-remote main.cpp ChromecastRemoteRunner.cpp)
target_link_libraries(cast-remote device keyboarddevice publisher CONAN_PKG::asio)
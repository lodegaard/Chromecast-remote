
add_library(publisher
    EventSerializer.cpp
    Publisher.cpp)
target_link_libraries(publisher CONAN_PKG::asio CONAN_PKG::nlohmann_json keyboarddevice)
target_include_directories(publisher PUBLIC ../include)
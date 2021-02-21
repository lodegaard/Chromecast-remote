add_executable(EventSerializerTests EventSerializerTests.cpp)
target_link_libraries(EventSerializerTests CONAN_PKG::gtest CONAN_PKG::nlohmann_json publisher)
target_include_directories(EventSerializerTests PUBLIC ../src)

add_test(NAME EventSerializer_Tests COMMAND EventSerializerTests)
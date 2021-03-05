set(EventSerializerTestsSources EventSerializerTests.cpp)

add_gtest(EventSerializerTests
    SOURCES "${EventSerializerTestsSources}"
    INCLUDES ../src
    DEPS CONAN_PKG::nlohmann_json publisher)
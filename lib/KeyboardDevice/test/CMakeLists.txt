set(KeyboardDeviceTestSources KeyboardDeviceListTests.cpp KeyboardDeviceHandlerTests.cpp RemotePresenterTests.cpp)

add_gtest(KeyboardDeviceTestss 
    SOURCES "${KeyboardDeviceTestSources}" 
    INCLUDES ../src 
    DEPS keyboarddevice
)

add_library(keyboarddevice 
    KeyboardDeviceList.cpp 
    KeyboardDeviceHandler.cpp 
    PosixStreamWrapper.cpp
    RemotePresenter.cpp 
    StreamWrapper.cpp)
target_link_libraries(keyboarddevice device CONAN_PKG::asio)
target_include_directories(keyboarddevice PUBLIC ../include)
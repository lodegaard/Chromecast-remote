
add_library(device Device.cpp DeviceHandler.cpp InputEvent.cpp)
target_include_directories(device PUBLIC ../include)
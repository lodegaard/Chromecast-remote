///

#include <asio.hpp>
#include <iostream>
#include <memory>

#include "ChromecastRemoteRunner.h"

using namespace std;

int main()
{
    cout << "Starting Chromecast remote\n";
    ChromecastRemoteRunner runner("192.168.0.83", 9999);
    runner.run();

    return 0;
}
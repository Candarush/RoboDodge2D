#pragma once
#include "influxdb.hpp"
#include <iostream>
#include <string>

using namespace std;

namespace RoboDodge
{
    class DBclient
    {
        influxdb_cpp::server_info* serverinfo;
    public:
        DBclient(string host, int port, string dbname);
        void SendPosition(string tag, float x, float y);
    };
}

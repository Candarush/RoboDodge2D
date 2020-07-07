#include "DBclient.hpp"

namespace RoboDodge
{
    DBclient::DBclient(string host, int port, string dbname)
    {
        string response;
        serverinfo = new influxdb_cpp::server_info(host,port,dbname);
        influxdb_cpp::create_db(response, dbname, *serverinfo);
        
    }

    void DBclient::SendPosition(string tag, float x, float y)
    {
        string response;
        int ret = influxdb_cpp::builder()
            .meas("RoboDodge2D")
        .tag("tag",tag)
        .field("x",x)
        .field("y",y)
        .post_http(*serverinfo,&response);
    }
}

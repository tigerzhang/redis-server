/*
* ----------------------------------------------------------------------------
* Copyright (c) 2015-2016, xSky <guozhw@gmail.com>
* All rights reserved.
* Distributed under GPL license.
* ----------------------------------------------------------------------------
*/

#include <unistd.h>
#include "../src/RedisServerLib.h"

class RedisConnect :public RedisConnectorBase
{
public:
    RedisConnect();
    ~RedisConnect();
private:
};

std::map<std::string, std::string> kvmap;

class RedisServer :public RedisServerBase
{
public:
    RedisServer() {

    }
    ~RedisServer() {

    }

public:
    bool Init()
    {
        CmdRegister();
    }

private:
    bool CmdRegister()
    {
        if (!SetCmdTable("get", (CmdCallback) &RedisServer::ProcessCmdGet)) return false;
        if (!SetCmdTable("set", (CmdCallback)&RedisServer::ProcessCmdSet)) return false;
        return true;
    }

    void ProcessCmdGet(RedisConnect *pConnector)
    {
        if (2 != pConnector->argc) {
            SendErrReply(pConnector, "ERR", "error arg");
            return;
        }
        auto k = kvmap.find(pConnector->argv[1]);
        if (k == kvmap.end()) {
            SendErrReply(pConnector, "ERR", "not found");
            return;
        }
        SendBulkReply(pConnector, k->second.c_str());
        return;
    }

    void ProcessCmdSet(RedisConnect *pConnector) {
        if (3 != pConnector->argc) {
            SendErrReply(pConnector, "cmd error:", "error arg");
            return;
        }
        kvmap[pConnector->argv[1]] = pConnector->argv[2];
        SendStatusReply(pConnector, "OK");
        return;
    }

private:

};

int main(int argc, char **argv)
{
    RedisServer redis;
    redis.Init();
    string pass = "shahe22f";
    redis.SetPassword(pass);
    redis.Start("127.0.0.1", 6479);

    while (1) {
        usleep(1000);
    }
    
    return 0;
}


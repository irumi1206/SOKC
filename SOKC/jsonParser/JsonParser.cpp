#include <iostream>
#include <jsoncpp/json/json.h>
#include "JsonParser.h"


Json::Value toJson(std::string str)
{
    Json::Reader reader;
    Json::Value root;
    bool parsedSuccess = reader.parse(str, root, false);
    if(not parsedSuccess)
    {
        return -1;
    }

    return root;
}
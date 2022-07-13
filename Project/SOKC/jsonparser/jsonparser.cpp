#include <iostream>
// #include "jsoncpp/dist/json/json.h"
// #include "jsoncpp/dist/json/json-forwards.h"
// #include "jsoncpp/dist/jsoncpp.cpp"
#include <jsoncpp/json/json.h>

// class jsonOb
// {
// private:
//     bool parsedSuccess;
//     Json::Reader reader;
//     Json::Value root;
// public:
//     jsonOb(string str){
//         this->parsedSuccess = reader.parse(str, root, false);
//         if(not parsedSuccess)
//         {
//             cout<<"fail to parse json"<<endl;
//         }
//     }
//     bool isValid(){
//         return parsedSuccess;
//     }
//     Json::Value toJson(){
//         return root;
//     }
//     string toString(){
//         return root.toStyledString();
//     }

// };

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

std::string toString(Json::Value data){
    return data.toStyledString();
}
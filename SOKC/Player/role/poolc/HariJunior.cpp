#include "HariJunior.h"

Json::Value HariJunior::userAbility(Json::Value data){
    Json::Value out;
    out["toAll"]=data;
    return out;
}
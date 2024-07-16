#include "DBManager.hpp"
#include "../igcommon.h"

namespace IG {

DBManager::DBManager()
{
    init();
}

DBManager::~DBManager()
{
}

void DBManager::init()
{
    dbOpen();
    spdlog::debug("Before instantiating game data");
    profile = new IG::Profile(dbInstance);
    profile->init();

    idleGenerators = new IG::Generator(dbInstance);
    idleGenerators->init();

}

void DBManager::dbOpen()
{
    sqlite3_open("db/app.db", &dbInstance);
}

void DBManager::dbClose() 
{
    sqlite3_close(dbInstance);
}

void DBManager::exec(std::string pSql, int (*callback)(void*,int,char**,char**), void *param)
{
    char* err = NULL;
    sqlite3_exec(dbInstance, pSql.c_str(), callback, param, &err);
}

}

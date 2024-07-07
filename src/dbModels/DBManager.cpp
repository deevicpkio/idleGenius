#include "DBManager.hpp"

DBManager::DBManager()
{
    init();
}

DBManager::~DBManager()
{
    sqlite3_close(dbInstance);
}

void DBManager::init()
{
    sqlite3_open("db/app.db", &dbInstance);
}

void DBManager::exec(std::string pSql, int (*callback)(void*,int,char**,char**), void *param)
{
    char* err = NULL;
    sqlite3_exec(dbInstance, pSql.c_str(), callback, param, &err);
}


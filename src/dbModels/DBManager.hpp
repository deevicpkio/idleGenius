#ifndef IG_DB_MANAGER
#define IG_DB_MANAGER
#include <string>
#include <sqlite3.h>

class DBManager {
public:
	DBManager();
	~DBManager();

	void exec(std::string pSql, int (*callback)(void*,int,char**,char**), void *param);

private:
	sqlite3* dbInstance;
	void init();
};

#endif

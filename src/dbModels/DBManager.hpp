#ifndef IG_DB_MANAGER
#define IG_DB_MANAGER
#include <string>
#include <sqlite3.h>
#include "ProfileModel.hpp"
#include "GeneratorModel.hpp"

namespace IG
{
class DBManager {
public:
	DBManager();
	~DBManager();

	void exec(std::string pSql, int (*callback)(void*,int,char**,char**), void *param);
	ProfileEntry getProfileData() { return profile->getData(); }
	std::vector<GeneratorEntry> getGenerators() { return idleGenerators->getData(); }
	int generatorCount() { return idleGenerators->count(); }

private:
	sqlite3* dbInstance;
	Profile* profile;
	Generator* idleGenerators;
	
	void init();
	void dbOpen();
	void dbClose();
};
}
#endif

#ifndef IG_PROFILE_MODEL
#define IG_PROFILE_MODEL
#pragma once

#include <string>
#include <sqlite3.h>

namespace IG
{

typedef struct {
	int id;
	std::string user_name;
	int rank_id;
	float current_exp;
	double prestige;
	double lifetime_currency;
	double wealth;
	double current_gold;
	std::string last_update;
	double manual_labor_gpc;
	
} ProfileEntry;

	
class Profile {
public:
	Profile(sqlite3* pDB);
	void init();
	ProfileEntry getData();
	void setData(ProfileEntry pNewEntry);
	void update(float deltaTime);

private:
	sqlite3* dbInstance;
	ProfileEntry data;

	void readDB();
};
}

#endif

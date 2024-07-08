#include "ProfileModel.hpp"
#include "../igcommon.h"

namespace IG {

    static int fProfile(void *a_param, int argc, char **argv, char **column){
        spdlog::debug("Entered profileCallback - ID: {}", argv[0]);
        IG::Profile* caller = static_cast<IG::Profile*>(a_param);
        ProfileEntry newEntry;

        for (int i=0; i< argc; i++) {
            if (strcmp(column[i], "id") == 0) {
                newEntry.id = std::stoi(argv[i]); 
            }
            if (strcmp(column[i], "user_name") == 0) {
                newEntry.user_name = argv[i]; 
            }
            if (strcmp(column[i], "rank_id") == 0) {
                newEntry.rank_id = std::stof(argv[i]); 
            }
            if (strcmp(column[i], "current_exp") == 0) {
                newEntry.current_exp = std::stof(argv[i]); 
            }
            if (strcmp(column[i], "prestige") == 0) {
                newEntry.prestige = std::stof(argv[i]);
            }
            if (strcmp(column[i], "lifetime_currency") == 0) {
                newEntry.lifetime_currency = std::stof(argv[i]);
            }
            if (strcmp(column[i], "wealth") == 0) {
                newEntry.wealth = std::stof(argv[i]);
            }
            if (strcmp(column[i], "current_gold") == 0) {
                newEntry.current_gold = std::stof(argv[i]); 
            }
            if (strcmp(column[i], "manual_labor_gpc") == 0) {
                newEntry.manual_labor_gpc = (int)std::stof(argv[i]);
            }
        }
        
        caller->setData(newEntry);
        
    return 0;
    }

    IG::Profile::Profile(DBManager* pDB) {
        db = pDB;
    }

    void IG::Profile::init()
    {
        readDB();
    }

    void IG::Profile::readDB() {

        std::string sql = "SELECT * FROM profile;";
        char* err = NULL;
        spdlog::debug("Before executing Profile SQL statement");
	db->exec(sql, IG::fProfile, this);
        
        spdlog::debug("Profile found");
        spdlog::debug("\nID: {0}\n - name {1}\n", 
		      data.id, data.user_name);
    }

    ProfileEntry IG::Profile::getData() {
        return data;
    }
    
    void IG::Profile::setData(ProfileEntry pNewEntry)
    {
	data = pNewEntry;
    }
}

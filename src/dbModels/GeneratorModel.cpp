#include "GeneratorModel.hpp"
#include <vector>
#include "../igcommon.h"

namespace IG {
    static int fGeneratorIdle(void *a_param, int argc, char **argv, char **column){
        spdlog::debug("Entered generatorCallback - ID: {}", argv[0]);
        IG::Generator* caller = static_cast<IG::Generator*>(a_param);
        GeneratorEntry newEntry;

        for (int i=0; i< argc; i++) {
            if (strcmp(column[i], "id") == 0) {
                newEntry.id = std::stoi(argv[i]); 
            }
            if (strcmp(column[i], "name") == 0) {
                newEntry.name = argv[i]; 
            }
            if (strcmp(column[i], "icon") == 0) {
                newEntry.icon = std::stoi(argv[i]); 
            }
            if (strcmp(column[i], "base_cost") == 0) {
                newEntry.base_cost = std::stof(argv[i]); 
            }
            if (strcmp(column[i], "level_mod") == 0) {
                newEntry.level_mod = std::stof(argv[i]);
            }
            if (strcmp(column[i], "gold_per_sec") == 0) {
                newEntry.gold_per_sec = std::stof(argv[i]);
            }
            if (strcmp(column[i], "order_weight") == 0) {
                newEntry.order_weight = std::stof(argv[i]);
            }
            if (strcmp(column[i], "upgrade_cost_mod") == 0) {
                newEntry.upgrade_cost_mod = std::stof(argv[i]); 
            }
            if (strcmp(column[i], "curr_level") == 0) {
                newEntry.curr_level = (int)std::stoi(argv[i]);
            }
            if (strcmp(column[i], "upgrade_cost") == 0) {
                newEntry.upgrade_cost = std::stof(argv[i]); 
            }
        }
        
        caller->addGenerator(newEntry);
        
    return 0;
    }

    IG::Generator::Generator(DBManager* pDB) {
        db = pDB;
    }

    void IG::Generator::init()
    {
        readDB();
    }

    void IG::Generator::readDB() {

        std::string sql = "SELECT * FROM idlegenerator;";
        spdlog::debug("Before executing Idle Generator SQL statement");
	db->exec(sql, IG::fGeneratorIdle, this);
        
        spdlog::debug("Generators found: {0}", data.size());
        
        for (auto gen : data) {
            spdlog::debug("\nID: {1}\nName: {0} | icon: {2} - gold/sec: {3} - level mod {4} \nbase cost {5} - upgrade cost mod {6} - order weight {7} - current level {8} - upgrade cost {9}\n", 
                         gen.name, gen.id, gen.icon, gen.gold_per_sec, gen.level_mod, gen.base_cost, gen.upgrade_cost_mod, gen.order_weight, gen.curr_level, gen.upgrade_cost);
        }
    }

    void IG::Generator::addGenerator(GeneratorEntry pNewGenerator) {
        data.push_back(pNewGenerator);
    }
    
    const int IG::Generator::count() {
        return data.size();
    }    

    std::vector<GeneratorEntry> IG::Generator::getData() {
        return data;
    }
}

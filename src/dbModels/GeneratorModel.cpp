#include "GeneratorModel.hpp"
#include <spdlog/spdlog.h>
#include <map>
#include <vector>

namespace IG {
	enum EmojiId {
		BANK = 1,
		CHART = 2,
		COFFEE = 3,
		WORK = 4,
		SHOP = 5,
		SEPARATOR = 6,
		UNICORN = 7,
		REFRESH = 8,
		LITHIUM_MINE = 9,
		DIAMOND_MINE = 10,
		HOURGLASS = 11,
		DOUBLE_ARROW_UP = 12,
		CHECK_MARK = 13,
		CRYPTO_MINE = 14,
		ADULT_FILM = 15,
		FOOD_TRUCK = 16,
		PRESTIGE = 17,
		WORKER = 18,
		UP = 19,
		DOWN = 20,
		NEXT_PAGE = 21,
		PREV_PAGE = 22,
		BUY_ONE = 23,
		BUY_MAX = 24,
		SELECTED = 25,
		UNSELECTED = 26,
		SICK = 27,
		WORLD = 28,
		OCCULT = 29,
		UPGRADES = 30,
		ON = 31,
		OFF = 32,
		GOLD_MINE = 33,
		CULT_WEAK = 34,
		NAV_BACK = 35,
		EXIT = 36,
	};

	std::map<EmojiId, std::string> ICONS = {
		{BANK, "🏦"},
		{CHART, "📈"},
		{COFFEE, "☕"},
		{WORK, "👨"},
		{SHOP, "🛍️"},
		{SEPARATOR, "┊"},
		{UNICORN, "🦄"},
		{REFRESH, "🔄"},
		{LITHIUM_MINE, "🔋"},
		{DIAMOND_MINE, "💎"},
		{HOURGLASS, "⏳"},
		{DOUBLE_ARROW_UP, "⏫"},
		{CHECK_MARK, "✅"},
		{CRYPTO_MINE, "📟"},
		{ADULT_FILM, "🫦"},
		{FOOD_TRUCK, "🍕"},
		{PRESTIGE, "💸"},
		{WORKER, "👷"},
		{UP, "🔼"},
		{DOWN, "🔽"},
		{NEXT_PAGE, "⏭️"},
		{PREV_PAGE, "⏮️"},
		{BUY_ONE, "💰"},
		{BUY_MAX, "💰"},
		{SELECTED, "◻️"},
		{UNSELECTED, "◼️"},
		{SICK, "😷"},
		{WORLD, "🌍"},
		{OCCULT, "🪬"},
		{UPGRADES, "‼️"},
		{ON, "🟢"},
		{OFF, "🔴"},
		{GOLD_MINE, "🌟"},
		{CULT_WEAK, "🕍"},
		{NAV_BACK, "↩️"},
		{EXIT, "📛"}
	};

    static int fGeneratorIdle(void *a_param, int argc, char **argv, char **column){
        spdlog::debug("Entered generatorCallback");
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
        readDB();
    }

    void IG::Generator::readDB() {

        std::string sql = "SELECT * FROM idlegenerator;";
        spdlog::debug("Before executing Idle Generator SQL statement");
	db->exec(sql, IG::fGeneratorIdle, this);
        
        spdlog::debug("Generators found: {0}", idleGenerators.size());
        
        for (auto gen : idleGenerators) {
            spdlog::debug("\nID: {1}\n{0} | icon: {2} - gold/sec: {3} - level mod {4} - base cost {5} - upgrade cost mod {6} - order weight {7} - current level {8} - upgrade cost {9}\n", 
                         gen.name, gen.id, gen.icon, gen.gold_per_sec, gen.level_mod, gen.base_cost, gen.upgrade_cost_mod, gen.order_weight, gen.curr_level, gen.upgrade_cost);
        }
    }

    void IG::Generator::addGenerator(GeneratorEntry pNewGenerator) {
        idleGenerators.push_back(pNewGenerator);
    }
    
    const int IG::Generator::count() {
        return idleGenerators.size();
    }    

    std::vector<GeneratorEntry> IG::Generator::getData() {
        return idleGenerators;
    }
}

#ifndef IG_GENERATOR_MODEL
#define IG_GENERATOR_MODEL

#pragma once

#include <string>
#include <cstdint>
#include <vector>
#include <sqlite3.h>

namespace IG
{

typedef struct {
	int id;
	std::string name;
	int icon;
	uint64_t gold_per_sec;
	float level_mod;
	double base_cost;
	float upgrade_cost_mod;
	int order_weight;
	int curr_level;
	double upgrade_cost;
	
} GeneratorEntry;

	
class Generator {
public:
	sqlite3* dbInstance;
	
	Generator(sqlite3* pDB);
	void init();
	std::vector<GeneratorEntry> getData();
	const int count();
	void addGenerator(GeneratorEntry pNewGenerator);
	void update(float deltaTime);

private:
	std::vector<GeneratorEntry> data;

	void readDB();
};
}

#endif

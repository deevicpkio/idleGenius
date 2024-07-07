#ifndef IG_SCENE
#define IG_SCENE
#include <raylib.h>
#include "common.h"
#include "dbModels/DBManager.hpp"
#include "dbModels/GeneratorModel.hpp"
#include "dbModels/ProfileModel.hpp"

class Scene 
{
public:
    Scene();
    ~Scene();
    void Update(float deltaTime, UIControlFlags* rControlFlags);
    void Draw(UIControlFlags* rControlFlags);

private:
    DBManager* dbManager;
    IG::Profile* profile;
    IG::Generator* idleGenerators;
    int toggleActive;
    // Screen constraints
    Rectangle panelScrArea;
    Rectangle panelContent;
    Rectangle panelView;
    Vector2 panelScroll;
    int entryHeight;
    int entryGap;
	
    void DrawProfile(); 
    void DrawIdleGenerators(); 
};
#endif

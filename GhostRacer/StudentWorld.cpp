#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

int StudentWorld::init()
{
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    decLives();
    return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
}

StudentWorld::~StudentWorld() {
    
}

GhostRacer* StudentWorld::getGhostRacer() {
    return nullptr;
}

  // Add an actor to the world.
void StudentWorld::addActor(Actor* a) {
    
}

  // Record that a soul was saved.
void StudentWorld::recordSoulSaved() {
    
}

  // If actor a overlaps some live actor that is affected by a holy water
  // projectile, inflict a holy water spray on that actor and return true;
  // otherwise, return false.  (See Actor::beSprayedIfAppropriate.)
bool StudentWorld::sprayFirstAppropriateActor(Actor* a) {
    return false;
}

  // Return true if actor a1 overlaps actor a2, otherwise false.
bool StudentWorld::overlaps(const Actor* a1, const Actor* a2) const {
    return false;
}

  // If actor a overlaps this world's GhostRacer, return a pointer to the
  // GhostRacer; otherwise, return nullptr
GhostRacer* StudentWorld::getOverlappingGhostRacer(Actor* a) const {
    return nullptr;
}

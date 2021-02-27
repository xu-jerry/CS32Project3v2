#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Actor;
class GhostRacer;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual ~StudentWorld();
    
    virtual int init();
    virtual int move();
    virtual void cleanUp();

      // Return a pointer to the world's GhostRacer.
    GhostRacer* getGhostRacer();

      // Add an actor to the world.
    void addActor(Actor* a);

      // Record that a soul was saved.
    void recordSoulSaved();
    
    // returns whether any actor is close, in front, and in same lane
    bool hasCloseActorFront(Actor* a);
    
    // return whether any actor is close, behind, and in same lane
    bool hasCloseActorBack(Actor* a);

      // If actor a overlaps some live actor that is affected by a holy water
      // projectile, inflict a holy water spray on that actor and return true;
      // otherwise, return false.  (See Actor::beSprayedIfAppropriate.)
    bool sprayFirstAppropriateActor(Actor* a);

      // Return true if actor a1 overlaps actor a2, otherwise false.
    bool overlaps(const Actor* a1, const Actor* a2) const;

      // If actor a overlaps this world's GhostRacer, return a pointer to the
      // GhostRacer; otherwise, return nullptr
    GhostRacer* getOverlappingGhostRacer(Actor* a) const;
private:
    GhostRacer* m_ghost_racer;
    std::vector<Actor*> m_actors;
    double m_last_white_border_y;
    int m_bonus;
    int m_souls2save;
};

#endif // STUDENTWORLD_H_

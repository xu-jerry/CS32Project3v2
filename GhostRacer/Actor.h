#ifndef ACTOR_H_
#define ACTOR_H_

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#include "GraphObject.h"

class StudentWorld;

class Actor : public GraphObject
{
public:
    // constructor
    Actor(StudentWorld* sw, int imageID, double x, double y, double size, int dir, int depth);

      // Action to perform for each tick.
    virtual void doSomething() = 0;

      // Is this actor dead?
    bool isDead() const;
    
      // Mark this actor as dead.
    void setDead();

      // Get this actor's world
    StudentWorld* world() const;

      // Get this actor's vertical speed.
    double getVerticalSpeed() const;

      // Set this actor's vertical speed.
    void setVerticalSpeed(double speed);
    
    // get which lane it is in (left = 0, middle = 1, right = 2)
    int getLane();

      // If this actor is affected by holy water projectiles, then inflict that
      // affect on it and return true; otherwise, return false.
    virtual bool beSprayedIfAppropriate();

      // Does this object affect zombie cab placement and speed?
    virtual bool isCollisionAvoidanceWorthy() const;

      // Adjust the x coordinate by dx to move to a position with a y coordinate
      // determined by this actor's vertical speed relative to GhostRacser's
      // vertical speed.  Return true if the new position is within the view;
      // otherwise, return false, with the actor dead.
    bool moveRelativeToGhostRacerVerticalSpeed(double dx);
private:
    bool m_alive;
    StudentWorld* m_student_world;
    int m_v_speed;
};

class BorderLine : public Actor
{
public:
    // constructor
    BorderLine(StudentWorld* sw, double x, double y, bool isYellow);
    
    // Action to perform for each tick.
    virtual void doSomething();
private:
    bool m_is_yellow;
};

class Agent : public Actor
{
public:
    // constructor
    Agent(StudentWorld* sw, int imageID, double x, double y, double size, int dir, int hp);
    virtual bool isCollisionAvoidanceWorthy() const;

      // Get hit points.
    int getHP() const;

      // Increase hit points by hp.
    void incHP(int hp);

      // Do what the spec says happens when hp units of damage is inflicted.
      // Return true if this agent dies as a result, otherwise false.
    virtual bool takeDamageAndPossiblyDie(int hp);

      // What sound should play when this agent is damaged but does not die?
    virtual int soundWhenHurt();

      // What sound should play when this agent is damaged and dies?
    virtual int soundWhenDie();
private:
    int m_hp;
};

class GhostRacer : public Agent
{
public:
    // constructor
    GhostRacer(StudentWorld* sw, double x, double y);
    
    // Action to perform for each tick.
    virtual void doSomething();
    
    // return sound when dies
    virtual int soundWhenDie() const;

      // How many holy water projectiles does the object have?
    int getNumSprays() const;

      // Increase the number of holy water projectiles the object has.
    void increaseSprays(int amt);

      // Spin as a result of hitting an oil slick.
    void spin();
private:
    int m_num_sprays;
};

class Pedestrian : public Agent
{
public:
    // constructor
    Pedestrian(StudentWorld* sw, int imageID, double x, double y, double size);
    
    // return sound when hurt
    virtual int soundWhenHurt() const;
    
    // return sound when dies
    virtual int soundWhenDie() const;

      // Get the pedestrian's horizontal speed
    int getHorizSpeed() const;

      // Set the pedestrian's horizontal speed
    void setHorizSpeed(int s);

      // Move the pedestrian.  If the pedestrian doesn't go off screen and
      // should pick a new movement plan, pick a new plan.
    void moveAndPossiblyPickPlan();
private:
    int m_h_speed;
    double m_plan_distance;
};

class HumanPedestrian : public Pedestrian
{
public:
    // constructor
    HumanPedestrian(StudentWorld* sw, double x, double y);
    
    // Action to perform for each tick.
    virtual void doSomething();
    
    // get sprayed
    virtual bool beSprayedIfAppropriate();
    
    // don't decrease own hp
    virtual bool takeDamageAndPossiblyDie(int hp);
};

class ZombiePedestrian : public Pedestrian
{
public:
    // constructor
    ZombiePedestrian(StudentWorld* sw, double x, double y);
    
    // Action to perform for each tick.
    virtual void doSomething();
    
    // get sprayed
    virtual bool beSprayedIfAppropriate();
private:
    int m_time_until_grunt;
};

class ZombieCab : public Agent
{
public:
    // constructor
    ZombieCab(StudentWorld* sw, double x, double y);
    
    // Action to perform for each tick.
    virtual void doSomething();
    
    // get sprayed
    virtual bool beSprayedIfAppropriate();
private:
    int m_h_speed;
    double m_plan_distance;
    bool m_has_damaged_ghost_racer;
};

class Spray : public Actor
{
public:
    // constructor
    Spray(StudentWorld* sw, double x, double y, int dir);
    
    // Action to perform for each tick.
    virtual void doSomething();
private:
    int m_travel_dist;
};


class GhostRacerActivatedObject : public Actor
{
public:
    // constructor
    GhostRacerActivatedObject(StudentWorld* sw, int imageID, double x, double y, double size, int dir);
    virtual bool beSprayedIfAppropriate();
    
    // Action to perform for each tick.
    virtual void doSomething();

      // Do the object's special activity (increase health, spin Ghostracer, etc.)
    virtual void doActivity(GhostRacer* gr) = 0;

      // Return the object's increase to the score when activated.
    virtual int getScoreIncrease() const = 0;

      // Return the sound to be played when the object is activated.
    virtual int getSound() const;

      // Return whether the object dies after activation.
    virtual bool selfDestructs() const;

      // Return whether the object is affected by a holy water projectile.
    virtual bool isSprayable() const = 0;
};

class OilSlick : public GhostRacerActivatedObject
{
public:
    // constructor
    OilSlick(StudentWorld* sw, double x, double y);
    
    // specific action when overlaps with ghostracer
    virtual void doActivity(GhostRacer* gr);
    
    // return amount of points given when touches ghost racer
    virtual int getScoreIncrease() const;
    
    // return sound when ghostracer overlaps with it
    virtual int getSound() const;
    
    // Return whether the object dies after activation.
    virtual bool selfDestructs() const;
    
    // Return whether the object is affected by a holy water projectile.
    virtual bool isSprayable() const;
};

class HealingGoodie : public GhostRacerActivatedObject
{
public:
    // constructor
    HealingGoodie(StudentWorld* sw, double x, double y);
    
    // specific action when overlaps with ghostracer
    virtual void doActivity(GhostRacer* gr);
    
    // return amount of points given when touches ghost racer
    virtual int getScoreIncrease() const;
    
    // Return whether the object is affected by a holy water projectile.
    virtual bool isSprayable() const;
};

class HolyWaterGoodie : public GhostRacerActivatedObject
{
public:
    // constructor
    HolyWaterGoodie(StudentWorld* sw, double x, double y);
    
    // specific action when overlaps with ghostracer
    virtual void doActivity(GhostRacer* gr);
    
    // return amount of points given when touches ghost racer
    virtual int getScoreIncrease() const;
    
    // Return whether the object is affected by a holy water projectile.
    virtual bool isSprayable() const;
};

class SoulGoodie : public GhostRacerActivatedObject
{
public:
    // constructor
    SoulGoodie(StudentWorld* sw, double x, double y);
    
    // specific action when overlaps with ghostracer
    virtual void doSomething();
    
    // specific action when overlaps with ghostracer
    virtual void doActivity(GhostRacer* gr);
    
    // return amount of points given when touches ghost racer
    virtual int getScoreIncrease() const;
    
    // return sound when ghostracer overlaps with it
    virtual int getSound() const;
    
    // Return whether the object is affected by a holy water projectile.
    virtual bool isSprayable() const;
};

#endif // ACTOR_H_

#include "Actor.h"
#include "StudentWorld.h"
using namespace std;
#define PI 3.14159265359

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(StudentWorld* sw, int imageID, double x, double y, double size, int dir, int depth): GraphObject(imageID, x, y, dir, size, depth) {
    m_student_world = sw;
    m_alive = true;
    m_v_speed = 0;
    
}

// Is this actor dead?
bool Actor::isDead() const {
    return !m_alive;
}

// Mark this actor as dead.
void Actor::setDead() {
    m_alive = false;
}

// Get this actor's world
StudentWorld* Actor::world() const {
    return m_student_world;
}

// Get this actor's vertical speed.
double Actor::getVerticalSpeed() const {
    return m_v_speed;
}

// Set this actor's vertical speed.
void Actor::setVerticalSpeed(double speed) {
    m_v_speed = speed;
}

int Actor::getLane() {
    if (getX() >= ROAD_CENTER - ROAD_WIDTH / 2 && getX() < ROAD_CENTER - ROAD_WIDTH / 2 + ROAD_WIDTH / 3) {
        return 0;
    }
    else if (getX() >= ROAD_CENTER - ROAD_WIDTH / 2 + ROAD_WIDTH / 3 && getX() < ROAD_CENTER + ROAD_WIDTH / 2 - ROAD_WIDTH / 3) {
        return 1;
    }
    else if (getX() >= ROAD_CENTER + ROAD_WIDTH / 2 - ROAD_WIDTH / 3 && getX() < ROAD_CENTER + ROAD_WIDTH / 2) {
        return 2;
    }
    return -1;
}

// If this actor is affected by holy water projectiles, then inflict that
// affect on it and return true; otherwise, return false.
bool Actor::beSprayedIfAppropriate() {
    return false;
}

// Does this object affect zombie cab placement and speed?
bool Actor::isCollisionAvoidanceWorthy() const {
    return false;
}

// Adjust the x coordinate by dx to move to a position with a y coordinate
// determined by this actor's vertical speed relative to GhostRacser's
// vertical speed.  Return true if the new position is within the view;
// otherwise, return false, with the actor dead.
bool Actor::moveRelativeToGhostRacerVerticalSpeed(double dx) {
    
    moveTo(getX() + dx, getY() + getVerticalSpeed() - world()->getGhostRacer()->getVerticalSpeed());
    if (getX() < 0 || getY() < 0 || getX() > VIEW_WIDTH || getY() >
        VIEW_HEIGHT) {
        setDead();
        return false;
    }
    return true;
}

BorderLine::BorderLine(StudentWorld* sw, double x, double y, bool isYellow): Actor(sw, isYellow? IID_YELLOW_BORDER_LINE: IID_WHITE_BORDER_LINE, x, y, 2.0, 0, 2){
    setVerticalSpeed(-4);
    isYellow? m_is_yellow = true: m_is_yellow = false;
    
}
void BorderLine::doSomething() {
    moveRelativeToGhostRacerVerticalSpeed(0);
}

Agent::Agent(StudentWorld* sw, int imageID, double x, double y, double size, int dir, int hp): Actor(sw, imageID, x, y, size, dir, 0){
    m_hp = hp;

}

bool Agent::isCollisionAvoidanceWorthy() const {
    return true;
}

// Get hit points.
int Agent::getHP() const {
    return m_hp;
}

// Increase hit points by hp.
void Agent::incHP(int hp) {
    m_hp += hp;
}

// Do what the spec says happens when hp units of damage is inflicted.
// Return true if this agent dies as a result, otherwise false.
bool Agent::takeDamageAndPossiblyDie(int hp) {
    m_hp -= hp;
    if (m_hp <= 0) {
        world()->playSound(soundWhenDie());
        setDead();
        return true;
    }
    world()->playSound(soundWhenHurt());
    return false;
}

// What sound should play when this agent is damaged but does not die?
int Agent::soundWhenHurt() {
    return SOUND_VEHICLE_HURT;
}

// What sound should play when this agent is damaged and dies?
int Agent::soundWhenDie() {
    return SOUND_VEHICLE_DIE;
}

GhostRacer::GhostRacer(StudentWorld* sw, double x, double y): Agent(sw, IID_GHOST_RACER, x, y, 4.0, 90, 100){
    m_num_sprays = 10;
}

void GhostRacer::doSomething() {
    if (isDead()) {
        return;
    }
    if (getX() < ROAD_CENTER - ROAD_WIDTH/2) {
        if (getDirection() > 90) {
            takeDamageAndPossiblyDie(10);
            setDirection(82);
            world()->playSound(SOUND_VEHICLE_CRASH);
        }
    }
    else if (getX() > ROAD_CENTER + ROAD_WIDTH/2)  {
        if (getDirection() < 90) {
            takeDamageAndPossiblyDie(10);
            setDirection(98);
            world()->playSound(SOUND_VEHICLE_CRASH);
        }
    }
    else {
        int ch;
        if (world()->getKey(ch))
            {
            // user hit a key during this tick!
            switch (ch)
            {
            case KEY_PRESS_LEFT:
                if (getDirection() < 114) {
                    setDirection(getDirection() + 8);
                }
            break;
            case KEY_PRESS_RIGHT:
                if (getDirection() > 66) {
                    setDirection(getDirection() - 8);
                }
            break;
                    /*
            case KEY_PRESS_SPACE:
            ... add spray in front of Ghost Racer...;
            break;
            // etc…
                     */
            case KEY_PRESS_UP:
                if (getVerticalSpeed() < 5) {
                    setVerticalSpeed(getVerticalSpeed() + 1);
                }
                break;
            case KEY_PRESS_DOWN:
                if (getVerticalSpeed() > -1) {
                    setVerticalSpeed(getVerticalSpeed() - 1);
                }
                break;
            }
        }
    }
    double max_shift_per_tick = 4.0;
    double direction = getDirection();
    double delta_x = cos(direction * PI / 180) * max_shift_per_tick;
    double cur_x = getX();
    double cur_y = getY();
    moveTo(cur_x + delta_x, cur_y);
}

int GhostRacer::soundWhenDie() const {
    return SOUND_PLAYER_DIE;
}

// How many holy water projectiles does the object have?
int GhostRacer::getNumSprays() const {
    return m_num_sprays;
}

// Increase the number of holy water projectiles the object has.
void GhostRacer::increaseSprays(int amt) {
    m_num_sprays += amt;
}

// Spin as a result of hitting an oil slick.
void GhostRacer::spin() {

}

Pedestrian::Pedestrian(StudentWorld* sw, int imageID, double x, double y, double size): Agent(sw, imageID, x, y, size, 0, 2) {
    setHorizSpeed(0);
    setVerticalSpeed(-4);
    m_plan_distance = 0;
}

int Pedestrian::soundWhenHurt() const {
    return SOUND_PED_HURT;
}

int Pedestrian::soundWhenDie() const {
    return SOUND_PED_DIE;
}

// Get the pedestrian's horizontal speed
int Pedestrian::getHorizSpeed() const {
    return m_h_speed;
}

// Set the pedestrian's horizontal speed
void Pedestrian::setHorizSpeed(int s) {
    m_h_speed = s;
}

// Move the pedestrian.  If the pedestrian doesn't go off screen and
// should pick a new movement plan, pick a new plan.
void Pedestrian::moveAndPossiblyPickPlan() {
    if (!moveRelativeToGhostRacerVerticalSpeed(m_h_speed)) {
        return;
    }
    m_plan_distance--;
    if (m_plan_distance > 0) {
        return;
    }
    else {
        m_h_speed = randInt(-3, 3);
        while (m_h_speed == 0) {
            m_h_speed = randInt(-3, 3);
        }
        m_plan_distance = randInt(4, 32);
        if (m_h_speed < 0) {
            setDirection(180);
        }
        else {
            setDirection(0);
        }
    }
}

HumanPedestrian::HumanPedestrian(StudentWorld* sw, double x, double y): Pedestrian(sw, IID_HUMAN_PED, x, y, 2.0){

}
void HumanPedestrian::doSomething() {
    if (isDead()) {
        return;
    }
    if (world()->getOverlappingGhostRacer(this) != nullptr) {
        world()->getGhostRacer()->setDead();
        return;
    }
    moveAndPossiblyPickPlan();
}
bool HumanPedestrian::beSprayedIfAppropriate() {
    return false;

}
bool HumanPedestrian::takeDamageAndPossiblyDie(int hp) {
    return false;

}

ZombiePedestrian::ZombiePedestrian(StudentWorld* sw, double x, double y): Pedestrian(sw, IID_ZOMBIE_PED, x, y, 3.0) {

}
void ZombiePedestrian::doSomething() {
    if (isDead()) {
        return;
    }
    if (world()->getOverlappingGhostRacer(this) != nullptr) {
        takeDamageAndPossiblyDie(2);
        world()->getGhostRacer()->takeDamageAndPossiblyDie(5);
        return;
    }
    // also implement holy water
    else {
        // implement later
        world()->increaseScore(150);
    }
    moveAndPossiblyPickPlan();
}
bool ZombiePedestrian::beSprayedIfAppropriate() {
    return false;
}

ZombieCab::ZombieCab(StudentWorld* sw, double x, double y): Agent(sw, IID_ZOMBIE_CAB, x, y, 4.0, 90, 3){
    m_h_speed = 0;
    m_plan_distance = 0;
    m_has_damaged_ghost_racer = false;
}
void ZombieCab::doSomething() {
    if (isDead()) {
        return;
    }
    if (world()->getOverlappingGhostRacer(this) != nullptr) {
        if (!m_has_damaged_ghost_racer) {
            world()->playSound(SOUND_VEHICLE_CRASH);
            world()->getGhostRacer()->takeDamageAndPossiblyDie(20);
            if (getX() <= world()->getGhostRacer()->getX()) {
                m_h_speed = -5;
                setDirection(120 + randInt(0, 19));
            }
            else {
                m_h_speed = 5;
                setDirection(60 - randInt(0, 19));
            }
            m_has_damaged_ghost_racer = true;
        }
    }
    if (!moveRelativeToGhostRacerVerticalSpeed(m_h_speed)) {
        return;
    }
    if (getVerticalSpeed() > world()->getGhostRacer()->getVerticalSpeed()) {
        double min_dist_to_actor = -1;
        for (int i = 0; i < world()->getActors().size(); i++) {
            Actor* cur_actor = world()->getActors()[i];
            if (cur_actor->isCollisionAvoidanceWorthy() && getLane() == cur_actor->getLane()) {
                if (getY() < cur_actor->getY()) {
                    if (min_dist_to_actor == -1) {
                        min_dist_to_actor = cur_actor->getY() - getY();
                    }
                    else {
                        min_dist_to_actor = min(min_dist_to_actor, cur_actor->getY() - getY());
                    }
                }
            }
        }
        if (min_dist_to_actor != -1 && min_dist_to_actor < 96) {
            setVerticalSpeed(getVerticalSpeed() - 0.5);
            return;
        }
    }
    else {
        double min_dist_to_actor = VIEW_HEIGHT + 1;
        for (int i = 0; i < world()->getActors().size(); i++) {
            Actor* cur_actor = world()->getActors()[i];
            if (cur_actor->isCollisionAvoidanceWorthy() && getLane() == cur_actor->getLane()) {
                if (getY() > cur_actor->getY()) {
                    if (min_dist_to_actor == VIEW_HEIGHT + 1) {
                        min_dist_to_actor = getY() - cur_actor->getY();
                    }
                    else {
                        min_dist_to_actor = min(min_dist_to_actor, getY() - cur_actor->getY());
                    }
                }
            }
        }
        if (min_dist_to_actor != VIEW_HEIGHT + 1 && min_dist_to_actor < 96) {
            setVerticalSpeed(getVerticalSpeed() + 0.5);
            return;
        }
    }
    m_plan_distance--;
    if (m_plan_distance > 0) {
        return;
    }
    m_plan_distance = randInt(4, 32);
    setVerticalSpeed(getVerticalSpeed() + randInt(-2, 2));
    /*
     4. If the
     the cab is moving up the screen) and there is a "collision-avoidance worthy" actor in the zombie cab's lane that is in front of that zombie cab:
     zombie cab’s vertical speed is greater than Ghost Racer’s vertical speed (so
     a. If the closest such actor is less than 96 vertical pixels in front of the zombie cab, decrease the zombie cab's vertical speed by .5 and immediately return.
     5. If the zombie cab's vertical speed is the same as or slower than Ghost Racer's vertical speed (so the cab is moving down the screen or holding steady with Ghost Racer) and there is a "collision-avoidance worthy" actor in the zombie cab's lane that is behind that zombie cab:
     a. If the closest such actor is less than 96 vertical pixels behind the zombie cab and is not Ghost Racer, increase the zombie cab's vertical speed by .5 and immediately return.
     6. Decrement the zombie cab’s movement plan distance by one.
     7. If the zombie cab’s movement plan distance is greater than zero, then
     immediately return.
     8. Otherwise, it’s time to pick a new movement plan for the zombie cab:
     a. Set the zombie cab’s movement plan distance to a random integer between 4 and 32, inclusive.
     b. Set the zombie cab’s vertical speed to its vertical speed + a random integer between -2 and 2, inclusive.
     */
}

bool ZombieCab::beSprayedIfAppropriate() {
    return false;
}
/*
Spray::Spray(StudentWorld* sw, double x, double y, int dir) {

}
void Spray::doSomething() {

}


GhostRacerActivatedObject::GhostRacerActivatedObject(StudentWorld* sw, int imageID, double x, double y, double size, int dir) {

}
bool GhostRacerActivatedObject::beSprayedIfAppropriate() {

}

// Return the sound to be played when the object is activated.
int GhostRacerActivatedObject::getSound() const {

}


OilSlick::OilSlick(StudentWorld* sw, double x, double y) {

}
void OilSlick::doSomething() {

}
void OilSlick::doActivity(GhostRacer* gr) {

}
int OilSlick::getScoreIncrease() const {

}
int OilSlick::getSound() const {

}
bool OilSlick::selfDestructs() const {

}
bool OilSlick::isSprayable() const {

}

HealingGoodie::HealingGoodie(StudentWorld* sw, double x, double y) {

}
void HealingGoodie::doSomething() {

}
void HealingGoodie::doActivity(GhostRacer* gr) {

}
int HealingGoodie::getScoreIncrease() const {

}
bool HealingGoodie::selfDestructs() const {

}
bool HealingGoodie::isSprayable() const {

}


HolyWaterGoodie::HolyWaterGoodie(StudentWorld* sw, double x, double y) {

}
void HolyWaterGoodie::doSomething() {

}
void HolyWaterGoodie::doActivity(GhostRacer* gr) {

}
int HolyWaterGoodie::getScoreIncrease() const {

}
bool HolyWaterGoodie::selfDestructs() const {

}
bool HolyWaterGoodie::isSprayable() const {

}
SoulGoodie::SoulGoodie(StudentWorld* sw, double x, double y) {

}
void SoulGoodie::doSomething() {

}
void SoulGoodie::doActivity(GhostRacer* gr) {

}
int SoulGoodie::getScoreIncrease() const {

}
int SoulGoodie::getSound() const {

}
bool SoulGoodie::selfDestructs() const {

}
bool SoulGoodie::isSprayable() const {

}
*/

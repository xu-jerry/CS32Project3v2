#include "Actor.h"
#include "StudentWorld.h"

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
    return false;
}

// What sound should play when this agent is damaged but does not die?
int Agent::soundWhenHurt() {
    return 0;
}

// What sound should play when this agent is damaged and dies?
int Agent::soundWhenDie() {
    return 0;
}

GhostRacer::GhostRacer(StudentWorld* sw, double x, double y): Agent(sw, IID_GHOST_RACER, x, y, 4.0, 90, 100){
    m_num_sprays = 10;
}

void GhostRacer::doSomething() {

}

int GhostRacer::soundWhenDie() const {
    return 0;
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

}
int Pedestrian::soundWhenHurt() const {
    return 0;
}
int Pedestrian::soundWhenDie() const {
    return 0;
}

// Get the pedestrian's horizontal speed
int Pedestrian::getHorizSpeed() const {
    return 0;
}

// Set the pedestrian's horizontal speed
void Pedestrian::setHorizSpeed(int s) {

}

// Move the pedestrian.  If the pedestrian doesn't go off screen and
// should pick a new movement plan, pick a new plan.
void Pedestrian::moveAndPossiblyPickPlan() {

}

HumanPedestrian::HumanPedestrian(StudentWorld* sw, double x, double y): Pedestrian(sw, IID_HUMAN_PED, x, y, 2.0){

}
void HumanPedestrian::doSomething() {

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

}
bool ZombiePedestrian::beSprayedIfAppropriate() {
    return false;
}
/*
ZombieCab::ZombieCab(StudentWorld* sw, double x, double y) {

}
void ZombieCab::doSomething() {

}
bool ZombieCab::beSprayedIfAppropriate() {

}

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

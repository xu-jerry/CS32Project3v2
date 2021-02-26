#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(StudentWorld* sw, int imageID, double x, double y, double size, int dir, int depth) {
    
}

  // Is this actor dead?
bool Actor::isDead() const {
    
}

  // Mark this actor as dead.
void Actor::setDead() {
    
}

  // Get this actor's world
StudentWorld* Actor::world() const {
    
}

  // Get this actor's vertical speed.
double Actor::getVerticalSpeed() const {
    
}

  // Set this actor's vertical speed.
void Actor::setVerticalSpeed(double speed) {
    
}

  // If this actor is affected by holy water projectiles, then inflict that
  // affect on it and return true; otherwise, return false.
 bool Actor::beSprayedIfAppropriate() {
    
}

  // Does this object affect zombie cab placement and speed?
 bool Actor::isCollisionAvoidanceWorthy() const {
    
}

  // Adjust the x coordinate by dx to move to a position with a y coordinate
  // determined by this actor's vertical speed relative to GhostRacser's
  // vertical speed.  Return true if the new position is within the view;
  // otherwise, return false, with the actor dead.
 bool Actor::moveRelativeToGhostRacerVerticalSpeed(double dx) {
    
}

BorderLine::BorderLine(StudentWorld* sw, double x, double y, bool isYellow);
 void BorderLine::doSomething() {
    
}

Agent::Agent(StudentWorld* sw, int imageID, double x, double y, double size, int dir, int hp) {
    
}

 bool Agent::isCollisionAvoidanceWorthy() const {
    
}

  // Get hit points.
int Agent::getHP() const {
    
}

  // Increase hit points by hp.
void Agent::getHP(int hp) const {
    
}

  // Do what the spec says happens when hp units of damage is inflicted.
  // Return true if this agent dies as a result, otherwise false.
 bool Agent::takeDamageAndPossiblyDie(int hp) {
    
}

  // What sound should play when this agent is damaged but does not die?
 int Agent::soundWhenHurt() {
    
}

  // What sound should play when this agent is damaged and dies?
 int Agent::soundWhenDie() {
    
}

GhostRacer::GhostRacer(StudentWorld* sw, double x, double y) {
    
}

 void GhostRacer::doSomething() {
    
}

 int GhostRacer::soundWhenDie() const {
    
}

  // How many holy water projectiles does the object have?
int GhostRacer::getNumSprays() const {
    
}

  // Increase the number of holy water projectiles the object has.
void GhostRacer::increaseSprays(int amt) {
    
}

  // Spin as a result of hitting an oil slick.
void GhostRacer::spin() {
    
}

Pedestrian::Pedestrian(StudentWorld* sw, int imageID, double x, double y, double size) {
    
}
 int Pedestrian::soundWhenHurt() const {
    
}
 int Pedestrian::soundWhenDie() const {
    
}

  // Get the pedestrian's horizontal speed
int Pedestrian::getHorizSpeed() const {
    
}

  // Set the pedestrian's horizontal speed
void Pedestrian::setHorizSpeed(int s) {
    
}

  // Move the pedestrian.  If the pedestrian doesn't go off screen and
  // should pick a new movement plan, pick a new plan.
void Pedestrian::moveAndPossiblyPickPlan() {
    
}

HumanPedestrian::HumanPedestrian(StudentWorld* sw, double x, double y) {
    
}
 void HumanPedestrian::doSomething() {
    
}
 bool HumanPedestrian::beSprayedIfAppropriate() {
    
}
 bool HumanPedestrian::takeDamageAndPossiblyDie(int hp) {
    
}

ZombiePedestrian::ZombiePedestrian(StudentWorld* sw, double x, double y) {
    
}
 void ZombiePedestrian::doSomething() {
    
}
 bool ZombiePedestrian::beSprayedIfAppropriate() {
    
}

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

#include "StudentWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_ghost_racer = nullptr;
}

int StudentWorld::init()
{
    // initialize variables
    m_bonus = 5000;
    m_souls2save = 2 * getLevel() + 5;
    
    // create ghost racer
    m_ghost_racer = new GhostRacer(this, 128, 32);
    // create the two columns of yellow borderlines
    int N = VIEW_HEIGHT / SPRITE_HEIGHT;
    for (int j = 0; j < N; j++){
        int LEFT_EDGE = ROAD_CENTER - ROAD_WIDTH/2;
        int RIGHT_EDGE = ROAD_CENTER + ROAD_WIDTH/2;
        BorderLine* left_yellow = new BorderLine(this, LEFT_EDGE, j * SPRITE_HEIGHT, true);
        BorderLine* right_yellow = new BorderLine(this, RIGHT_EDGE, j * SPRITE_HEIGHT, true);
        m_actors.push_back(left_yellow);
        m_actors.push_back(right_yellow);
    }
    
    // create the two columns of white borderlines
    int M = VIEW_HEIGHT / (4 * SPRITE_HEIGHT);
    for (int j = 0; j < M; j++) {
        int LEFT_EDGE = ROAD_CENTER - ROAD_WIDTH/2;
        int RIGHT_EDGE = ROAD_CENTER + ROAD_WIDTH/2;
        BorderLine* left_middle_white = new BorderLine(this, LEFT_EDGE + ROAD_WIDTH/3, j * (4*SPRITE_HEIGHT), false);
        BorderLine* right_middle_white = new BorderLine(this, RIGHT_EDGE - ROAD_WIDTH/3, j * (4*SPRITE_HEIGHT), false);
        m_actors.push_back(left_middle_white);
        m_actors.push_back(right_middle_white);
    }
    m_last_white_border_y = (M - 1) * (4*SPRITE_HEIGHT);
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // Give each actor a chance to do something, including Ghost Racer
   m_ghost_racer->doSomething();
   for (int i = 0; i < m_actors.size(); i++) {
        if (!m_actors[i]->isDead()){
           // tell that actor to do something (e.g. move)
           m_actors[i]->doSomething();
           if (m_ghost_racer->isDead()) {
               return GWSTATUS_PLAYER_DIED;
           }
            /*
           if (m_souls2save <= 0) {
               //add bonus points to the score
               increaseScore(m_bonus);
               return GWSTATUS_FINISHED_LEVEL;
           }
             */
       }
   }
   
   // Remove newly-dead actors after each tick
   for (int i = 0; i < m_actors.size(); i++) {
       if (m_actors[i]->isDead()) {
           delete m_actors[i];
           m_actors.erase(m_actors.begin() + i);
           i--;
       }
   }
   // Potentially add new actors to the game
   
   // update last white borderline location
    m_last_white_border_y -= 4 + m_ghost_racer->getVerticalSpeed();
    int new_border_y = VIEW_HEIGHT - SPRITE_HEIGHT;
   int delta_y = new_border_y - m_last_white_border_y;
   
   // add new white/yellow borderlines as needed
   if (delta_y >= SPRITE_HEIGHT) {
       BorderLine* temp_yellow1 = new BorderLine(this, ROAD_CENTER - ROAD_WIDTH/2, new_border_y, true);
       BorderLine* temp_yellow2 = new BorderLine(this, ROAD_CENTER + ROAD_WIDTH/2, new_border_y, true);
       m_actors.push_back(temp_yellow1);
       m_actors.push_back(temp_yellow2);
   }
   if (delta_y >= 4*SPRITE_HEIGHT) {
       BorderLine* temp_white1 = new BorderLine(this, ROAD_CENTER - ROAD_WIDTH / 2 + ROAD_WIDTH/3, new_border_y, false);
       BorderLine* temp_white2 = new BorderLine(this, ROAD_CENTER + ROAD_WIDTH / 2 - ROAD_WIDTH/3, new_border_y, false);
       m_actors.push_back(temp_white1);
       m_actors.push_back(temp_white2);
       m_last_white_border_y = new_border_y;
   }
    
   // add zombie cabs
   
    
    int ChanceVehicle = max(100 - getLevel() * 10, 20);
    //int ChanceVehicle = 5;
    int ChanceVehicle1 =  randInt(0, ChanceVehicle - 1);
    if (ChanceVehicle1 == 0) {
        int found_lane = -1;
        double start_y = -1;
        double v_speed;
        vector<int> columns = {0, 1, 2};
        for (int i = 0; i < 3; i++) {
            int col_num = randInt(0, columns.size() - 1);
            int cur_lane = columns[col_num];
            double min_y = -1;
            if (m_ghost_racer->getLane() == cur_lane) {
                min_y = m_ghost_racer->getY();
            }
            for (int j = 0; j < m_actors.size(); j++) {
                bool in_lane = false;
                switch (cur_lane) {
                    case 0:
                        if (m_actors[j]->getX() >= ROAD_CENTER - ROAD_WIDTH / 2 && m_actors[j]->getX() < ROAD_CENTER - ROAD_WIDTH / 2 + ROAD_WIDTH / 3) {
                            in_lane = true;
                        }
                        break;
                    case 1:
                        if (m_actors[j]->getX() >= ROAD_CENTER - ROAD_WIDTH / 2 + ROAD_WIDTH / 3 && m_actors[j]->getX() < ROAD_CENTER + ROAD_WIDTH / 2 - ROAD_WIDTH / 3) {
                            in_lane = true;
                        }
                        break;
                    default:
                        if (m_actors[j]->getX() >= ROAD_CENTER + ROAD_WIDTH / 2 - ROAD_WIDTH / 3 && m_actors[j]->getX() < ROAD_CENTER + ROAD_WIDTH / 2) {
                            in_lane = true;
                        }
                        break;
                }
                if (m_actors[j]->isCollisionAvoidanceWorthy() && in_lane) {
                    if (min_y == -1) {
                        min_y = m_actors[j]->getY();
                    }
                    else {
                        min_y = min(min_y, m_actors[j]->getY());
                    }
                }
            }
            if (min_y == -1 || min_y > VIEW_HEIGHT / 3) {
                found_lane = cur_lane;
                start_y = SPRITE_HEIGHT / 2;
                v_speed = m_ghost_racer->getVerticalSpeed() + randInt(2, 4);
                break;
            }
            double max_y = VIEW_HEIGHT + 1;
            if (m_ghost_racer->getLane() == cur_lane) {
                max_y = m_ghost_racer->getY();
            }
            for (int j = 0; j < m_actors.size(); j++) {
                bool in_lane = false;
                switch (cur_lane) {
                        // change later
                    case 0:
                        if (m_actors[j]->getX() >= ROAD_CENTER - ROAD_WIDTH / 2 && m_actors[j]->getX() < ROAD_CENTER - ROAD_WIDTH / 2 + ROAD_WIDTH / 3) {
                            in_lane = true;
                        }
                        break;
                    case 1:
                        if (m_actors[j]->getX() >= ROAD_CENTER - ROAD_WIDTH / 2 + ROAD_WIDTH / 3 && m_actors[j]->getX() < ROAD_CENTER + ROAD_WIDTH / 2 - ROAD_WIDTH / 3) {
                            in_lane = true;
                        }
                        break;
                    default:
                        if (m_actors[j]->getX() >= ROAD_CENTER + ROAD_WIDTH / 2 - ROAD_WIDTH / 3 && m_actors[j]->getX() < ROAD_CENTER + ROAD_WIDTH / 2) {
                            in_lane = true;
                        }
                        break;
                }
                if (m_actors[j]->isCollisionAvoidanceWorthy() && in_lane) {
                    if (max_y == VIEW_HEIGHT + 1) {
                        max_y = m_actors[j]->getY();
                    }
                    else {
                        max_y = max(max_y, m_actors[j]->getY());
                    }
                }
            }
            if (max_y == VIEW_HEIGHT + 1 || max_y < VIEW_HEIGHT * 2 / 3) {
                found_lane = cur_lane;
                start_y = VIEW_HEIGHT - SPRITE_HEIGHT / 2;
                v_speed = m_ghost_racer->getVerticalSpeed() - randInt(2, 4);
                break;
            }
            columns.erase(columns.begin() + col_num);
        }
        if (found_lane != -1) {
            double start_x;
            switch (found_lane) {
                case 0:
                    start_x = ROAD_CENTER - ROAD_WIDTH / 3;
                    break;
                case 1:
                    start_x = ROAD_CENTER;
                    break;
                default:
                    start_x = ROAD_CENTER + ROAD_WIDTH / 3;
                    break;
            }
            ZombieCab* tempcab = new ZombieCab(this, start_x, start_y);
            tempcab->setVerticalSpeed(v_speed);
            m_actors.push_back(tempcab);
        }
    }
   
   // add new human pedestrians
   int ChanceHumanPed = max(200 - getLevel() * 10, 30);
   // CHANGE LATER
   //int ChanceHumanPed = 10;
   int ChanceHumanPed1 = randInt(0, ChanceHumanPed - 1);
   if (ChanceHumanPed1 == 0) {
       HumanPedestrian* temp = new HumanPedestrian(this, randInt(0, VIEW_WIDTH), VIEW_HEIGHT);
       m_actors.push_back(temp);
   }
   
   // add new zombie pedestrians
   int ChanceZombiePed = max(100 - getLevel() * 10, 20);
   // CHANGE LATER
   //int ChanceHumanPed = 10;
   int ChanceZombiePed1 = randInt(0, ChanceZombiePed - 1);
   if (ChanceZombiePed1 == 0) {
       ZombiePedestrian* temp = new ZombiePedestrian(this, randInt(0, VIEW_WIDTH), VIEW_HEIGHT);
       m_actors.push_back(temp);
   }
    
   //Add new actors
    
    
   // Update the Game Status display text
   // update the score/lives/level text at screen top
   m_bonus--;
   ostringstream oss;
   oss << "Score: " << getScore() << "  ";
   oss << "Lvl: " << getLevel() << "  ";
   oss << "Souls2Save: " << m_souls2save << "  ";
   oss << "Lives: " << getLives() << "  ";
   oss << "Health: " << m_ghost_racer->getHP() << "  ";
   oss << "Sprays: " << m_ghost_racer->getNumSprays() << "  ";
   oss << "Bonus: " << m_bonus << "  ";
   string text = oss.str();
   setGameStatText(text);
     /*
    // the player hasn’t completed the current level and hasn’t died, so
    // continue playing the current level
    */
   return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for (int i = 0; i < m_actors.size(); i++) {
        delete m_actors[i];
    }
    m_actors.clear();
    if (m_ghost_racer != nullptr) {
        delete m_ghost_racer;
        m_ghost_racer = nullptr;
    }
}

StudentWorld::~StudentWorld() {
    cleanUp();
}

GhostRacer* StudentWorld::getGhostRacer() {
    return m_ghost_racer;
}

std::vector<Actor*> StudentWorld::getActors() {
    return m_actors;
}

  // Add an actor to the world.
void StudentWorld::addActor(Actor* a) {
    m_actors.push_back(a);
}

  // Record that a soul was saved.
void StudentWorld::recordSoulSaved() {
    playSound(SOUND_GOT_SOUL);
    increaseScore(100);
    m_souls2save--;
}

  // If actor a overlaps some live actor that is affected by a holy water
  // projectile, inflict a holy water spray on that actor and return true;
  // otherwise, return false.  (See Actor::beSprayedIfAppropriate.)
bool StudentWorld::sprayFirstAppropriateActor(Actor* a) {
    return false;
}

  // Return true if actor a1 overlaps actor a2, otherwise false.
bool StudentWorld::overlaps(const Actor* a1, const Actor* a2) const {
    double delta_x = abs(a1->getX() - a2->getX());
    double delta_y = abs(a1->getY() - a2->getY());
    double radius_sum = a1->getRadius() + a2->getRadius();
    if (delta_x < radius_sum * 0.25 && delta_y < radius_sum * 0.6) {
        return true;
    }
    return false;
}

  // If actor a overlaps this world's GhostRacer, return a pointer to the
  // GhostRacer; otherwise, return nullptr
GhostRacer* StudentWorld::getOverlappingGhostRacer(Actor* a) const {
    if (overlaps(a, m_ghost_racer)) {
        return m_ghost_racer;
    }
    return nullptr;
}

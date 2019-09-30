#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"
#include <string>
#include <list>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Actor;
class Penelope;

bool checkDead(Actor* p);

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual ~StudentWorld() { cleanUp(); }
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    bool canMoveTo(double destX, double destY, Actor* caller) const;
    void playerDied();
    void citizenSaved();
    void zombieDied(double x, double y, Actor* zombie);
    inline void finishLevel() { m_levelFinished = true; }
    int getCitizens() const { return m_numCitizens; }
    double closestZombie(double x, double y);
    void playerPos(double& x, double& y);
    Actor* checkOverlap(double x, double y, int& type, Actor* caller);
    void incGoodie(int goodie);
    void createZombie(Actor* caller);
    void createFlame(Actor* caller);
    void createMine(Actor* caller);
    void createVomit(double x, double y, Direction dir);
    bool checkVomitRange(double x, double y) const;
    void checkVomitVictims(double x, double y);
    void createVaccine(double x, double y);
    void removeDead();
    bool canOverlap(double x, double y, Actor* caller) const;
    void citizenDied(double x, double y);
    double closestPerson(double& x, double& y);
    bool checkFlameBlock(double destX, double destY) const;
    void checkFlameDamage(Actor* caller);
private:
    Penelope* player;
    std::list<Actor*> actors;
    int m_numCitizens;
    bool m_levelFinished;
    bool m_playerDead;
};

double distance(double x1, double y1, double x2, double y2);

#endif // STUDENTWORLD_H_

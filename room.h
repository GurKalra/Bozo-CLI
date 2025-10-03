#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include <map>
#include <limits>
#include <cstdlib>

void clearScreen();

class Room {
public:
    std::map<int, Room*> exits;
    virtual Room* OnEnter(Room* lastRoom, bool &playerHasKey, bool &hasBeenToBasement) = 0;
    virtual ~Room() = default;
};

//Bedroom class
class Bedroom : public Room{
private:
    bool bedMade = false;
    bool hasCried = false;

public:
    bool isBedMade() const;
    bool playerHasCried() const;
    Room* OnEnter(Room* lastRoom, bool &playerHasKey, bool &hasBeenToBasement) override;
};

//Start room class
class StartRoom : public Room{
public:
    Room* OnEnter(Room* lastRoom, bool &playerHasKey,bool &hasBeenToBasement) override;
};

//Kitchen room class
class KitchenRoom : public Room{
private:
    bool fridgeEaten = false;
    bool dustbinEaten = false;
    bool keyTaken = false;
public:
    Room *OnEnter(Room* lastRoom, bool &playerHasKey, bool &hasBeenToBasement) override;
};

//Basement room class
class BasementRoom : public Room{
public:
    Room* OnEnter(Room* lastRoom, bool &playerHasKey, bool &hasBeenToBasement) override;
};

//Bathroom class
class Bathroom : public Room{
public:
    Room *OnEnter(Room* lastRoom, bool &playerHasKEy, bool &hasBeenToBasement) override;
};

#endif
#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include <map>
#include <limits>
#include <cstdlib>

//Helper functions implementation
void clearScreen();
void pressEnterToContinue(); 

class Room {
public:
    std::map<int, Room*> exits;
    virtual Room* OnEnter(Room* lastRoom, bool &playerHasKey, bool &hasBeenToBasement, bool &playerHasScrewdriver, bool &safeOpened) = 0;
    virtual ~Room() = default;
};

//Bedroom class
class Bedroom : public Room{
private:
    bool bedMade = false;
    bool hasCried = false;
    bool resetAfterBasement = false;

public:
    bool isBedMade() const;
    bool playerHasCried() const;
    Room* OnEnter(Room* lastRoom, bool &playerHasKey, bool &hasBeenToBasement, bool &playerHasScrewdriver, bool &safeOpened) override;
};

//Start room class
class StartRoom : public Room{
public:
    Room* OnEnter(Room* lastRoom, bool &playerHasKey,bool &hasBeenToBasement, bool &playerHasScrewdriver, bool &safeOpened) override;
};

//Kitchen room class
class KitchenRoom : public Room{
private:
    bool fridgeEaten = false;
    bool dustbinEaten = false;
public:
    Room *OnEnter(Room* lastRoom, bool &playerHasKey, bool &hasBeenToBasement, bool &playerHasScrewdriver, bool &safeOpened) override;
};

//Basement room class
class BasementRoom : public Room{
public:
    Room* OnEnter(Room* lastRoom, bool &playerHasKey, bool &hasBeenToBasement, bool &playerHasScrewdriver, bool &safeOpened) override;
};

//Bathroom class
class Bathroom : public Room{
public:
    Room *OnEnter(Room* lastRoom, bool &playerHasKey, bool &hasBeenToBasement,bool &playerHasScrewdriver, bool &safeOpened) override;
};

//Study room class
class Study : public Room{
public:
    Room *OnEnter(Room* lastRoom, bool &playerHasKey, bool &hasBeenToBasement,bool &playerHasScrewdriver, bool &safeOpened) override;
};

#endif
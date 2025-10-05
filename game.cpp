#include "room.h"

//main loop
int main() {
    //bools used
    bool hasBeenToBasement = false;
    bool playerHasKey = false;
    bool playerHasScrewdriver = false;
    bool safeOpened = false;

    //rooms
    StartRoom start;
    KitchenRoom kitchen;
    Bedroom bedroom;
    BasementRoom basement;
    Bathroom bathroom;
    Study studyroom;

    //exits linking
    start.exits[1] = &kitchen;
    start.exits[2] = &bedroom;
    start.exits[4] = &bathroom;
    start.exits[5] = &studyroom;

    kitchen.exits[3] = &bedroom;
    kitchen.exits[5] = &start;

    basement.exits[1] = &start;

    Room* currentRoom = &start;
    Room* lastRoom = nullptr;

    while (currentRoom != nullptr) {
        Room* nextRoom;

        if(currentRoom == &start && !hasBeenToBasement){
            Room* tempRoom = currentRoom->OnEnter(lastRoom, playerHasKey, hasBeenToBasement, playerHasScrewdriver, safeOpened);
            if(tempRoom == nullptr){
                std::cout << "\n'Not so fast,' a voice whispers as the floor gives way beneath you!\n";
                pressEnterToContinue();
                nextRoom = &basement;
            }else{
                nextRoom = tempRoom;
            }
        }else{
            nextRoom = currentRoom->OnEnter(lastRoom, playerHasKey, hasBeenToBasement, playerHasScrewdriver, safeOpened);
        }

       if (nextRoom != currentRoom){
        lastRoom = currentRoom;
       }
        currentRoom = nextRoom;
    }

    //Game Over screen
    clearScreen();
    std::cout << "\n\n";
    std::cout << "  #####    ######   ######   ######   \n";
    std::cout << "  #    #   #    #        #   #    #   \n";
    std::cout << "  #####    #    #     ###    #    #    \n";
    std::cout << "  #    #   #    #    #       #    #    \n";
    std::cout << "  #####    ######   ######   ######   \n";
    std::cout << "\n\n";
    return 0;
}


#include "room.h"

//main loop
int main() {
    //for basement ending
    bool hasBeenToBasement = false;
    bool playerHasKey = false;

    //rooms
    StartRoom start;
    KitchenRoom kitchen;
    Bedroom bedroom;
    BasementRoom basement;
    Bathroom bathroom;

    //exits linking
    start.exits[1] = &kitchen;
    start.exits[2] = &bedroom;
    start.exits[4] = &bathroom;

    kitchen.exits[3] = &bedroom;
    kitchen.exits[5] = &start;

    basement.exits[1] = &start;

    Room* currentRoom = &start;
    Room* lastRoom = nullptr;

    while (currentRoom != nullptr) {
        Room* nextRoom;

        if(currentRoom == &start && !hasBeenToBasement){
            Room* tempRoom = currentRoom->OnEnter(lastRoom, playerHasKey, hasBeenToBasement);
            if(tempRoom == nullptr){
                std::cout << "\n'Not so fast,' a voice whispers as the floor gives way beneath you!\n";
                std::cout << "Press Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();

                nextRoom = &basement;
                hasBeenToBasement = true;
            }else{
                nextRoom = tempRoom;
            }
        }else{
            nextRoom = currentRoom->OnEnter(lastRoom, playerHasKey, hasBeenToBasement);
        }

        lastRoom = currentRoom;
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


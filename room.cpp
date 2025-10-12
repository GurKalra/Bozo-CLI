#include "room.h"

//Helper functions implementation
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pressEnterToContinue(){
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

//Bedroom Implementations
bool Bedroom::isBedMade() const{
    return bedMade;
}

bool Bedroom::playerHasCried() const{
    return hasCried;
}

Room* Bedroom::OnEnter(Room* lastRoom, bool &playerHasKey, bool &hasBeenToBasement, bool &playerHasScrewdriver, bool &safeOpened, bool &playerKnowsCode, bool &boxIsOpened){
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "==               BEDROOM              ==\n";
    std::cout << "========================================\n\n";

    //Reset bools for after basement
    if (hasBeenToBasement && !resetAfterBasement){
        bedMade = false;
        hasCried = false;
        resetAfterBasement = true;
    }

    int choice = 0;

    //Before Basement
    if(!hasBeenToBasement){
        if(bedMade || hasCried){
            std::cout << "You've already dealt with the bedroom. No need to go back.\n";
            pressEnterToContinue();
            return lastRoom;
        }

        std::cout << "You have come to cry but the bed is not made....What to do??\n\n";
        std::cout << "  1. Clean the bed and then cry\n";
        std::cout << "  2. Let me just cry please\n";
        std::cout << "  3. My bad i will leave\n\n";
        std::cout << "Choose: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "\nStop pressing random keys bruh\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            pressEnterToContinue();
            return this;
        }

        switch (choice) {
        case 1:
            bedMade = true;
            std::cout << "\nWow the bed is now made but now you feel like you dont want to cry.\nThat's nice and now you feel like leaving......" << std::endl;
            pressEnterToContinue();
            return lastRoom;
        case 2:
            hasCried = true;
            std::cout << "\nYou cried. The unmade bed is surprisingly comforting." << std::endl;
            pressEnterToContinue();
            return lastRoom;
        case 3:
            std::cout << "\nYou leave the messy room." << std::endl;
            pressEnterToContinue();
            return lastRoom;
        default:
            std::cout << "\nReally even after all these choices. Wow" << std::endl;
            pressEnterToContinue();
            return this;
        }
    //After Basement
    }else{
        std::cout << "The Voice in your head re-frames the options for you.\n\n";
        std::cout << "  1. Fight the apathy and make the bed.\n";
        std::cout << "  2. Give in to the exhaustion.\n";
        std::cout << "  3. Check the wobbly leg on the nightstand.\n";
        std::cout << "  4. Flee from the responsibility.\n\n";
        std::cout << "What will it be?: ";

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "\nStop pressing random keys bruh\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Press Enter to continue...";
            std::cin.get();
            return this;
        }

        switch (choice) {
        case 1:
            bedMade = true;
            std::cout << "\nWith a sigh, you make the bed. A small victory..." << std::endl;
            pressEnterToContinue();
            return this;
        case 2:
            hasCried = true;
            std::cout << "\nYou collapse onto the sheets. The Voice whispers, 'Easier, isn't it?'" << std::endl;
            pressEnterToContinue();
            return this;
        case 3:
            if (!playerHasScrewdriver) {
                std::cout << "\nYou tighten a loose screw by hand. As you do, another one falls out... along with a small screwdriver. You pocket it." << std::endl;
                playerHasScrewdriver = true;
            } else {
                std::cout << "\nYou've already fixed the nightstand. It's perfectly stable now (you assume)." << std::endl;
            }
            pressEnterToContinue();
            return this;
        case 4:
            std::cout << "\nYou turn and leave. The unmade bed feels like a silent accusation." << std::endl;
            pressEnterToContinue();
            return lastRoom;
        default:
            std::cout << "\n'Indecisive as always,' the Voice mutters." << std::endl;
            pressEnterToContinue();
            return this;
        }
    }
}

//Start room implementation
Room* StartRoom::OnEnter(Room* lastRoom, bool &playerHasKey, bool &hasBeenToBasement, bool &playerHasScrewdriver, bool &safeOpened, bool &playerKnowsCode, bool &boxIsOpened){
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "==             STARTING POINT         ==\n";
    std::cout << "========================================\n\n";

    int choice = 0;
    //Before Basement
    if(!hasBeenToBasement){
        std::cout << "Choose your choice:\n";
        std::cout << "  1. Eat?\n";
        std::cout << "  2. Cry?\n";
        std::cout << "  3. Nah i'm out\n\n";
        std::cout << "Choose Wisely: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "\nBro choose something valid." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            pressEnterToContinue();
            return this;
        }

        switch (choice) {
            case 1:
                return exits[1];
            case 2:
                return exits[2];
            case 3:
                return nullptr;
            default:
                std::cout << "\nInvalid choice man." << std::endl;
                pressEnterToContinue();
                return this;
        }

    } else{
        std::cout << "The Voice in your head presents the usual, tedious options:\n";
        std::cout << "  1. Fill the void? (Kitchen)\n";
        std::cout << "  2. Wallow in it? (Bedroom)\n";
        std::cout << "  3. Try to leave again?\n";
        std::cout << "  4. Face yourself. (Bathroom)\n";
        std::cout << "  5. Retreat into old memories. (Study)\n\n";
        std::cout << "What will it be?: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "\n'A pointless choice for a pointless existence,' the Voice mocks." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            pressEnterToContinue();
            return this;
        }

        switch (choice) {
            case 1:
                return exits[1];
            case 2:
                return exits[2];
            //----------ENDING 5----------
            case 3:
                std::cout << "\n'Fine. Leave,' the Voice sighs. 'See if I care.'\n";
                std::cout << "    --- FIN --- \n\n";
                std::cout << "Press Enter to close the game...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                return nullptr;
            case 4:
                return exits[4];
            case 5:
                return exits[5];
            default:
                std::cout << "\n'A pointless choice for a pointless existence,' the Voice mocks." << std::endl;
                pressEnterToContinue();
                return this;
        }
    }
}

//Kitchen Room implementation
Room* KitchenRoom::OnEnter(Room* lastRoom, bool &playerHasKey, bool &hasBeenToBasement, bool &playerHasScrewdriver, bool &safeOpened, bool &playerKnowsCode, bool &boxIsOpened){
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "==               KITCHEN              ==\n";
    std::cout << "========================================\n\n";

    int choice = 0;

    //Before Basement
    if(!hasBeenToBasement){
        std::cout << "Came to the kitchen....What to do in kitchen?\n\n";
        std::cout << "  1. Open fridge?\n";
        std::cout << "  2. Eat from Dustbin\n";
        std::cout << "  3. Go to cry\n";
        std::cout << "  4. Search the cookie jar\n";
        std::cout << "  5. Nothing to do here LET ME LEAVE\n\n";
        std::cout << "Choose Right Now: ";

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "\nStop pressing random keys bruh\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            pressEnterToContinue();
            return this;
        }

        switch (choice){
            case 1:
                if (!fridgeEaten) {
                std::cout << "\nYou opened the fridge and ate the apple" << std::endl;
                fridgeEaten = true;
                }else{
                    std::cout << "\nThe fridge is now empty. Maybe next time bring your own groceries." << std::endl;
                }
                pressEnterToContinue();
                return this;
            case 2:
                if (!dustbinEaten) {
                std::cout << "\nYou ate leftovers from the dustbin. Gross but satisfying." << std::endl;
                dustbinEaten = true;
                }else{
                    std::cout << "\nLiterally nothing is left have some shame" << std::endl;
                }
                pressEnterToContinue();
                return this;
            case 3:
                if (!fridgeEaten){
                    std::cout << "\nYou try to go cry... but the fridge glares at you" << std::endl;
                }else{
                    std::cout << "\nAfter eating, the thought of your messy room fills you with a strange sense of responsibility. You can't face it right now." << std::endl;
                }
                pressEnterToContinue();
                return this;
            case 4:
                if (!playerHasKey) {
                    std::cout << "\nYou search the dusty old cookie jar. Beneath a few old crumbs, you find a small, iron key!...Also you ate the crumbs" << std::endl;
                    playerHasKey = true;
                } else {
                    std::cout << "\nYou've already searched the cookie jar." << std::endl;
                }
                pressEnterToContinue();
                return this;
            case 5:
                std::cout << "\nOk man stop shouting... Going back" << std::endl;
                return exits[5];
            default:
                std::cout << "\nStop pressing random keys bruh\n";
                pressEnterToContinue();
                return this;
        }
    }else{
        std::cout << "The kitchen feels judgmental. The appliances watch you silently.\n\n";
        std::cout << "  1. Eat the apple from the fridge. Again.\n";
        std::cout << "  2. Scrounge for scraps. Again.\n";
        std::cout << "  3. Listen to what the fridge is saying.\n";
        std::cout << "  4. Stare into the empty cookie jar.\n";
        std::cout << "  5. Flee the judgment.\n\n";
        std::cout << "Choose: ";

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "\nStop pressing random keys bruh\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            pressEnterToContinue();
            return this;
        }

        switch (choice){
            case 1:
                if (!fridgeEaten) {
                std::cout << "\nYou opened the fridge and ate the apple" << std::endl;
                fridgeEaten = true;
                }else{
                    std::cout << "\n'Still not satisfied?' the fridge seems to hum." << std::endl;
                }
                pressEnterToContinue();
                return this;
            case 2:
                if (!dustbinEaten) {
                std::cout << "\nYou ate leftovers from the dustbin. Gross but satisfying." << std::endl;
                dustbinEaten = true;
                }else{
                    std::cout << "\n'Pathetic,' whispers the bin lid." << std::endl;
                }
                pressEnterToContinue();
                return this;
            case 3:
                std::cout << "\nThe fridge hums a low, judgmental tone. 'You are never satisfied,' it seems to say. 'Always wanting more.'" << std::endl;
                pressEnterToContinue();
                return this;
            case 4:
                if (!playerHasKey) {
                    std::cout << "\nStaring into the empty jar, you feel a moment of clarity. This is what you were looking for." << std::endl;
                    playerHasKey = true;
                } else {
                    std::cout << "\nYou've already stared into the abyss of the cookie jar." << std::endl;
                }
                pressEnterToContinue();
                return this;
            case 5:
                std::cout << "\nYou flee the silent judgement." << std::endl;
                return exits[5];
            default:
                std::cout << "\n'Pointless,' the room seems to sigh." << std::endl;
                pressEnterToContinue();
                return this;
        }
    }
}

//Basement room implementation
Room* BasementRoom::OnEnter(Room* lastRoom, bool &playerHasKey, bool &hasBeenToBasement, bool &playerHasScrewdriver, bool &safeOpened,bool &playerKnowsCode, bool &boxIsOpened){
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "==               BASEMENT             ==\n";
    std::cout << "========================================\n\n";

    std::cout << "You're in a dark, musty basement. The heavy door is shut tight!\n" << std::endl;

    if(playerHasKey){
        std::cout<<"But wait... you have a key! It looks like it might fit this door.\n\n";
        std::cout << "  1. Use the iron key\n";
        std::cout << "  2. Panic\n\n";
        std::cout << "Choose: ";
        int choice = 0;
        std::cin >> choice;

        if(std::cin.good() && choice == 1){
            std::cout << "\nThe key actually works well done man!! You are where you started (don't try leaving again just in case)..." << std::endl;
            hasBeenToBasement = true;
            pressEnterToContinue();
            return exits[1];
        }
    }
    //----------ENDING 1----------
    std::cout << "\nThe door is locked tight. There are no windows. You are trapped here. \n";
    std::cout << "You lived here without any food or water for 25 days and then died RIP....\n" << std::endl;
    std::cout << "    --- FIN --- \n\n";
    std::cout << "Press Enter to close the game...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    return nullptr;
}

//Bathroom implementation
Room* Bathroom::OnEnter(Room* lastRoom, bool &playerHasKey, bool &hasBeenToBasement, bool &playerHasScrewdriver, bool &safeOpened, bool &playerKnowsCode, bool &boxIsOpened){
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "==               BATHROOM             ==\n";
    std::cout << "========================================\n\n";
    std::cout << "You stand in a small, grimy bathroom. A large, clouded mirror hangs over the sink.\n";

    if(!playerHasKey){
        std::cout << "\nYou look in the mirror, but your refection is distorted and unclear. 'What are you even doing here?' it seems to mumble.\n";
        pressEnterToContinue();
        return lastRoom;
    }

    std::cout << "\nYou hold the moment of clarity you found. As you look in the mirror, your reflection sharpens. It looks back at you, and you hear The Voice clearly.\n\n";
    std::cout << "'So, this is it,' The Voice says. 'This is all you are.'\n\n";
    std::cout << "How do you respond?\n";
    std::cout << "  1. 'You're right. I'm a failure.' (Agree with The Voice)\n";
    std::cout << "  2. 'No, you're wrong!' (Argue with The Voice)\n";
    std::cout << "  3. (Say nothing. Just nod.) (Acknowledge The Voice)\n\n";
    if(boxIsOpened){
        std::cout << "  4. 'I remember the drawing. (Show compassion)\n";
    }
    std::cout << "Choose: ";

    int choice = 0;
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cout << "\n'Indecisive,' the Voice mutters." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        pressEnterToContinue();
        return this;
    }

    switch (choice){
        //----------ENDING 2----------
        case 1:
            std::cout << "\n'I knew it,' the reflection smirks. The room fades to black.\n";
            std::cout << "    --- FIN --- \n\n";
            std::cout << "Press Enter to close the game...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            return nullptr;
        //----------ENDING 3----------
        case 2:
            std::cout << "\n'Am I?' it laughs. 'We'll have this argument again tomorrow.' The room fades.\n";
            std::cout << "    --- FIN --- \n\n";
            std::cout << "Press Enter to close the game...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            return nullptr;
        //----------ENDING 4----------
        case 3:
            std::cout << "\nThe reflection's smirk falters. It seems surprised by your lack of resistance.\n'I hear you,' you think. 'Now I'm going to go eat something.'\n";
            std::cout << "The Voice is silent. For now.\n";
            std::cout << "    And so, the day continued.\n\n";
            std::cout << "    --- FIN --- \n\n";
            std::cout << "Press Enter to close the game...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            return nullptr;
        //----------ENDING 6----------
        case 4:
            if (boxIsOpened){
                std::cout << "\nYou look at the snarling face in the mirror and instead of anger, you feel a deep, aching sadness.\n";
                std::cout << "'I remember the drawing,' you think. 'I remember you were just trying to protect me then.'\n\n";
                std::cout << "The reflection's face softens. The anger drains away, replaced by that same, echoing sadness from the memory.\n";
                std::cout << "'I was,' it whispers. 'I'm... tired.'\n\n";
                std::cout << "The reflection fades, not in anger, but in quiet release. You are alone, but for the first time, you don't feel lonely.\n";
                std::cout << "    --- FIN --- \n\n";
                std::cout << "Press Enter to close the game...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                return nullptr;
            }

        default:
            std::cout << "\nYour silence is an answer in itself. The reflection just stares." << std::endl;
            pressEnterToContinue();
            return this;
    }
}


//Study room implementation
Room* Study::OnEnter(Room* lastRoom, bool &playerHasKey, bool &hasBeenToBasement, bool &playerHasScrewdriver, bool &safeOpened, bool &playerKnowsCode, bool &boxIsOpened){
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "==                 STUDY              ==\n";
    std::cout << "========================================\n\n";

    std::cout << "You enter a dusty study. Bookshelves line the walls, and a large, imposing painting hangs crookedly.\n\n";
    std::cout << "  1. Examine the bookshelves.\n";
    std::cout << "  2. Examine the crooked painting.\n";
    if(safeOpened){
        std::cout << "  4. Try to open the metal box.\n";
    }
    std::cout << "  3. Leave.\n\n";
    std::cout << "Choose: ";

    int choice = 0;
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cout << "\nStop pressing random keys bruh\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        pressEnterToContinue();
        return this;
    }

    switch(choice){
        case 1:
            if(safeOpened){
                if(!playerKnowsCode){
                     std::cout << "\nYou search the books with a new sense of purpose. Tucked away is a single, slim diary. Most pages are blank, but one has a date circled in red: April 18th." << std::endl;
                     playerKnowsCode = true;
                } else {
                    std::cout << "\nYou look at the diary again. The date, 0418, seems to burn into your memory." << std::endl;
                }
            } else {
                std::cout << "\nThe books are old and uninteresting. You notice a slim diary tucked away, but the thought of opening it feels exhausting. 'Leave it,' The Voice mutters. 'It's better left forgotten.'" << std::endl;
            }
            pressEnterToContinue();
            return this;
        case 2:
            if(!safeOpened){
                std::cout << "\nYou straighten the painting. As you do, you feel a hollow space behind it. You take it off the wall, revealing a ventilation grate." << std::endl;
                if(playerHasScrewdriver){
                    std::cout << "You use the screwdriver to easily pop the grate off. Inside is a small, heavy metal box. You've found something important." << std::endl;
                    safeOpened = true;
                } else {
                    std::cout << "The grate is screwed tight. You can't open it with your bare hands. 'Another failure,' the Voice sighs." << std::endl;
                }
            } else {
                std::cout << "\nYou look at the empty space where the grate used to be. You've already found what was hidden here." << std::endl;
            }
            pressEnterToContinue();
            return this;
        case 3:
            return lastRoom;
        case 4:
            if(safeOpened){
                if(playerKnowsCode){
                    if(!boxIsOpened){
                        std::cout << "\nYou enter the date you found, 0-4-1-8. The box clicks open. Inside are faded photographs of a life before... before all this. You've unlocked the core memory." << std::endl;
                        boxIsOpened = true;
                    } else {
                        std::cout << "\nThe box is already open. The faded photographs sit inside." << std::endl;
                    }
                } else {
                    std::cout << "\nThe box has a four-digit lock. You don't know the combination. 'Missing something, aren't we?' the Voice taunts." << std::endl;
                }
            } else {
                std::cout << "\n'A pointless choice,' the Voice says. You do nothing." << std::endl;
            }
            pressEnterToContinue();
            return this;
        default:
            std::cout << "\n'A pointless choice,' the Voice says. You do nothing." << std::endl;
            pressEnterToContinue();
            return this;
    }
}

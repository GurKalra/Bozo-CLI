#include "room.h"

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

//Bedroom Implementations
bool Bedroom::isBedMade() const{
    return bedMade;
}

bool Bedroom::playerHasCried() const{
    return hasCried;
}

Room* Bedroom::OnEnter(Room* lastRoom, bool &playerHasKey, bool &hasBeenToBasement){
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "==               BEDROOM              ==\n";
    std::cout << "========================================\n\n";

    int choice = 0;
    
    if(!hasBeenToBasement){
        std::cout << "You have come to cry but the bed is not made....What to do??\n\n";
        std::cout << "  1. Clean the bed and then cry\n";
        std::cout << "  2. Let me just cry please\n";
        std::cout << "  3. My bad i will leave\n\n";
        std::cout << "Choose: ";
    }else{
        std::cout << "The Voice in your head re-frames the options for you.\n\n";
        std::cout << "  1. Fight the apathy and make the bed.\n";
        std::cout << "  2. Give in to the exhaustion.\n";
        std::cout << "  3. Flee from the responsibility.\n\n";
        std::cout << "What will it be?: ";
    }
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
        std::cout << (!hasBeenToBasement ? "\nWow the bed is now made but now you feel like you dont want to cry.\nThat's nice and now you feel like leaving......" : "\nWith a sigh, you make the bed. A small victory...") << std::endl;
        break;
    case 2:
        hasCried = true;
        std::cout << (!hasBeenToBasement ? "\nYou cried. The unmade bed is surprisingly comforting." : "\nYou collapse onto the sheets. The Voice whispers, 'Easier, isn't it?'") << std::endl;
        break;
    case 3:
        std::cout << (!hasBeenToBasement ? "\nYou leave the messy room." : "\nYou turn and leave. The unmade bed feels like a silent accusation.") << std::endl;
        break;
    default:
        std::cout << "\nReally even after all these choices. Wow" << std::endl;
        break;
    }

    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    return lastRoom;
}

//Start room implementation
Room* StartRoom::OnEnter(Room* lastRoom, bool &playerHasKey, bool &hasBeenToBasement){
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "==             STARTING POINT         ==\n";
    std::cout << "========================================\n\n";

    int choice = 0;
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
            std::cout << "Press Enter to continue...";
            std::cin.get();
            return this;
        }

        if (choice == 2) {
            Bedroom* bedroom = dynamic_cast<Bedroom*>(exits[2]);
            if (bedroom) {
                if (bedroom->isBedMade()) {
                    std::cout << "\nYou made the bed earlier. You feel too accomplished to go back and cry now." << std::endl;
                    std::cout << "Press Enter to continue...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();
                    return this;
                }
                if (bedroom->playerHasCried()) {
                    std::cout << "\nYou've already had your cry. The room feels emotionally spent." << std::endl;
                    std::cout << "Press Enter to continue...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();
                    return this;
                }
            }
        }

        if (exits.count(choice)) {
            return exits[choice];
        }

        if(choice==3){
            return nullptr;
        }

    }else{
        std::cout << "The Voice in your head presents the usual, tedious options:\n";
        std::cout << "  1. Fill the void? (Kitchen)\n";
        std::cout << "  2. Wallow in it? (Bedroom)\n";
        std::cout << "  3. Try to leave again?\n";
        std::cout << "  4. Face yourself. (Bathroom)\n\n";
        std::cout << "What will it be?: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "\nBro choose something valid." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Press Enter to continue...";
            std::cin.get();
            return this;
        }
        if (choice == 2) {
            Bedroom* bedroom = dynamic_cast<Bedroom*>(exits[2]);
            if (bedroom) {
                if (bedroom->isBedMade() || bedroom->playerHasCried()) {
                    std::cout << "\n'You've already dealt with that,' the Voice says. 'Find a new problem.'\n";
                    std::cout << "Press Enter to continue...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();
                    return this;
                }
            }
        }
        if (choice == 3) {
            //----------ENDING 5----------
            std::cout << "\n'Fine. Leave,' the Voice sighs. 'See if I care.'\n";
            std::cout << "Press Enter to close the game...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            return nullptr;
        }
        if (exits.count(choice)) { return exits[choice]; }
    }
    std::cout << "\nInvalid choice man." << std::endl;
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    return this;
}

//Kitchen Room implementation
Room* KitchenRoom::OnEnter(Room* lastRoom, bool &playerHasKey, bool &hasBeenToBasement){
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "==               KITCHEN              ==\n";
    std::cout << "========================================\n\n";

    int choice = 0;
    if(!hasBeenToBasement){
        std::cout << "Came to the kitchen....What to do in kitchen?\n\n";
        std::cout << "  1. Open fridge?\n";
        std::cout << "  2. Eat from Dustbin\n";
        std::cout << "  3. Go to cry\n";
        std::cout << "  4. Search the cookie jar\n";
        std::cout << "  5. Nothing to do here LET ME LEAVE\n\n";
        std::cout << "Choose Right Now: ";
    }else{
        std::cout << "The kitchen feels judgmental. The appliances watch you silently.\n\n";
        std::cout << "  1. Eat the apple from the fridge. Again.\n";
        std::cout << "  2. Scrounge for scraps. Again.\n";
        std::cout << "  3. Listen to what the fridge is saying.\n";
        std::cout << "  4. Stare into the empty cookie jar.\n";
        std::cout << "  5. Flee the judgment.\n\n";
        std::cout << "Choose: ";
    }
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
        if (!fridgeEaten) {
            std::cout << "\nYou opened the fridge and ate the apple" << std::endl;
            fridgeEaten = true;
        }
        else {
            std::cout << (!hasBeenToBasement ? "\nThe fridge is now empty. Maybe next time bring your own groceries." : "\n'Still not satisfied?' the fridge seems to hum.") << std::endl;
        }
        break;
    case 2:
        if (!dustbinEaten) {
            std::cout << "\nYou ate leftovers from the dustbin. Gross but satisfying." << std::endl;
            dustbinEaten = true;
        }
        else {
            std::cout << (!hasBeenToBasement ? "\nLiterally nothing is left have some shame" : "\n'Pathetic,' whispers the bin lid.") << std::endl;
        }
        break;
    case 3:
        if(!hasBeenToBasement){
            if(!fridgeEaten){
                std::cout << "\nYou try to go cry… but the fridge glares at you";
            }else{
                 std::cout << "\nAfter eating, the thought of your messy room fills you with a strange sense of responsibility. You can't face it right now." << std::endl;
            }
        }else{
            std::cout << "\nThe fridge hums a low, judgmental tone. 'You are never satisfied,' it seems to say. 'Always wanting more.'\n";
        }
        break;
    case 4:
        if(!keyTaken){
            std::cout << (!hasBeenToBasement ? "\nYou search the dusty old cookie jar. Beneath a few old crumbs, you find a small, iron key!...Also you ate the crumbs" : "\nStaring into the empty jar, you feel a moment of clarity. This is what you were looking for.") << std::endl;
            playerHasKey = true;
            keyTaken = true;
        } else{
            std::cout<< "\nYou've already searched the cookie jar." <<std::endl;
        }
        break;
    case 5:
        std::cout << "\nOk man stop shouting... Going back" << std::endl;
        return exits[5];
    default:
        std::cout << "\nStop pressing random keys bruh\n";
        break;
    }

    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    return this;
}

//Basement room implementation
Room* BasementRoom::OnEnter(Room* lastRoom, bool &playerHasKey, bool &hasBeenToBasement){
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
            std::cout << "Press Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();

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
Room* Bathroom::OnEnter(Room* lastRoom, bool &playerHasKey, bool &hasBeenToBasement){
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "==               BATHROOM             ==\n";
    std::cout << "========================================\n\n";
    std::cout << "You stand in a small, grimy bathroom. A large, clouded mirror hangs over the sink.\n";

    if(!playerHasKey){
        std::cout << "\nYou look in the mirror, but your refection is distorted and unclear. 'What are you even doing here?' it seems to mumble.\n";
        std::cout<<"Press Enter to go back...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        return lastRoom;
    }

    std::cout << "\nYou hold the moment of clarity you found. As you look in the mirror, your reflection sharpens. It looks back at you, and you hear The Voice clearly.\n\n";
    std::cout << "'So, this is it,' The Voice says. 'This is all you are.'\n\n";
    std::cout << "How do you respond?\n";
    std::cout << "  1. 'You're right. I'm a failure.' (Agree with The Voice)\n";
    std::cout << "  2. 'No, you're wrong!' (Argue with The Voice)\n";
    std::cout << "  3. (Say nothing. Just nod.) (Acknowledge The Voice)\n\n";
    std::cout << "Choose: ";

    int choice = 0;
    std::cin >> choice;

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

    }
    return this;
}


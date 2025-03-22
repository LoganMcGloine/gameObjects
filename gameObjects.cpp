#include <iostream>
#include <vector>
#include <string>


//global variables
int playerHealth = 10;
double playerMoney = 0.0;
int attackPower = 10;
int healPower = 20;
int maxHealth = 150;



//create a abstract class for players which contains the common attributes and methods for all players
class player {
    protected:
        std::string name;
        int health;
        double money;

    public:
        //constructor to initialize player
        player(std::string name) :
         name(name),
         health(playerHealth),
         money(playerMoney) 
         {}

        //virtual destructor is important for proper cleanup of derived classes
        virtual ~player() {
            std::cout << "Player " << name << " has been deleted" << std::endl;
        }

        //function to print players information
        virtual void printPlayer() {
            std::cout << "Name: " << name << std::endl;
            std::cout << "Type: " << getPlayerTypeName() << std::endl;
            std::cout << "Health: " << health << std::endl;
            std::cout << "Money: " << money << std::endl;
        }

        // Keep this pure virtual to force subclasses to identify their type
        virtual std::string getPlayerTypeName() = 0;
        virtual int playerType() = 0;

        //getter methods for player attributes
        std::string getName() const { return name; }
        int getHealth() const { return health; }
        double getMoney() const { return money; }

        //setter methods for player attributes 
        void setHealth(int newHealth) { health = newHealth; }
        void setMoney(double newMoney) { money = newMoney; }

        //incrementing functions for health and money
        void incrementHealth(int amount) { health += amount; }
        void incrementMoney(double amount) { money += amount; }
 
        //functions to decrement health and money
        void decrementHealth(int amount) { health -= amount; }
        void decrementMoney(double amount) { money -= amount; }
};

//create a warrior class that inherits from the player class
class warrior : public player {
    //adding a protected variable for power
    protected:
        int power;

    public:
        //Constructor to initialize warrior set power, health and money
        warrior(std::string name) : player(name) {
            power = attackPower * 1.5;
            setHealth(playerHealth);
            setMoney(playerMoney);
        }
   
        //a function to override the playerType function to return 1
        int playerType() override {
            return 1;
        }

        //a function to override the getPlayerTypeName function to return "Warrior"
        std::string getPlayerTypeName() override {
            return "Warrior";
        }

        //function to attack player
        int attack(player& target) {
            //warrior attacks player
            std::cout << name << " attacks " << target.getName() << " for " << power << " damage!" << std::endl;
            
            //decrement the target's health
            target.decrementHealth(power);
            std::cout << target.getName() << " now has " << target.getHealth() << " health!" << std::endl;
           
            //if the target's health is less than 0, print a message then deconstruct the target
            if (target.getHealth() <= 0) {
                std::cout << target.getName() << " has been defeated!" << std::endl;
                //deconstruct the target
                delete &target;
                return 1;
            }
            return 0;
        }
};

//create a healer class that inherits from the player class
class healer : public player {
    //adding a protected variable for heal power
    protected:
        int healPower;

    public:
        //Constructor to initialize healer set heal power, health and money
        healer(std::string name) : player(name) {
            healPower = 20;
            setHealth(playerHealth);
            setMoney(playerMoney);
        }

        //a function to override the playerType function to return 2
        int playerType() override {
            return 2;
        }

        //a function to override the getPlayerTypeName function to return "Healer"  
        std::string getPlayerTypeName() override {
            return "Healer";
        }

        //function to heal player
        void heal(player& target) {
            //healer heals player as long as players health is less than 100
            if (target.getHealth() < maxHealth) {
                std::cout << name << " heals " << target.getName() << " for " << healPower << " health!" << std::endl;
                //increment the target's health
                target.incrementHealth(healPower);
                std::cout << target.getName() << " now has " << target.getHealth() << " health!" << std::endl;
                
            } else {
                std::cout << target.getName() << " is already at full health!" << std::endl;
            }
        }
};

//function to play the game and interact with the player objects
void playGame(std::vector<warrior*>& warriors, std::vector<healer*>& healers) {
    while (true) {
    //print the warriors and healers
    std::cout << "Warriors: " << std::endl;
    for (size_t i = 0; i < warriors.size(); i++) {
        warriors[i]->printPlayer();
    }
    std::cout << "Healers: " << std::endl;
    for (size_t i = 0; i < healers.size(); i++) {
        healers[i]->printPlayer();
    }
    std::cout << "who would you like to play as?" << std::endl;
    std::cout << "1. warrior" << std::endl;
    std::cout << "2. healer" << std::endl;
    std::cout << "3. exit" << std::endl;
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        //print all the warriors with index
        for (size_t i = 0; i < warriors.size(); i++) {
            std::cout << i << ". " << warriors[i]->getName() << std::endl;
        }
        int warriorChoice;
        std::cin >> warriorChoice;
        std::cout << "You have chosen to play as " << warriors[warriorChoice]->getName() << "here is your information:" << std::endl;
        warriors[warriorChoice]->printPlayer();
        std::cout << "Who would you like to attack?" << std::endl;
        std::cout << "1. healer" << std::endl;
        std::cout << "2. warrior" << std::endl;
        int attackChoice;
        std::cin >> attackChoice;
        if (attackChoice == 1) {
            std::cout << "Who would you like to attack?" << std::endl;
            for (size_t i = 0; i < healers.size(); i++) {
                std::cout << i << ". " << healers[i]->getName() << std::endl;
            }
            int healerChoice;
            std::cin >> healerChoice;
            if (warriors[warriorChoice]->attack(*healers[healerChoice]) == 1) {
                //remove the healer from the vector
                healers.erase(healers.begin() + healerChoice);
            }
        }
        else if (attackChoice == 2) {
            std::cout << "Who would you like to attack?" << std::endl;
            for (size_t i = 0; i < warriors.size(); i++) {
                std::cout << i << ". " << warriors[i]->getName() << std::endl;
            }
            int warriorChoice;
            std::cin >> warriorChoice;
            if (warriors[warriorChoice]->attack(*warriors[warriorChoice]) == 1) {
                //remove the warrior from the vector
                warriors.erase(warriors.begin() + warriorChoice);
            }
        }  
        else {
            std::cout << "Invalid choice" << std::endl;
        }

    }
    else if (choice == 2) {
        std::cout << "You have chosen to play as a healer" << std::endl;
        for (size_t i = 0; i < healers.size(); i++) {
            std::cout << i << ". " << healers[i]->getName() << std::endl;
        }
        int healerChoice;
        std::cin >> healerChoice;
        healers[healerChoice]->printPlayer();
        std::cout << "Who would you like to heal?" << std::endl;
        std::cout << "1. warrior" << std::endl;
        std::cout << "2. healer" << std::endl;
        int healChoice;
        std::cin >> healChoice;
        if (healChoice == 1) {
            std::cout << "Who would you like to heal?" << std::endl;
            for (size_t i = 0; i < warriors.size(); i++) {
                std::cout << i << ". " << warriors[i]->getName() << std::endl;
            }
            int warriorChoice;
            std::cin >> warriorChoice;
            healers[healerChoice]->heal(*warriors[warriorChoice]);
        }
        else if (healChoice == 2) {
            std::cout << "Who would you like to heal?" << std::endl;
            for (size_t i = 0; i < healers.size(); i++) {
                std::cout << i << ". " << healers[i]->getName() << std::endl;
            }
            int healerChoice;
            std::cin >> healerChoice;
            healers[healerChoice]->heal(*healers[healerChoice]);
        }
        else {
            std::cout << "Invalid choice" << std::endl;
        }
    } else if (choice == 3) {
        std::cout << "Exiting game..." << std::endl;
        exit(0);
    }
    else {
        std::cout << "Invalid choice" << std::endl;
    }
    }
}

//main function to create the player objects and start the game
int main() {
    //create a vector of players
    std::vector<warrior*> warriors;
    std::vector<healer*> healers;


    //a while loop to create the player objects then start the game
    std::cout << "Welcome to the game!" << std::endl;
    while (true) {
        std::cout << "What do you want to do?" << std::endl;
        std::cout << "1. Create a warrior" << std::endl;
        std::cout << "2. Create a healer" << std::endl;
        std::cout << "3. Play the game" << std::endl;
        std::cout << "4. Exit" << std::endl;
        int choice;
        std::cin >> choice;
        if (choice == 1) {
            std::string warriorName;
            std::cout << "Enter the name of warrior: ";
            std::cin >> warriorName;
            warrior* warrior1 = new warrior(warriorName);
            warriors.push_back(warrior1);
        }
        else if (choice == 2) {
            std::string healerName;
            std::cout << "Enter the name of healer: ";
            std::cin >> healerName;
            healer* healer1 = new healer(healerName);
            healers.push_back(healer1);
        }
        else if (choice == 3) {
            playGame(warriors, healers);
            break;
        }
        else if (choice == 4) {
            break;
        }
        else {
            std::cout << "Invalid choice" << std::endl;
        }
    }

    // Add cleanup before returning
    for (auto* w : warriors) {
        delete w;
    }
    for (auto* h : healers) {
        delete h;
    }
    return 0;
}
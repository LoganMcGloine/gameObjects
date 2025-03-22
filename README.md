# gameObjects
A program that explores object oriented programming in c++


gameObjects.cpp is a simple text based game that explores object oriented programming in c++.
The program contains a base class for a player which is an abstract class that contains the common attributes and methods for all players.
There are two derived classes of player: warrior and healer.

The warrior class is a player derived class that contains an attack method that allows the warrior to attack another player.
This method takes a player object as a parameter and reduces the player's health by the warrior's attack power, and if the player's health is reduced to 0 or below, the player is dead and the player is deconstructed.

The healer class is a player derived class that contains a heal method that allows the healer to heal another player.
This method takes a player object as a parameter and increases the player's health by the healer's heal power.

The program also contains a function to play the game which allows warriors and healers to interact with each other in a game like fashion.

This program demonstrates the following Object-Oriented Programming concepts:

- Inheritance:
    - The warrior and healer classes inherit attributes (health, name, money) and methods from the player base class
    - This demonstrates code reuse and establishes an is-a relationship (a warrior is a player)

- Polymorphism:
    - Runtime polymorphism is achieved through virtual functions in the player class
    - Each derived class (warrior/healer) provides its own implementation of virtual methods    like getPlayerTypeName()
    - This allows different player types to be treated uniformly through base class pointers

- Encapsulation:
    - Data (health, name, money) is protected/private and only accessible through public methods
    - Implementation details are hidden from outside code
    - Public interfaces (like getHealth(), getName()) control how the object's state can be accessed and modified

- Abstraction:
    - The player class is abstract (contains pure virtual functions) and defines a common interface
    - Complex implementation details are hidden behind simple method calls
    - The abstract base class serves as a contract that derived classes must fulfill











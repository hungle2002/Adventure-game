# Adventure game
## Implement: 
C++ (OOP)
## Description:
### 3.1 Game Concept:
- This is a role-playing game, in which players will be given three characters: Tank, Warrior, and Wizard. Each character has basic stats including: HP (health points), ATK (attack), DEF (defense), and their own unique skills. Specifically:
Tank has an additional stat called ARM (armor) and a skill to buff ARM. When attacked, damage will first be reduced from ARM before being taken from HP. For example, if the enemy's attack value is _ATK (_ATK >DEF):
	- ARM = ARM - (_ATK -DEF).
	- If ARM < 0 then:
	- HP = HP + ARM
	- ARM = 0;
- Warrior can penetrate the enemy's armor with their attacks, along with a skill to boost ATK in one turn.
- Wizard has a skill where their attack strength will be multiplied by 1.5 after going through the enemy's defense. For example, if the enemy's DEF value is _DEF, when Wizard attacks the enemy (_ARM, _HP):
	- _ARM = ARM - 1.5*(_ATK - DEF)
	- If ARM < 0 then:
	- HP = HP + ARM
	- ARM = 0;
- Wizard's skill is to deal direct damage to all enemies' HP (amount increases with skill level).
- Characters can only use their skill once per chapter, and after each chapter, their skill and HP will be restored, and players will be rewarded with some money.
- Players can use their money to upgrade the skill levels or buy equipment to increase their characters' stats. The available equipment are:
	- Helmet: increases DEF
	- Armor: increases DEF
	- Weapon: increases ATK
	- DrugArm: restores ARM (only usable for Tank)
	- DrugHp: increases HP
- Each character can equip one Helmet, one Armor, and one Weapon at most. When buying new equipment for a character, the old equipment will be removed and replaced with the new one.
Character skills will be divided into three levels: 1, 2, 3, with increasing stats:
	- Tank (buffARM): 500 -> 700 -> 1000
	- Warrior (buffATK): 500 -> 700 -> 1000
	- Wizard (attack all): 200 -> 300 -> 500
### 3.2 Game Structure:
#### 3.2.1 Game structure diagram (attached draw.io file)
- The game structure is divided into 3 main groups:
	- Skill: containing information about skills (abstract class)
	- Item: containing information about equipment (abstract class)
	- Character: containing information about characters (abstract class)
- There are also child classes:
	- Player: containing information about the player
	- Enemy: containing information about the enemy
	- Store: containing information about the store
	- Battle: containing information about the enemy and player to conduct the game.
#### 3.2.2 Skill class (in skill.h file)
- Skill class will be an abstract class, containing the following parameters:
	- state: usage state (1: not used, 0: used)
	- level: level of the skill (1, 2, 3)
	- name: name of the skill
	- description: description of the skill
	- target: target of the skill (enemy, all enemies, self, etc.)
	- power: strength of the skill (damage, heal, buff, etc.)
	- mpCost: cost of the skill in MP (magic points)
	- use(): a virtual function that will be implemented by each subclass to define the specific effects of the skill when used by a 
#### 3.2.3 Item class (in item.h file)
-The Item class will also be an abstract class, containing information about:
	- name: the name of the item
	- description: a brief description of the item's effects
	- price: the cost of the item in the store
	- use(): a virtual function that will be implemented by each subclass to define the specific effects of the item when used by a character.
#### 3.2.4 Character class (in character.h file)
-The Character class will be an abstract class, containing information about:
	- name: the name of the character
	- HP: the health points of the character
	- ATK: the attack stat of the character
	- DEF: the defense stat of the character
	- ARM: the armor stat of the character (only applicable to Tank)
	- level: the level of the character, which determines its stats and the level of its skills
	- skill1, skill2, skill3: pointers to Skill objects representing the character's skills
	- helmet, armor, weapon: pointers to Item objects representing the character's equipment
	- useSkill(int skillIndex): a function that will use the skill corresponding to the specified index (1, 2, or 3)
	- equipItem(Item* item): a function that will equip the specified item, replacing the current item of the same type
	- unequipItem(Item* item): a function that will remove the specified item from the character's equipment, replacing it with a default item of the same type.
#### 3.2.5 Player class (in player.h file)
-The Player class will inherit from the Character class, and will also contain information about:
	- balance: the amount of money the player currently has
	- inventory: a vector of Item pointers representing the items the player currently has in their inventory
	- buyItem(Item* item): a function that will add the specified item to the player's inventory, subtracting the item's price from the player's balance
	- sellItem(Item* item): a function that will remove the specified item from the player's inventory, adding the item's price to the player's balance.
#### 3.2.6 Enemy class (in enemy.h file)
-The Enemy class will also inherit from the Character class, and will contain information about the enemy's type and any special abilities or weaknesses it may have. Each enemy will have a unique name and stats.
### 3.3 How to play:
- Firstly, when entering the game, there will be a basic introduction interface about how to play.

- The player will choose the level they want to participate in (can only participate in the level when they have won the previous level). Therefore, when just starting, the player will choose the first level.

- After selecting the level, the program will print out the parameters of the player's characters regarding ATK, DEF, ARM, HP, and skill level along with the amount of money the player has ($500). These are the default parameters of the characters.

##### Upgrade skills

- Next, the player will choose whether to upgrade their skills or not. If they want to, they will press 1 and 0 to continue.

- Suppose the player chooses 1 and starts upgrading their skills.

- Next, the player will enter the character they want to upgrade.

- Suppose the player chooses to upgrade the skill of the Tank character. At this point, the program will show the price to upgrade, the cost of upgrading, and the status after upgrading the skill. If the player chooses to upgrade, they will upgrade if the player has enough money. The program will print out a successful upgrade if they have enough money, and if they don't, the program will display an error message.

- Then the player can choose whether to continue upgrading or not. If they want to, they will continue upgrading.

##### Go to the store to buy equipment
- After selecting the store, the store interface will appear:

- The player will enter the name of the equipment they want to buy, for example, Basic Armor.

- Then choose the character they want to equip and finally see the character's stats after equipping that equipment.

- In the example, the player chooses to buy Basic Armor with a stat of +100DEF. Then, the Tank character will increase DEF from 500 to 600 after equipping the item.

- Then, if the player wants to continue upgrading, they will press 1, and if not, they will press 0 to exit the store.

##### Battle

- After leaving the store, the player will engage in a battle with the enemy.

- The first turn will be the player's, and they will take turns attacking the selected enemy with their characters, Tank, Warrior, and Wizard, respectively. The player can activate skills if they want. However, skills can only be used once per level. If they pass the level, the skills will be reset.

	- Turn of Tank

	- Turn of Warrior

	- Turn of Wizard

	- After the player finishes their turn, it will be the enemy's turn. The enemy will attack in the order of Tank, Warrior, and then Wizard by default.

- Then it will be the player's turn again, and this will be repeated until all enemies are defeated or all player characters are defeated.

- Player's turn

- Enemy's turn

- Player's turn

- After all enemies are defeated, the player will win.

- Then, the player can choose whether to continue playing or not. If they want to, they will return to the level selection interface, and if not, they will exit the game.

- When continuing chapter 2, players will be given additional money after winning and can go to the shop to buy equipment or upgrade their skills.

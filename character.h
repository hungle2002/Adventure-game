#ifndef CHARACTER_H
#define CHARACTER_H
#include "main.h"
#include "store.h"
#include "skill.h"
class Character{
protected:
    int DEF;
    int ATK;
    int HP;
    Type type;
    Item* items[3];
    Skill* skill;
public:
    Character(){
        items[0] = new Helmet();
        items[1] = new Armor();
        items[2] = new Weapon();
    }
    ~Character(){
        delete items[0];
        delete items[1];
        delete items[2];
    }
    virtual void attack(Character* c) =0;
    virtual void defend(int _ATK, Type _type) =0;
    virtual void turnOnSkill()=0;
    virtual void putOnDrugArm(Item* item){
        return;
    }
    virtual void print() = 0;
    virtual int getARM(){
        return 0;
    }
    virtual void resetHP() = 0;
    void putOn(Item* item){
        switch(item->getType()){
            case Helmets:
            // weared
                if (items[0]->getPrice() > 0){
                    // put off
                    DEF -= items[0]->getNum();
                }
                // put on
                DEF += item->getNum();
                items[0] = item;
                break;
            case Armors:
            // weared
                if (items[1]->getPrice() > 0){
                    // put off
                    DEF -= items[1]->getNum();
                }
                // put on
                DEF += item->getNum();
                items[1] = item;
                break;
            case Weapons:
            // weared
                if (items[2]->getPrice() > 0){
                    // put off
                    ATK -= items[2]->getNum();
                }
                // put on
                ATK += item->getNum();
                items[2] = item;
                break;
            case DrugHps:
                HP += item->getNum();
                break;
            default:
                break;
        }
    }
    bool alive(){
        return HP > 0;
    }
    friend class Player;
    friend class Battle;
    friend class Enemy;
};

class Tank:public Character{
private:
    int ARM; // armor
    int defaultTank[4] = {500, 1000, 200, 500};
public:
    // constructer
    Tank(){
        DEF = defaultTank[0];
        HP = defaultTank[1];
        ATK = defaultTank[2];
        ARM = defaultTank[3];
        type = Tanks;
        skill = new SkillTank();
    }
    
    // destructer
    ~Tank(){
        delete skill;
    }
    // get ARM
    int getARM(){
        return ARM;
    }

    // put on DrugArm
    void putOnDrugArm(Item* item){
        ARM += item->getNum();
    }
    
    // attack by normal DEF
    void attack(Character* c){
        c->defend(this->ATK, this->type);
    }

    // attack to ARM
    void defend(int _ATK, Type _type){
        if(_ATK < DEF) return;
        // Boss attack through ARM
        if(_type == Bosses){
            HP -= (_ATK - DEF);
        }
        else if(_type == Monsters){
            ARM = ARM - (_ATK - DEF);
            if(ARM < 0){
                HP = HP + ARM;
                ARM = 0;
            }
        }
        if(HP < 0) HP = 0;
    }

    // buff ARMOR
    void turnOnSkill(){
        ARM += skill->getNum();
        skill->turnOn();
    }

    // reset HP
    void resetHP(){
        HP = defaultTank[0];
    }

    // print info
    void print(){
        cout << "Tank: "<<endl;
        cout << "ATK: "<<ATK<<"\nDEF: "<<DEF <<"\nHP: "<<HP<<"\nARM: "<<ARM<<endl;
    }
};

class Warrior:public Character{
private:
    bool skillForWarrior;
    int defaultWarrior[3] = {300, 700, 700};

public:
    // constructor
    Warrior(){
        skillForWarrior = 0;
        DEF = defaultWarrior[0];
        HP = defaultWarrior[1];
        ATK = defaultWarrior[2];
        type = Warriors;
        skill = new SkillWarrior();
    }
    // destructer
    ~Warrior(){
        delete skill;
    }
    // attack through ARM
    void attack(Character* c){
        if(skillForWarrior == 1){
            // buff ATK in 1 turn
            c->defend(this->ATK + this->skill->getNum(), this->type);
            skillForWarrior = 0;
        }
        else{
            c->defend(this->ATK, this->type);
        }
    }

    // attack to ARM
    void defend(int _ATK, Type _type){
        if(_ATK > DEF){
            HP -= (_ATK - DEF);
        }
        if(HP < 0) HP = 0;
    }

    // buff ATK on one turn
    void turnOnSkill(){
        skillForWarrior = 1;
        skill->turnOn();
    }

    // reset HP
    void resetHP(){
        HP = defaultWarrior[0];
    }
    // print Info
    void print(){
        cout << "Warrior: "<<endl;
        cout << "ATK: "<<ATK<<"\nDEF: "<<DEF <<"\nHP: "<<HP<<endl;
    }
};

class Wizard:public Character{
private:
    int defaultWizard[3] = {100, 400, 1000};
public:
    // constructor
    Wizard(){
        DEF = defaultWizard[0];
        HP = defaultWizard[1];
        ATK = defaultWizard[2];
        type = Wizards;
        skill = new SkillWizard();
    }
    // destructer
    ~Wizard(){
        delete skill;
    }
    // attack *1.5 to ARM
    void attack(Character* c){
        c->defend(this->ATK, this->type);
    }

    // normal defend
    void defend(int _ATK, Type _type){
        if(_ATK > DEF){
            HP -= (_ATK - DEF);
        }
        if(HP < 0) HP = 0;
    }

    // attack All enemy
    void turnOnSkill(){
        skill->turnOn();
    }

    // reset HP
    void resetHP(){
        HP = defaultWizard[0];
    }
    // print Info
    void print(){
        cout << "Wizard: "<<endl;
        cout << "ATK: "<<ATK<<"\nDEF: "<<DEF <<"\nHP: "<<HP<<endl;
    }
};

class Monster:public Character{
private:
    int ARM;
    int defaultMonster[4] = {300, 2000, 1000, 500};
public:
    // constructor
    Monster(){
        DEF = defaultMonster[0];
        HP = defaultMonster[1];
        ATK = defaultMonster[2];
        ARM = defaultMonster[3];
        type = Monsters;
        skill = NULL;
    }
    // destructer
    ~Monster(){
        delete skill;
    }
    // get ARM
    int getARM(){
        return ARM;
    }
    // attack normal
    void attack(Character* c){
        c->defend(this->ATK, this->type);
    }
    // normal defend
    void defend(int _ATK, Type _type){
        if(_ATK < DEF) return;
        // warior attack through ARM
        if(_type == Warriors){
            HP -= (_ATK - DEF);
        }
        // *1.5 to ARM
        else if(_type == Wizards){
            _ATK -= DEF;
            ARM = ARM - 1.5 * _ATK;
            if(ARM < 0){
                HP = HP + ARM;
                ARM = 0;
            }
        }
        else{
            if(ATK > DEF){
                ARM -= (ATK -DEF);
                if(ARM < 0){
                    HP += ARM;
                    ARM = 0;
                }
            }
        }
        if(HP < 0) HP = 0;
    }

    // no skill
    void turnOnSkill(){
        return;
    }

    // print Info
    void print(){
        cout << "Monster: "<<endl;
        cout << "ATK: "<<ATK<<"\nDEF: "<<DEF <<"\nHP: "<<HP<<"\nARM: "<<ARM<<endl;
    }

    // reset HP
    void resetHP(){
        HP = defaultMonster[0];
    }
    friend class Enemy;
};

class Boss:public Character{
private:
    int ARM;
    int defaultBoss[4] = {500, 10000, 1200, 2000};
public:
    // constructor
    Boss(){
        DEF = defaultBoss[0];
        HP = defaultBoss[1];
        ATK = defaultBoss[2];
        ARM = defaultBoss[3];
        type = Bosses;
        skill = NULL;
    }
    // destructer
    ~Boss(){
        delete skill;
    }
    // get ARM
    int getARM(){
        return ARM;
    }
    
    // attack normal
    void attack(Character* c){
        c->defend(this->ATK, this->type);
    }

    // normal defend
    void defend(int _ATK, Type _type){
        // warior attack through ARM
        if(_type == Warriors){
            HP -= (_ATK - DEF);
        }
        // *1.5 to ARM
        else if(_type == Wizards){
            _ATK -= DEF;
            ARM = ARM - 1.5 * _ATK;
            if(ARM < 0){
                ARM = 0;
                HP = HP + ARM;
            }
        }
        else{
            if(ATK > DEF){
                ARM -= (ATK -DEF);
                if(ARM < 0){
                    HP += ARM;
                    ARM = 0;
                }
            }
        }
        if(HP < 0) HP = 0;
    }

    // no skill
    void turnOnSkill(){
        return;
    }

    // reset HP
    void resetHP(){
        HP = defaultBoss[0];
    }

    // print Info
    void print(){
        cout << "Boss: "<<endl;
        cout << "ATK: "<<ATK<<"\nDEF: "<<DEF <<"\nHP: "<<HP<<"\nARM: "<<ARM<<endl;
    }
};  

class Player{
private:
    int money;
    Character* c[3];
public:
    // constructer
    Player(){
        // default money
        money = 500;
        c[0] = new Tank();
        c[1] = new Warrior();
        c[2] = new Wizard();
    }
    // destructer
    ~Player(){
        for(int i=0; i<3; i++){
            delete c[i];
        }
    }
   // buy item for heroes
    void goToStore(Store* store){
            // print store
        store->printItems();
        int flag = 1;
        while(flag){
            cout << "\n   Please choose what you want! \n";
            cout << "Basic Armor for example.\n";
            string str1;
            string str2;
            Item* curItem = NULL;
            while(1){
                cout << "Text here: ";
                cin >> str1 >> str2;
                curItem = store->getItem(str1+" "+str2);
                // cannot find
                if(!curItem)
                {
                    cout << "We can't find your equipment.";
                }
                else{
                    break;
                }
            }
                // check money
            if(this->money < curItem->getPrice()){
                cout <<"    Sorry you don't have enough money.\nNow you have only "<<this->money<<"$\n";
                cout << "   Do you want to buy something more ?\n";
                cout << "Press 1 to countinue and 0 for return. Your choice is: ";
                cin >> flag;
                continue;
            }
                // pay for item
                this->money -= curItem->getPrice();
                // choose heroes to equip
            cout << "\n   Please choose what heroes want to equip! \n";
            cout << "Warrior ,Tank or Wizard\n";
                // input name of heroes
            while(1)
            {
                cout << "Text here: ";
               cin >> str1;
                //--------------put on item------------------------
                    // DrugArm only put on Tank
                if(curItem->getType() == DrugArms){
                    if(str1 == "Tank"){
                        cout <<"    == Equip successfull ==";
                    }
                    else{
                        cout << "!! You can only use DrugArms for Tank !!\n";
                        c[0]->putOnDrugArm(curItem);
                        cout <<"    == Equip successfull ==\n";
                        c[0]->print();
                    }
                    break;
                }
                else{
                        // Other Items
                    string str[3] = {"Tank","Warrior", "Wizard"};
                    bool flag1 = 0;
                    for(int i=0; i<3; i++){
                        if(str1 == str[i]){
                            c[i]->putOn(curItem);
                            cout <<"    == Equip successfull ==\n";
                            c[i]->print();
                            flag1 = 1;
                        }
                    }
                    if(flag1) break;
                    cout << "We can't find your heroes. Please try again!\n";
                } 
            }
            //----------------------------------------------------------

            cout << "\n     Do you want to buy something more ?\n";
            cout << "Press 1 to countinue and 0 for return. Your choice is: ";
            cin >> flag;
        }
        cout << "\n     Thanks for your visiting our store !!";
    }
   // earn money after 1 chap
    void earnMoney(int _money){
        money += _money;
    }
    // check player loss : all heroes die
    bool checkLoss(){
        bool flag = 1;
        for(int i=0; i<3; i++){
            if(c[i]->alive()){
                flag = 0;
            }
        }
        return flag;
    }
    // printFull
    void printFull(){
        cout << "            Tanker       Warrior       Wizard ";
        int k = 13; // space
        cout << "\nATK: ";
        for(int i=0; i<3; i++){
            cout << setw(k)<<c[i]->ATK;
        }
        cout << "\nDEF: ";
        for(int i=0; i<3; i++){
            cout << setw(k)<<c[i]->DEF;
        }
        cout << "\nARM: ";
        for(int i=0; i<1; i++){
            cout << setw(k)<<c[i]->getARM();
        }
        cout << "\nHP : ";
        for(int i=0; i<3; i++){
            cout << setw(k)<<c[i]->HP;
        }
        cout << "\nLevel   ";
        cout << "\nskill :";
        k=9;
        for(int i=0; i<3; i++){
            if(i>0) k=13;
            cout << setw(k)<<c[i]->skill->getLevel();
        }
        cout << endl;
    }
    // printHpArm
    void printHpArm(){
        cout << "            Tanker       Warrior       Wizard ";
        int k = 13; // space
        cout << "\nARM: ";
        for(int i=0; i<1; i++){
            cout << setw(k)<<c[i]->getARM();
        }
        cout << "\nHP : ";
        for(int i=0; i<3; i++){
            cout << setw(k)<<c[i]->HP;
        }
        cout << endl; 
    }
    friend class Enemy;
    friend class Battle;
};

class Enemy{
private:
    int nMonster;
    int nBoss;
    Character* cMon[100];
    Character* cBoss[100];
public:
    Enemy(){
        nMonster=0;
        nBoss = 0;
    }
    Enemy(int chap){
        if(chap == 1){
            nMonster = 2;
            nBoss = 0;
        }
        else if(chap == 2){
            nMonster = 4;
            nBoss = 0;
        }
        else if(chap == 3){
            nMonster = 2;
            nBoss = 1;
        }
        else{
            nMonster = 0;
            nBoss = 2;
        }

        // init Monster and Boss
        for(int i=0; i<nMonster; i++){
            cMon[i] = new Monster();
        }
        for(int i = 0; i<nBoss; i++){
            cBoss[i] = new Boss();
        }
    }
    ~Enemy(){
        for(int i=0; i<nMonster; i++){
            delete cMon[i];
        }
        for(int i=0; i<nBoss; i++){
            delete cBoss[i];
        }
    }
    // Enemy attack player
    void attack(Player * player){
        cout<<"-------------------------------------------------------------------------------------";
        cout << "\n   Enemy turn:\n";
        for(int i = 0 ; i<nMonster; i++){
            if(cMon[i]->alive()){
                // atactk alive boss Tank-Warrior-Wizard
                for(int j=0; j<3; j++){
                    if(player->c[j]->alive()){
                        cMon[i]->attack(player->c[j]);
                        cout << "Heroes after "<< "Monster "<<i<<" attack: \n";
                        player->printHpArm();
                        break;
                    }
                }
            }
        }
        for(int i = 0 ; i<nBoss; i++){
            if(cBoss[i]->alive()){
                // atactk alive boss Tank-Warrior-Wizard
                for(int j=0; j<3; j++){
                    if(player->c[j]->alive()){
                        cBoss[i]->attack(player->c[j]);
                        cout << "Heroes after "<< "Boss "<<i<<"attack:\n";
                        player->printHpArm();
                    }
                }
            }
        }
    }
    // check Player wins ; all monster die
    bool checkWin(){
        bool flag = 1;
        for(int i=0; i<nMonster; i++){
            if(cMon[i]->alive()){
                flag = 0;
            }
        }
        for(int i=0; i<nBoss; i++){
            if(cBoss[i]->alive()){
                flag = 0;
            }
        }
        return flag;
    }
    // print enemy
    void printFull(){
        cout <<"         ";
        for(int i=0; i<nMonster; i++){
            cout <<"    Monster "<<i;
        }
        for(int i=0; i<nBoss; i++){
            cout <<"    Boss "<<i+nMonster;
        }
        
        int k = 13; // space
        cout << "\nATK: ";
        for(int i=0; i<nMonster; i++){
            cout << setw(k)<<cMon[i]->ATK;
        }
        for(int i=0; i<nBoss; i++){
            cout << setw(k)<<cBoss[i]->ATK;
        }
        cout << "\nDEF: ";
        for(int i=0; i<nMonster; i++){
            cout << setw(k)<<cMon[i]->DEF;
        }
        for(int i=0; i<nBoss; i++){
            cout << setw(k)<<cBoss[i]->DEF;
        }
        cout << "\nARM: ";
        for(int i=0; i<nMonster; i++){
            cout << setw(k)<<cMon[i]->getARM();
        }
        for(int i=0; i<nBoss; i++){
            cout << setw(k)<<cBoss[i]->getARM();
        }
        cout << "\nHP : ";
        for(int i=0; i<nMonster; i++){
            cout << setw(k)<<cMon[i]->HP;
        }
        for(int i=0; i<nBoss; i++){
            cout << setw(k)<<cBoss[i]->HP;
        }
        cout << endl;

    }
    // print hp and ARM
    void printHpArm(){
        int k = 13;
        cout <<"         ";
        for(int i=0; i<nMonster; i++){
            cout <<"    Monster "<<i;
        }
        for(int i=0; i<nBoss; i++){
            cout <<"    Boss "<<i+nMonster;
        }
        cout << "\nARM: ";
        for(int i=0; i<nMonster; i++){
            cout << setw(k)<<cMon[i]->getARM();
        }
        for(int i=0; i<nBoss; i++){
            cout << setw(k)<<cBoss[i]->getARM();
        }
        cout << "\nHP : ";
        for(int i=0; i<nMonster; i++){
            cout << setw(k)<<cMon[i]->HP;
        }
        for(int i=0; i<nBoss; i++){
            cout << setw(k)<<cBoss[i]->HP;
        }
        cout << endl;
    }
    friend class Player;
    friend class Battle;
};

class Battle{
private:
    Player* player;
    Enemy* enemy;
    Store* store;
    bool chapters[5]{0};
public:
    Battle(){
        store = new Store();
        player = new Player();
    }
    ~Battle(){
        delete player;
        delete enemy;
        delete store;
    }
    //uplevel for heroes
    void upLevel(){
        string str;
        string type[3] = {"Tank", "Warrior", "Wizard"};
        string typeSkill[3] = {"Buff ARM", "Buff ATK", "Attack All enemy"};
        // upgrade skill many time
        while(1){
            cout << "   Please choose heroes to upgrade(Tank, Wizard, Warrior).\n Text here:";
            cin >> str;
            // choose heroes
            for(int i=0; i<3; i++){
                if(str == type[i]){
                    // print option
                    int level = player->c[i]->skill->getLevel();
                    int cost = player->c[i]->skill->cost();
                    // check level
                    if(level == 4){
                        cout <<"This is max level !!\n";
                        break;
                    } 
                    cout << "Skill "+str+"\n    Level: "+to_string(level)+"->"+to_string(level+1)<<" cost "<<cost<<" $\n";
                    cout << typeSkill[i] <<" : "<<player->c[i]->skill->getNum()<<" -> "<<player->c[i]->skill->getNextNum()<<endl;
                    cout << "\n     Do you want to upgrade? 1:Yes, 0:No ";
                    int n;
                    cin >> n;
                    if(n){
                        if(player->money > cost){
                            if(player->c[i]->skill->upLevel()){
                                cout << "   == Successfully ==\n";
                                // take money
                                player->money -= cost;
                            }
                        }
                        else cout << "Sorry you don't have enough money\n";
                    }
                }
            }
            int n;
            cout << "Do you want to upgrade more ? 1:Yes, 0:No ";
            cin >> n;
            if(n==0) break;
        }
    }
    // Player attacks Enemy
    void attackEnemy(){
        int n=0;
        cout<<"-------------------------------------------------------------------------------------";
        cout << "\n   Your attack turn:\n";
        // Tank attack
        while(1){
            cout << "\n   Tank attack: ";
            // check skill to use
            if(player->c[0]->skill->checkUsed()){
                cout << "\n     Do you want to use Tank skill: buffARM (1:Yes / 0:No ) ";
                cin >> n;
                if(n){
                    player->c[0]->turnOnSkill();
                    cout << "       == Successful == \n";
                    player->c[0]->print();
                }
            }
            cout << "Please input enemy (0 1 2...) :" ;
            cin >>n;
            // attack monster
            if(n<enemy->nMonster){
                player->c[0]->attack(enemy->cMon[n]);
                break;
            }
            else{
                n -= enemy->nMonster;
                if(n<enemy->nBoss){
                    player->c[0]->attack(enemy->cBoss[n]);
                    break;
                }
                else{
                    cout << "We can't find your monster!. Please try again!";
                }
            }
        }
        cout << "Enemy after Tank attack: \n";
        enemy->printHpArm();
        // Warrior attack
        while(1){
            cout << "\n   Warrior attack: (Warrior attack through ARM)";
            // check skill to use
            if(player->c[1]->skill->checkUsed()){
                cout << "\n     Do you want to use Warrior skill: buff ATK in one turn (1:Yes / 0:No ) " ;
                cin >> n;
                if(n){
                    player->c[1]->turnOnSkill();
                    cout << "       == Successful == \n";
                }
            }
            cout << "Please input enemy (0 1 2....) :";
            cin >>n;
            // attack monster
            if(n<enemy->nMonster){
                player->c[1]->attack(enemy->cMon[n]);
                break;
            }
            else{
                n -= enemy->nMonster;
                if(n<enemy->nBoss){
                    player->c[1]->attack(enemy->cBoss[n]);
                    break;
                }
                else{
                    cout << "We can't find your monster!. Please try again!";
                }
            }
        }
        cout << "Enemy after Warrior attack: \n";
        enemy->printHpArm();
        // Wizard attack
        while(1){
            cout << "\n   Wizard attack: (after -DEF, Wizard ATK X1.5 to ARM and HP)";
            // check skill to use
            if(player->c[2]->skill->checkUsed()){
                cout << "\n     Do you want to use Wizard skill: attack all enemy (1:Yes / 0:No ) ";
                cin >> n;
                if(n){
                    player->c[2]->turnOnSkill();
                    // attack all enemy to HP
                    for(int i=0; i<enemy->nMonster; i++){
                        if(enemy->cMon[i]->alive()){
                            enemy->cMon[i]->HP -= player->c[2]->skill->getNum();
                        }
                    }
                    for(int i=0; i<enemy->nBoss; i++){
                        if(enemy->cBoss[i]->alive()){
                            enemy->cBoss[i]->HP -= player->c[2]->skill->getNum();
                        }
                    }
                    cout << "       == Successful == \n";
                    // print enemy
                    enemy->printHpArm();
                }
            }
            cout << "Please input enemy (0 1 2....) :";
            cin >>n;
            // attack monster
            if(n<enemy->nMonster){
                player->c[2]->attack(enemy->cMon[n]);
                break;
            }
            else{
                n -= enemy->nMonster;
                if(n<enemy->nBoss){
                    player->c[2]->attack(enemy->cBoss[n]);
                    break;
                }
                else{
                    cout << "We can't find your monster!. Please try again!";
                }
            }
        }
        cout << "Enemy after Wizard attack: \n";
        enemy->printHpArm();
    }
    // play
    void play(){
        cout << "                                Welcome to my Heroes game !!\n";
        cout << "In this game, you will have three heroes : Tank, Warrior and Wizard. Tank have Armor, Warrior can attack through ARM and Wizard will attack X1.5 to ARM (after -DEF). We will go through 4 chapter to kill all monster and boss to win. In every chapter, you can use your heroes skill one time and earn some money after every chapter. You can use money to buy item in store and upgrade your heroes skill !!";
        cout << "\n                                   Goods luck!!\n\n";
        int chap = 0;
        while(1){
            // reset skill
            for(int i=0; i<3; i++){
                player->c[i]->skill->reset();
            }
            // reset HP
            for(int i=0; i<3; i++){

            }
            while(1){
                cout << "Let choose chapter (1,2,3,4) :";
                cin >> chap;
                if(chap > 1 && chapters[chap-1] == 0){
                    cout << "You need to win chap "<< chap-1 <<" !!"<<endl;
                }
                else{
                    break;
                }
            }
            enemy = new Enemy(chap);
            cout << "\n     You have "<< player->money << "$ now.\n";
            cout << "   Your heroes information\n";
            player->printFull();

                // upgrade skill
            int n;
            cout << "\nDo you want to upgrade your skill ? 1:Yes, 0:No  ";
            cin >> n;
            if(n){
                upLevel();
            }

                // go to store
            cout << "\nDo you want to go to store for somthing ? 1:Yes, 0:No ";
            cin >> n;
            if(n){
                player->goToStore(store);
            }

                // out of store
            cout << "\n     You have "<< player->money << "$ now.\n";
            cout << "   Your heroes information\n";
            player->printFull();
            cout << "   Your enemy in this chapter:\n";
            enemy->printFull();

            // battle takes place
            while(1){
                attackEnemy();
                if(enemy->checkWin()){
                    cout << "\n         Congratulation! \1 You win chap "<< chap;
                    cout << "\nLet go to another chap !!";
                    int n;
                    cout << "\n 1 for continuing and 0 for out!!\n";
                    cin >> n;
                    if(n==0)
                    {
                        cout << "\n\n          Thank you for visiting my game !!\n\n";
                        return;
                    } 
                    // update chapter 
                    chapters[chap] = 1;
                    // take money after winning
                    player->earnMoney(500*chap);
                    break;
                }
                enemy->attack(player);
                if(player->checkLoss()){
                    cout << "\n         You loss \n";
                    cout << "Let try again or go to store and buy some thing!!";
                    int n;
                    cout << "1 for continuing and 0 for out!!";
                    if(n==0)
                    {
                        cout << "\n\n          Thank you for visiting my game !!\n\n";
                        return;
                    } 
                    break;
                }
            }
        }
    }

friend class Character;
friend class Player;
friend class Enemy;
};

#endif
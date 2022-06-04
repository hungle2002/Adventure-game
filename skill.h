#ifndef SKILL_H
#define SKILL_H
#include "main.h"

class Skill{
protected:
    bool state;  // 1:unused  0:used
    int level;
    int priceToUp;
    int num;
public:
    virtual bool upLevel() = 0;
    Skill(){
        state = 1;
        level = 1;
    }
    bool checkUsed(){
        return state;
    }
    int cost(){
        return priceToUp;
    }
    void turnOn(){
        state = 0;
    }
    void reset(){
        state = 1;
    }
    int getNum(){
        return num;
    }
    int getLevel(){
        return level;
    }
    virtual int getNextNum() =0;
};

class SkillTank:public Skill{
private:
    int price[4] = {0, 300, 400, 700};
    int buffARM[4] = {0, 500, 700, 1000};
public:
    SkillTank(){
        priceToUp = price[level];
        num = buffARM[level];
    }
    bool upLevel(){
        if(level == 3){
            cout << "This is the max level"<<endl;
            return 0;
        }
        level++;
        priceToUp = price[level];
        num = buffARM[level];
        return 1;
    }
    int getNextNum(){
        if(level < 3){
            return buffARM[level+1];
        }
        return -1;
    }
};

class SkillWarrior:public Skill{
private:
    int price[4] = {0, 300, 500, 800};
    int buffATK[4] = {0, 500, 700, 1000};
public:
    SkillWarrior(){
        priceToUp = price[level];
        num = buffATK[level];
    }
    bool upLevel(){
        if(level>2){
            cout << "This is the max level"<<endl;
            return 0;
        }
        level++;
        priceToUp = price[level];
        num = buffATK[level];
        return 1;
    }
    int getNextNum(){
        if(level < 3){
            return buffATK[level+1];
        }
        return -1;
    }
};

class SkillWizard:public Skill{
private:
    int price[4] = {0, 400, 600, 1000};
    int attackAll[4] = {0, 200,300, 500};
public:
    SkillWizard(){
        priceToUp = price[level];
        num = attackAll[level];
    }
    bool upLevel(){
        if(level>2){
            cout << "This is the max level"<<endl;
            return 0;
        }
        level++;
        priceToUp = price[level];
        num = attackAll[level];
        return 1;
    }
    int getNextNum(){
        if(level < 3){
            return attackAll[level+1];
        }
        return -1;
    }
};

#endif
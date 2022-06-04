#ifndef STORE_H
#define STORE_H
#include "main.h"

class Item{
protected:
    int price;
    StoreType type;
public:
    virtual string getInfo() = 0;
    virtual int getNum() = 0;
    virtual void setNum(int n) = 0;
    StoreType getType(){
        return type;
    }
    void setPrice(int _price){
        price = _price;
    }
    int getPrice(){
        return price;
    }
};

class Helmet: public Item{
private:
    int DEF;
public:
    Helmet(){
        price = 0;
        DEF = 0;
        type = Helmets;
    }
    Helmet(int _num, int _price){
        price = _price;
        DEF = _num;
        type = Helmets;
    }
    string getInfo(){
        return "+"+to_string(DEF)+" DEF";
    }
    int getNum(){
        return DEF;
    }
    void setNum(int _Num){
        DEF = _Num;
    }
};

class Armor: public Item{
private:
    int DEF;
public:
    Armor(){
        price = 0;
        DEF = 0;
        type = Armors;
    }
    Armor(int _num, int _price){
        price = _price;
        DEF = _num;
        type = Armors;
    }
    string getInfo(){
        return "+"+to_string(DEF)+" DEF";
    }
    int getNum(){
        return DEF;
    }
    void setNum(int _Num){
        DEF = _Num;
    }
};

class Weapon: public Item{
private:
    int ATK;
public:
    Weapon(){
        price = 0;
        ATK = 0;
        type = Weapons;
    }
    Weapon(int _num, int _price){
        ATK = _num;
        price = _price;
        type = Weapons;
    }
    string getInfo(){
        return "+"+to_string(ATK)+" ATK";
    }
    int getNum(){
        return ATK;
    }
    void setNum(int _Num){
        ATK = _Num;
    }
};

class DrugArm: public Item{
private:
    int ARM;
public:
    DrugArm(){
        ARM  = 0;
        price = 0;
        type = DrugArms;
    }
    DrugArm(int _num, int _price){
        ARM = _num;
        price = _price;
        type = DrugArms;
    }
    string getInfo(){
        return "+"+to_string(ARM)+" ARM";
    }
    int getNum(){
        return ARM;
    }
    void setNum(int _Num){
        ARM = _Num;
    }
};

class DrugHp: public Item{
private:
    int HP;
public:
    DrugHp(){
        HP = 0;
        price = 0;
        type = DrugHps;
    }
    DrugHp(int _num, int _price){
        HP = _num;
        price = _price;
        type = DrugHps;
    }
    string getInfo(){
        return "+"+to_string(HP)+" HP";
    }
    int getNum(){
        return HP;
    }
    void setNum(int _Num){
        HP = _Num;
    }
};

class Store{
private:
    Item* items[5][3];
    int helmet[3][2] = {{100, 200},{200, 300},{300, 500}};
    int armor[3][2] = {{100, 150},{150, 250},{250, 400}};
    int weapon[3][2] = {{100, 200},{200, 400},{400, 600}};
    int drugHp[3][2] = {{100, 100},{150, 200},{200, 250}};
    int drupArm[3][2] = {{100, 50},{150, 100},{200, 200}};
public:
    Store(){
        // Helmet
        for(int i=0; i<3; i++){
            items[0][i] = new Helmet(helmet[i][0], helmet[i][1]);
        }
        // Armor
        for(int i=0; i<3; i++){
            items[1][i] = new Armor(armor[i][0], armor[i][1]);
        }
        // Weapon
        for(int i=0; i<3; i++){
            items[2][i] = new Weapon(weapon[i][0], weapon[i][1]);
        }
        // DrugArm
        for(int i=0; i<3; i++){
            items[3][i] = new DrugArm(drupArm[i][0], drupArm[i][1]);
        }
        // DrugHp
        for(int i=0; i<3; i++){
            items[4][i] = new DrugHp(drugHp[i][0], drugHp[i][1]);
        }
    }
    ~Store(){
        for(int i=0; i<5; i++){
            for(int j=0; j<3; j++){
                delete items[i][j];
            }
        }
    }
    void printItems(){
    cout << "                                               Welcome to our Store\n\n";
    cout << "                  Helmet               Armor             Weapon             DrugArm             DrugHp";
    cout << "\n\nBasic  ";
    for(int i=0; i<5; i++){
        cout << setw(10)<<items[i][0]->getPrice()<<"$ "<<items[i][0]->getInfo();
    }
    cout <<"\n\nMedium ";
    for(int i=0; i<5; i++){
        cout << setw(10)<<items[i][1]->getPrice()<<"$ "<<items[i][1]->getInfo();
    }
    cout <<"\n\nAdvance";
    for(int i=0; i<5; i++){
        cout << setw(10)<<items[i][2]->getPrice()<<"$ "<<items[i][2]->getInfo();
    }
    cout <<'\n';
    }
    Item* getItem(string str){
        // example Basic Armor
    string typeEquip = str.substr(0, str.find(' '));
    string nameEquip = str.substr(str.find(' ')+1);
    string typeEquips[3] = {"Basic", "Medium", "Advance"};
    string nameEquips[5] = {"Helmet", "Armor", "Weapon", "DrugArm", "DrugHp"};
    for(int i=0; i<5; i++){
        if(nameEquip == nameEquips[i]){
            for(int j=0; j<3; j++){
                if(typeEquip == typeEquips[j]){
                    return items[i][j];
                }
            }
        }
    }
    return NULL;
    }
};

#endif
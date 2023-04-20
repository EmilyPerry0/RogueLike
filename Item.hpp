#ifndef ITEM
#define ITEM

#include <string>

class Item{

public:
    Item(std::string name, char itemType, std::string info, int cost);
    std::string getName();
    char getItemType();
    std::string getInfo();
    int getCost();

private:
    std::string name;
    char itemType;
    std::string info;
    int cost;
};

Item::Item(std::string name, char itemType, std::string info, int cost){
    this->name = name;
    this->itemType = itemType;
    this->info = info;
    this->cost = cost;
}

std::string Item::getName(){
    return this->name;
}

char Item::getItemType(){
    return this->itemType;
}

std::string Item::getInfo(){
    return this->info;
}

int Item::getCost(){
    return this->cost;
}

#endif
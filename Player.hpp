#include <string>
#include <vector>

class Player{

public:
    Player();

    //all the accessor functions
    int getHP() const;
    int getMaxHP() const;
    int getXPos() const;
    int getYPos() const;
    std::string getItemAtPos(const int POS);

    //all the mutator functions
    void updateHP(const int TO_ADD);
    void updateMaxHP(const int TO_ADD);
    void fillHP();
    void updateXPos(const int NEW_POS);
    void updateYPos(const int NEW_POS);
    void addItem(const std::string ITEM_TO_ADD);

private:
    int hp;
    int maxHP;
    int xPos;
    int yPos;
    std::vector<std::string> itemList;
};

/**
 * @brief Construct a new Player object
 * 
 */
Player::Player(){
    this->hp = 5;
    this->maxHP = 5;
    this->xPos = 0;
    this->yPos = 0;
}

//all the accessor functions
int Player::getHP() const {
    return this->hp;
}

int Player::getMaxHP() const {
    return this->maxHP;
}

int Player::getXPos() const{
    return this->xPos;
}

int Player::getYPos() const{
    return this->yPos;
}

std::string Player::getItemAtPos(const int POS){
    return this->itemList.at(POS);
}

//all the mutator functions
void Player::updateHP(const int TO_ADD){
    this->hp += TO_ADD;
}

void Player::updateMaxHP(const int TO_ADD){
    this->maxHP += TO_ADD;
}

void Player::fillHP(){
    this->hp = this->maxHP;
}

void Player::updateXPos(const int NEW_POS){
    //if the bool is true, update xPos by one (like stepping to the right once),otherwise opp
    this->xPos = NEW_POS;
}

void Player::updateYPos(const int NEW_POS){
    //if the bool is true, update yPos down by one (like stepping down once),otherwise opp
    this->yPos = NEW_POS;
}

void Player::addItem(const std::string ITEM_TO_ADD){
    this->itemList.push_back(ITEM_TO_ADD);
}
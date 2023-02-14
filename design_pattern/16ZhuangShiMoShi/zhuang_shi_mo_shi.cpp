#include <iostream>
using namespace std;

// 抽象的英雄
class AbstractHero {
public:
  virtual void ShowStatus() = 0;

// 基本属性
public:
  int mHp; // 血量
  int mMp; // 魔法
  int mAt; // 攻击
  int mDf; // 防御
};

// 具体的英雄
class HeroA : public AbstractHero {
public:
  HeroA() {
    mHp = 0;
    mMp = 0;
    mAt = 0;
    mDf = 0;
  }
  virtual void ShowStatus() {
    cout << "血量：" << mHp << endl;
    cout << "魔法：" << mMp << endl;
    cout << "攻击：" << mAt << endl;
    cout << "防御：" << mDf << endl;
  }
};

// 抽象的装饰物，英雄穿上装饰物，还是一个英雄
class AbstractEquipment : public AbstractHero{
public:
  AbstractEquipment(AbstractHero *hero) {
    this->pHero = hero;
  }

  virtual void ShowStatus() {}
public:
  AbstractHero *pHero;
};

// 装饰物A
class EquipmentA : public AbstractEquipment {
public:
  EquipmentA(AbstractHero *hero) : AbstractEquipment(hero) {}

  // 增加额外功能
  void AddEquipmentA() {
    cout << "英雄穿上装饰物A之后" << endl;
    this->mHp = this->pHero->mHp;
    this->mMp = this->pHero->mMp;
    this->mAt = this->pHero->mAt;
    this->mDf = this->pHero->mDf + 30;

    delete this->pHero; // 析构
  }

  virtual void ShowStatus() {
    AddEquipmentA();
    cout << "血量：" << mHp << endl;
    cout << "魔法：" << mMp << endl;
    cout << "攻击：" << mAt << endl;
    cout << "防御：" << mDf << endl;
  }
};

class EquipmentB : public AbstractEquipment {
public:
  EquipmentB(AbstractHero *hero) : AbstractEquipment(hero) {}

  // 增加额外功能
  void AddEquipmentB() {
    cout << "英雄穿上装饰物A之后" << endl;
    this->mHp = this->pHero->mHp;
    this->mMp = this->pHero->mMp;
    this->mAt = this->pHero->mAt + 80;
    this->mDf = this->pHero->mDf;

    delete this->pHero; // 析构
  }

  virtual void ShowStatus() {
    AddEquipmentB();
    cout << "血量：" << mHp << endl;
    cout << "魔法：" << mMp << endl;
    cout << "攻击：" << mAt << endl;
    cout << "防御：" << mDf << endl;
  }
};

void test01() {
  AbstractHero *hero = new HeroA;
  cout << "-----初始转态------" << endl;
  hero->ShowStatus();

  hero = new EquipmentA(hero);
  cout << "---穿上装饰物A之后---" << endl;
  hero->ShowStatus();

  hero = new EquipmentB(hero);
  cout << "---穿上装饰物B之后---" << endl;
  hero->ShowStatus();
}

int main(int argc, char const *argv[]) {
  test01();
  return 0;
}

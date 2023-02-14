#include <iostream>
using namespace std;

// 抽象武器 武器策略
class WeaponStrate {
public:
  virtual void UseWeapon() = 0;
};

class Knife : public WeaponStrate {
public:
  virtual void UseWeapon() { 
    cout << "使用匕首" << endl; 
  }
};

class AK47 : public WeaponStrate {
public:
  virtual void UseWeapon() { 
    cout << "使用AK47" << endl; 
  }
};

class Person {
public:
  void setWeapon(WeaponStrate *weapon) { 
    this->pWeapon = weapon; 
  }
  void ThrowWeapon() { 
    this->pWeapon->UseWeapon(); 
  }

public:
  WeaponStrate *pWeapon;
};

void test01() {
  // 创建人物
  Person *person = new Person;

  // 武器策略
  WeaponStrate *knife = new Knife;
  WeaponStrate *ak47 = new AK47;

  // 使用武器
  person->setWeapon(knife);
  person->ThrowWeapon();

  person->setWeapon(ak47);
  person->ThrowWeapon();

  // 释放内存
  delete ak47;
  delete knife;
  delete person;
}

int main(int argc, char const *argv[]) {
  test01();
  return 0;
}

#include <iostream>
using namespace std;

class DrinkTemplate {
public:
  virtual void BoilWater() = 0;    // 煮开水
  virtual void Brew() = 0;         // 冲泡
  virtual void PourInCup() = 0;    // 倒入杯中
  virtual void AddSomething() = 0; // 加料

  // 模板方法
  void Make() {
    this->BoilWater();
    this->Brew();
    this->PourInCup();
    this->AddSomething();
  }
};

// 制作茶水
class Tea : public DrinkTemplate {
public:
  virtual void BoilWater() { 
    cout << "煮开水" << endl; 
  }
  virtual void Brew() { 
    cout << "冲泡茶叶" << endl; 
  }
  virtual void PourInCup() { 
    cout << "茶水倒入杯中" << endl; 
  }
  virtual void AddSomething() { 
    cout << "加入柠檬" << endl; 
  }
};

// 制作咖啡
class Coffee : public DrinkTemplate {
public:
  virtual void BoilWater() { 
    cout << "煮开水" << endl; 
  }
  virtual void Brew() { 
    cout << "冲泡咖啡" << endl; 
  }
  virtual void PourInCup() { 
    cout << "咖啡倒入杯中" << endl; 
  }
  virtual void AddSomething() { 
    cout << "加入牛奶" << endl;
  }
};

void test01() {
  cout << "---泡茶---" << endl;
  Tea *tea = new Tea;
  tea->Make();
}

void test02() {
  cout << "---泡咖啡---" << endl;
  Coffee *coffee = new Coffee;
  coffee->Make();
}

int main(int argc, char const *argv[]) {
  test01();
  test02();
  return 0;
}

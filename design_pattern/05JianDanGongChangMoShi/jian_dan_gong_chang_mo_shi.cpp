#include <iostream>
using namespace std;

// 抽象水果类
class AbstractFruit {
public:
  virtual void ShowName() = 0;
};

// 苹果类
class Apple : public AbstractFruit {
public:
  virtual void ShowName() { 
    cout << "我是苹果" << endl; 
  }
};

// 香蕉类
class Banana : public AbstractFruit {
public:
  virtual void ShowName() { 
    cout << "我是香蕉" << endl; 
  }
};

// 鸭梨类
class Pear : public AbstractFruit {
public:
  virtual void ShowName() { 
    cout << "我是鸭梨" << endl; 
  }
};

// 水果工厂类
class FruitFactory {
public:
  static AbstractFruit *CreatFruit(string flag) {
    if (flag == "apple") {
      return new Apple;
    } 
    else if (flag == "banana") {
      return new Banana;
    } 
    else if (flag == "pear") {
      return new Pear;
    } 
    else {
      return NULL;
    }
  }
};

void test01() {
  FruitFactory *factory = new FruitFactory();
  AbstractFruit *apple = factory->CreatFruit("apple");
  apple->ShowName();
  AbstractFruit *banana = factory->CreatFruit("banana");
  banana->ShowName();

  AbstractFruit *fruit = factory->CreatFruit("apple");
  fruit->ShowName();
  delete fruit;
  fruit = factory->CreatFruit("banana");
  fruit->ShowName();
  delete fruit;
  fruit = factory->CreatFruit("pear");
  fruit->ShowName();
  delete fruit;
}

int main(int argc, char const *argv[]) {
  test01();
  return 0;
}

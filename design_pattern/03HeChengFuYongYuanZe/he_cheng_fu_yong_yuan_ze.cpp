#include <iostream>
using namespace std;

// 抽象车类
class AbstractCar {
public:
  virtual void run() = 0;
};

// 大众车
class Dazhong : public AbstractCar {
public:
  virtual void run() { 
    cout << "大众车启动。。。" << endl; 
  }
};

// 拖拉机
class Tuolaji : public AbstractCar {
public:
  virtual void run() { 
    cout << "拖拉机启动。。。" << endl; 
  }
};

// 针对具体的类 不适用继承
#if 0
class PersonA : public Tuolaji{
  public:
    void Doufeng(){
      run();
    }
};

class PersonB : public Dazhong{
  public:
    void Doufeng(){
      run();
    }
};
#endif

// 使用组合
class Person {
public:
  void setCar(AbstractCar *car) { 
    this->car = car; 
  }
  void Doufeng() { 
    this->car->run(); 
  }
  ~Person() {
    if (this->car != NULL) {
      delete this->car;
    }
  }

public:
  AbstractCar *car;
};

void test01() {
  Person *p = new Person;
  p->setCar(new Dazhong);
  p->Doufeng();

  // delete p;

  p->setCar(new Tuolaji);
  p->Doufeng();
  delete p;
}

int main(int argc, char const *argv[]) {
  test01();
  return 0;
}

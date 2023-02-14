#include <iostream>
using namespace std;
// 开闭原则：对扩展开放，对修改关闭，增加功能是通过增加代码来实现，而不是去修改源代码

// 抽象计算器类
class AbstractCaculator {
public:
  virtual void setOperatorNumber(int a, int b) = 0;
  virtual int getResult() = 0;
};

// 加法计算器类
class PlusCaculator : public AbstractCaculator {
public:
  virtual void setOperatorNumber(int a, int b) {
    this->mA = a;
    this->mB = b;
  }
  virtual int getResult() { 
    return mA + mB; 
  }

public:
  int mA;
  int mB;
};

// 减法计算器类
class MinuteCaculator : public AbstractCaculator {
public:
  virtual void setOperatorNumber(int a, int b) {
    this->mA = a;
    this->mB = b;
  }
  virtual int getResult() { 
    return mA - mB; 
  }

public:
  int mA;
  int mB;
};

// 乘法计算器类
class MultiplyCaculator : public AbstractCaculator {
public:
  virtual void setOperatorNumber(int a, int b) {
    this->mA = a;
    this->mB = b;
  }
  virtual int getResult() { 
    return mA * mB; 
  }

public:
  int mA;
  int mB;
};

int main(int argc, char const *argv[]) {
  AbstractCaculator *caculator = new PlusCaculator();
  caculator->setOperatorNumber(10, 20);
  cout << caculator->getResult() << endl;

  delete caculator;

  caculator = new MinuteCaculator();
  caculator->setOperatorNumber(10, 20);
  cout << caculator->getResult() << endl;
  return 0;
}

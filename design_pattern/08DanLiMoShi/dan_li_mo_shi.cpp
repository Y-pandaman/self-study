#include <iostream>
using namespace std;

class A {
private:
  A() { 
    a = new A; 
  }

public:
  static A *getInstance() { 
    return a; 
  }

private:
  static A *a; // 静态成员函数可以通过类名直接调用
};

A *A::a = NULL; // 类外初始化

// 单例分为懒汉式和饿汉式
// 懒汉式
class Singleton_lazy {
private:
  Singleton_lazy() {}

public:
  static Singleton_lazy *getInstance() {
    if (pSingleton == NULL) {
      pSingleton = new Singleton_lazy;
    }
    return pSingleton;
  }
#if 0
    static void freeSpace(){
      if(pSingleton != NULL){
        delete pSingleton;
      }
    }
#endif

  // 不必要，可删
  class Garbo {
    ~Garbo() {
      if (pSingleton != NULL) {
        delete pSingleton;
      }
    }
  };

private:
  static Singleton_lazy *pSingleton;
  static Garbo garbo;
};
// 类外初始化
Singleton_lazy *Singleton_lazy::pSingleton = NULL;

// 饿汉式
class Singleton_hungry {
private:
  Singleton_hungry() { 
    cout << "饿汉式构造！" << endl; 
  }

public:
  static Singleton_hungry *getInstance() { 
    return pSingleton; 
  }

private:
  static Singleton_hungry *pSingleton;
};
// 类外初始化
Singleton_hungry *Singleton_hungry::pSingleton = new Singleton_hungry;

void test01() {
  Singleton_lazy *p1 = Singleton_lazy::getInstance();
  Singleton_lazy *p2 = Singleton_lazy::getInstance();
  if (p1 == p2) {
    cout << "两个指针指向同一块内存，是单例！" << endl;
  } 
  else {
    cout << "不是单例！" << endl;
  }

  Singleton_hungry *p3 = Singleton_hungry::getInstance();
  Singleton_hungry *p4 = Singleton_hungry::getInstance();
  if (p3 == p4) {
    cout << "两个指针指向同一块内存，是单例！" << endl;
  } 
  else {
    cout << "不是单例！" << endl;
  }
}

// void test02(){
//   Singleton_lazy::freeSpace();
// }

int main(int argc, char const *argv[]) {
  // A::getInstance();
  cout << "main函数开始执行！" << endl;
  test01();
  return 0;
}

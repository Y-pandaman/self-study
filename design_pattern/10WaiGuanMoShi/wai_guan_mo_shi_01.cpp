#include <iostream>
using namespace std;

class SubSystem1 {
public:
  void run() { 
    cout << "子系统一启动！" << endl; 
  }
};

class SubSystem2 {
public:
  void run() { 
    cout << "子系统二启动！" << endl; 
  }
};

class SubSystem3 {
public:
  void run() { 
    cout << "子系统三启动！" << endl; 
  }
};

class SubSystem4 {
public:
  void run() { 
    cout << "子系统四启动！" << endl; 
  }
};

class Facede {
public:
  Facede() {
    pSystem1 = new SubSystem1;
    pSystem2 = new SubSystem2;
    pSystem3 = new SubSystem3;
    pSystem4 = new SubSystem4;
  }

  void runSystem() {
    pSystem1->run();
    pSystem2->run();
    pSystem3->run();
    pSystem4->run();
  }

private:
  SubSystem1 *pSystem1;
  SubSystem2 *pSystem2;
  SubSystem3 *pSystem3;
  SubSystem4 *pSystem4;
};

void test01() {
  Facede *facede = new Facede;
  facede->runSystem();
}

int main(int argc, char const *argv[]) {
  test01();
  return 0;
}

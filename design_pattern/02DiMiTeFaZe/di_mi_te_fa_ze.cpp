#include <iostream>
#include <vector>
using namespace std;
// 迪米特法则 又叫最少知识原则

class AbstractBuilding {
public:
  virtual void sale() = 0;
  virtual std::string getQuality() = 0;
};

// 楼盘A
class BuildingA : public AbstractBuilding {
public:
  BuildingA() { 
    mQuilty = "高品质"; 
  }
  virtual void sale() {
    std::cout << "楼盘A" << mQuilty << "被售卖！" << std::endl;
  }
  virtual std::string getQuality() { 
    return mQuilty; 
  }

public:
  std::string mQuilty;
};

// 楼盘B
class BuildingB : public AbstractBuilding {
public:
  BuildingB() { 
    mQuilty = "低品质"; 
  }
  virtual void sale() {
    std::cout << "楼盘B" << mQuilty << "被售卖！" << std::endl;
  }
  virtual std::string getQuality() { 
    return mQuilty; 
  }

public:
  std::string mQuilty;
};

// 中介类
class Mediator {
public:
  Mediator() {
    AbstractBuilding *building = new BuildingA();
    vBuilding.push_back(building);
    building = new BuildingB();
    vBuilding.push_back(building);
  }

  // 对外提供接口
  AbstractBuilding *findMyBuilding(std::string quality) {
    for (vector<AbstractBuilding *>::iterator it = vBuilding.begin();
         it != vBuilding.end(); it++) {
      if ((*it)->getQuality() == quality) {
        return *it;
      }
    }
    return NULL;
  }

  ~Mediator() {
    for (vector<AbstractBuilding *>::iterator it = vBuilding.begin();
         it != vBuilding.end(); it++) {
      if (*it != NULL) {
        delete *it;
      }
    }
  }

public:
  vector<AbstractBuilding *> vBuilding;
};

void test01() {
  BuildingA *ba = new BuildingA();
  if (ba->mQuilty == "低品质") {
    ba->sale();
  }

  BuildingB *bb = new BuildingB();
  if (bb->mQuilty == "低品质") {
    bb->sale();
  }
}

void test02() {
  Mediator *mediator = new Mediator();
  AbstractBuilding *building = mediator->findMyBuilding("高品质");
  if (building != NULL) {
    building->sale();
  } 
  else {
    cout << "没有符合条件的楼盘！";
  }
}

int main(int argc, char const *argv[]) {
  test01();
  test02();
  return 0;
}

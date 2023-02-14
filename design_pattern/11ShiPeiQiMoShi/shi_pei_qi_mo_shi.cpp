#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 已存在的函数(两个参数)
struct MyPrint {
  void operator()(int v1, int v2) { 
    cout << v1 + v2 << endl; 
  }
};

// 目标接口（一个参数）
class Target {
public:
  virtual void operator()(int v) = 0;
};

// 适配器
class Adapter : public Target {
public:
  Adapter(int param) { 
    this->mParam = param; 
  }
  virtual void operator()(int v) { 
    print(v, mParam); 
  }

public:
  MyPrint print;
  int mParam;
};

Adapter MyBind2nd(int v) { 
  return Adapter(v); 
}

int main(int argc, char const *argv[]) {
  vector<int> v;
  for (int i = 0; i < 10; i++) {
    v.push_back(i);
  }
  // for_each(v.begin(), v.end(), MyPrint());  // 错误，目标函数参数不匹配
  // for_each(v.begin(), v.end(), Adapter(100));
  for_each(v.begin(), v.end(), MyBind2nd(10));

  return 0;
}

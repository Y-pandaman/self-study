#include <iostream>
using namespace std;

// 抽象接口类
class AbstractCommonINterface {
public:
  virtual void run() = 0;
};

// 系统类
class MySystem : public AbstractCommonINterface {
public:
  virtual void run() { 
    cout << "系统启动" << endl; 
  }
};

// 代理类
class MySystemProxy : public AbstractCommonINterface {
public:
  MySystemProxy(string username, string password) {
    this->mUserName = username;
    this->mPassword = password;
    pSystem = new MySystem;
  }

  bool checkUsernameAndPassword() {
    if (mUserName == "admin" && mPassword == "admin") {
      return true;
    }
    return false;
  }

  virtual void run() {
    if (checkUsernameAndPassword()) {
      cout << "用户名和密码正确，验证通过。。。" << endl;
      this->pSystem->run();
    } 
    else {
      cout << "用户名或密码错误，权限不足。。。" << endl;
    }
  }

  ~MySystemProxy() {
    if (pSystem != NULL) {
      delete pSystem;
    }
  }

public:
  MySystem *pSystem;
  string mUserName;
  string mPassword;
};

void test01() {
  MySystemProxy *proxy = new MySystemProxy("admin", "admin");
  proxy->run();
}

int main(int argc, char const *argv[]) {
  test01();
  return 0;
}

#include <iostream>
#include <queue>
#include <windows.h>
using namespace std;

// 协议处理类
class HandleClientProtocol {
public:
  // 处理增加金币
  void AddMoney() { 
    cout << "增加金币！" << endl; 
  }

  // 处理增加钻石
  void AddDiamond() { 
    cout << "增加钻石！" << endl; 
  }

  // 处理玩家装备
  void AddEquipment() { 
    cout << "穿装备！" << endl; 
  }

  // 处理玩家升级
  void AddLevel() { 
    cout << "玩家升级！" << endl; 
  }
};

// 命令接口
class AbstractCommand {
public:
  virtual void handle() = 0; // 处理客户端请求的接口
};

// 处理增加金币请求
class AddMoneyCommand : public AbstractCommand {
public:
  AddMoneyCommand(HandleClientProtocol *protocol) {
    this->pProtocol = protocol;
  }

  virtual void handle() { 
    this->pProtocol->AddMoney(); 
  }

public:
  HandleClientProtocol *pProtocol;
};

// 处理增加钻石请求
class AddDiamondCommand : public AbstractCommand {
public:
  AddDiamondCommand(HandleClientProtocol *protocol) {
    this->pProtocol = protocol;
  }
  virtual void handle() { 
    this->pProtocol->AddDiamond(); 
  }

public:
  HandleClientProtocol *pProtocol;
};

// 处理穿装备请求
class AddEquimentCommand : public AbstractCommand {
public:
  AddEquimentCommand(HandleClientProtocol *protocol) {
    this->pProtocol = protocol;
  }
  virtual void handle() { 
    this->pProtocol->AddEquipment(); 
  }

public:
  HandleClientProtocol *pProtocol;
};

// 处理玩家升级请求
class AddLevelCommand : public AbstractCommand {
public:
  AddLevelCommand(HandleClientProtocol *protocol) {
    this->pProtocol = protocol;
  }
  virtual void handle() { 
    this->pProtocol->AddLevel(); 
  }

public:
  HandleClientProtocol *pProtocol;
};

// 服务器程序
class Server {
public:
  void addRequest(AbstractCommand *command) { 
    mCommands.push(command); 
  }

  void startHandle() {
    while (!mCommands.empty()) {
      Sleep(2000);
      AbstractCommand *command = mCommands.front();
      command->handle();
      mCommands.pop();
    }
  }

public:
  queue<AbstractCommand *> mCommands;
};

void test01() {
  HandleClientProtocol *protocol = new HandleClientProtocol;
  // 客户端增加金币的请求
  AbstractCommand *addmoney = new AddMoneyCommand(protocol);
  // 客户端增加钻石的请求
  AbstractCommand *adddiamond = new AddDiamondCommand(protocol);
  // 客户端穿装备的请求
  AbstractCommand *addequiment = new AddEquimentCommand(protocol);
  // 客户端升级的请求
  AbstractCommand *addlevel = new AddLevelCommand(protocol);

  // 服务器启动
  Server *server = new Server;
  server->addRequest(addmoney);
  server->addRequest(adddiamond);
  server->addRequest(addequiment);
  server->addRequest(addlevel);

  // 服务器开始处理请求
  server->startHandle();
}

int main(int argc, char const *argv[]) {
  test01();
  return 0;
}

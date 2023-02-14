#include <iostream>
using namespace std;

// 银行工作人员类（做太多的事了）
class BankWorker {
public:
  void saveService() { 
    cout << "办理存款业务！" << endl; 
  }

  void payService() { 
    cout << "办理支付业务！" << endl; 
  }

  void transferService() { 
    cout << "办理转账业务！" << endl; 
  }
};

// 中层模块
void doSaveBusiness(BankWorker *worker) { 
  worker->saveService(); 
}

void dopayBusiness(BankWorker *worker) { 
  worker->payService(); 
}

void doTransferBusiness(BankWorker *worker) { 
  worker->transferService(); 
}

// 业务模块
void test01() {
  BankWorker *worker = new BankWorker;
  doSaveBusiness(worker);     // 办理存款业务
  dopayBusiness(worker);      // 办理支付业务
  doTransferBusiness(worker); // 办理转账业务
}

//----------------------------------

// 抽象银行工作人员类
class AbstractWorker {
public:
  virtual void doBusiness() = 0;
};

// 专门负责办理存款业务的工作人员
class SaveBankWorker : public AbstractWorker {
public:
  virtual void doBusiness() { 
    cout << "办理存款业务。。。" << endl; 
  }
};

// 专门负责办理支付业务的工作人员
class PayBankWorker : public AbstractWorker {
public:
  virtual void doBusiness() { 
    cout << "办理支付业务。。。" << endl; 
  }
};

// 专门负责办理转账业务的工作人员
class TransferBankWorker : public AbstractWorker {
public:
  virtual void doBusiness() { 
    cout << "办理转账业务。。。" << endl; 
  }
};

// 中层业务
void doNewBusiness(AbstractWorker *worker) {
  worker->doBusiness();
  delete worker;
}

void test02() {
  AbstractWorker *transfer = new TransferBankWorker;
  doNewBusiness(transfer);

  doNewBusiness(new TransferBankWorker);
  doNewBusiness(new PayBankWorker);
  doNewBusiness(new SaveBankWorker);
}

int main(int argc, char const *argv[]) {
  test01();
  test02();
  return 0;
}

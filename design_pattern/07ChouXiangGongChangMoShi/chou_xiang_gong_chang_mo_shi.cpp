#include <iostream>
using namespace std;

// 抽象苹果类
class AbstractApple {
public:
  virtual void ShowName() = 0;
};

// 中国苹果
class ChinaApple : public AbstractApple {
public:
  virtual void ShowName() { 
    cout << "中国苹果" << endl; 
  }
};

// 美国苹果
class USAApple : public AbstractApple {
public:
  virtual void ShowName() { 
    cout << "美国苹果" << endl; 
  }
};

// 日本苹果
class JapanApple : public AbstractApple {
public:
  virtual void ShowName() { 
    cout << "日本苹果" << endl; 
  }
};

// 抽象香蕉类
class AbstractBanana {
public:
  virtual void ShowName() = 0;
};

// 中国香蕉
class ChinaBanana : public AbstractBanana {
public:
  virtual void ShowName() { 
    cout << "中国香蕉" << endl; 
  }
};

// 美国香蕉
class USABanana : public AbstractBanana {
public:
  virtual void ShowName() { 
    cout << "美国香蕉" << endl; 
  }
};

// 日本香蕉
class JapanBanana : public AbstractBanana {
public:
  virtual void ShowName() { 
    cout << "日本香蕉" << endl; 
  }
};

// 抽象鸭梨类
class AbstractPear {
public:
  virtual void ShowName() = 0;
};

// 中国鸭梨
class ChinaPear : public AbstractPear {
public:
  virtual void ShowName() { 
    cout << "中国鸭梨" << endl; 
  }
};

// 美国鸭梨
class USAPear : public AbstractPear {
public:
  virtual void ShowName() { 
    cout << "美国鸭梨" << endl; 
  }
};

// 日本鸭梨
class JapanPear : public AbstractPear {
public:
  virtual void ShowName() { 
    cout << "日本鸭梨" << endl; 
  }
};

// 抽象工厂
class AbstractFactory {
public:
  virtual AbstractApple *CreatApple() = 0;
  virtual AbstractBanana *CreateBanana() = 0;
  virtual AbstractPear *CreatePear() = 0;
};

// 中国工厂
class ChinaFactory : public AbstractFactory {
public:
  virtual AbstractApple *CreatApple() { 
    return new ChinaApple; 
  }
  virtual AbstractBanana *CreateBanana() { 
    return new ChinaBanana; 
  }
  virtual AbstractPear *CreatePear() { 
    return new ChinaPear; 
  }
};

// 美国工厂
class USAFactory : public AbstractFactory {
public:
  virtual AbstractApple *CreatApple() { 
    return new USAApple; 
  }
  virtual AbstractBanana *CreateBanana() { 
    return new USABanana; 
  }
  virtual AbstractPear *CreatePear() { 
    return new USAPear; 
  }
};

// 日本工厂
class JapanFactory : public AbstractFactory {
public:
  virtual AbstractApple *CreatApple() { 
    return new JapanApple; 
  }
  virtual AbstractBanana *CreateBanana() { 
    return new JapanBanana; 
  }
  virtual AbstractPear *CreatePear() { 
    return new JapanPear; 
  }
};

void test01() {
  AbstractFactory *factory = NULL;
  AbstractApple *apple = NULL;
  AbstractBanana *banana = NULL;
  AbstractPear *pear = NULL;

  factory = new ChinaFactory;
  apple = factory->CreatApple();
  apple->ShowName();
  banana = factory->CreateBanana();
  banana->ShowName();
  pear = factory->CreatePear();
  pear->ShowName();

  // 释放内存
  delete pear;
  delete banana;
  delete apple;
  delete factory;
}

int main(int argc, char const *argv[]) {
  test01();
  return 0;
}

#include <iostream>
using namespace std;

class TV {
public:
  void On() { 
    cout << "电视机打开" << endl; 
  }
  void Off() { 
    cout << "电视机关闭" << endl; 
  }
};

class LED {
public:
  void On() { 
    cout << "灯打开" << endl; 
  }
  void Off() { 
    cout << "灯关闭" << endl; 
  }
};

class Audio {
public:
  void On() { 
    cout << "音响打开" << endl; 
  }
  void Off() { 
    cout << "音响关闭" << endl; 
  }
};

class Microphone {
public:
  void On() { 
    cout << "麦克风打开" << endl; 
  }
  void Off() { 
    cout << "麦克风关闭" << endl; 
  }
};

class DVD {
public:
  void On() { 
    cout << "DVD打开" << endl; 
  }
  void Off() { 
    cout << "DVD关闭" << endl; 
  }
};

class Gamemachine {
public:
  void On() { 
    cout << "游戏机打开" << endl; 
  }
  void Off() { 
    cout << "游戏机关闭" << endl; 
  }
};

// KTV模式
class KTVMode {
public:
  KTVMode() {
    pTV = new TV;
    pLED = new LED;
    pMicrophone = new Microphone;
    pAudio = new Audio;
    pDVD = new DVD;
  }

  void runKTV() {
    pTV->On();
    pLED->Off();
    pMicrophone->On();
    pAudio->On();
    pDVD->On();
  }

  ~KTVMode() {
    delete pTV;
    delete pLED;
    delete pMicrophone;
    delete pAudio;
    delete pDVD;
  }
public:
  TV *pTV;
  LED *pLED;
  Microphone *pMicrophone;
  Audio *pAudio;
  DVD *pDVD;
};

// 游戏模式
class GameMode {
public:
  GameMode() {
    pTV = new TV;
    pAudio = new Audio;
    pGameMachine = new Gamemachine;
  }

  void runGame() {
    pTV->On();
    pAudio->On();
    pGameMachine->On();
  }

  ~GameMode() {
    delete pTV;
    delete pAudio;
  }

public:
  TV *pTV;
  Audio *pAudio;
  Gamemachine *pGameMachine;
};

void test01() {
  cout << "---KTV模式---" << endl;
  KTVMode *ktvmode = new KTVMode;
  ktvmode->runKTV();
}

void test02() {
  cout << "---游戏模式---" << endl;
  GameMode *gamemode = new GameMode;
  gamemode->runGame();
}

int main(int argc, char const *argv[]) {
  test01();
  test02();
  return 0;
}

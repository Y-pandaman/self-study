# WebRTC源码（Ubuntu）下载编译

## 1. 环境配置（16.6G）

### 指定 同步目录

```bash
export WORKSPACE=`pwd`
```

### 安装depot_tools

```bash
cd $WORKSPACE
rm -rf depot_tools && git clone https://webrtc.bj2.agoralab.co/webrtc-mirror/depot_tools.git
chmod +x $WORKSPACE/depot_tools/cipd
export PATH=$PATH:$WORKSPACE/depot_tools
```

### 同步WebRTC

```bash
mkdir -p $WORKSPACE/webrtc && cd $WORKSPACE/webrtc
vi .gclient
//添加以下内容
solutions = [
  { "name"        : "src",
    "url"         : "https://webrtc.bj2.agoralab.co/webrtc-mirror/src.git@65e8d9facab05de13634d777702b2c93288f8849",
    "deps_file"   : "DEPS",
    "managed"     : False,
    "safesync_url": "",
    "custom_deps": {
    },
  },
]
target_os = ["linux"]  /*根据需要Android, ios，改完删除此行注释*/
```

```
// 在终端中输入（开系统代理无效）：
export http_proxy=x.x.x.x:port
export https_proxy=x.x.x.x:port

//开始同步，时间较久
date; gclient sync; date
//出现提示是否使用谷歌的depot_tools，推荐“n”，或者等1分钟提示框超时。
```

## 2. 编译

### Linux

```bash
apt-get update
apt-get install -y g++

export PATH=$PATH:$WORKSPACE/depot_tools

cd $WORKSPACE/webrtc/src

./build/install-build-deps.sh
gn gen out/Release "--args=is_debug=false"
ninja -C out/Release
```

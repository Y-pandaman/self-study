# 使用WebRTC捕获摄像头

## 使用说明

1. 按[文档](WebRTC源码下载编译.md)下载WebRTC源码

2. 将**video_capture**文件夹移动到*/workspace/webrtc/src/examples*目录下

3. 将下载的**BUILD.gn**替换掉**/workspace/webrtc/src/examples/BUILD.gn**文件

4. 再执行编译命令

   ```
   gn gen out/Release "--args=is_debug=false"
   ninja -C out/Release
   ```

5. 会在**/workspace/webrtc/src/out/Release/**目录下生成**video_capture_demo**可执行文件

6. 运行命令

   ```
   ./video_capture_demo
   ```

   会显示本地摄像头画面，30秒后自动关闭。




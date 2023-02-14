#include "modules/video_capture/video_capture_factory.h"
#include "rtc_base/logging.h"
#include "examples/video_capture/vcm_capturer_test.h"
#include "test/video_renderer.h"

#include <iostream>
#include <thread>

int main() {
  // 初始化
  const size_t kWidth = 1920;
  const size_t kHeight = 1080;
  const size_t kFps = 30;

  std::unique_ptr<webrtc_demo::VcmCapturerTest> capturer;  // 设备
  std::unique_ptr<webrtc::VideoCaptureModule::DeviceInfo> info(  // 设备信息
      webrtc::VideoCaptureFactory::CreateDeviceInfo());
  std::unique_ptr<webrtc::test::VideoRenderer> renderer;  // 视频渲染

  if (!info) {
    RTC_LOG(LERROR) << "CreateDeviceInfo failed";
    return -1;
  }
  int num_devices = info->NumberOfDevices();  // 遍历 /dev/video*,得到设备数量
  for (int i = 0; i < num_devices; ++i) {
    capturer.reset(
        webrtc_demo::VcmCapturerTest::Create(kWidth, kHeight, kFps, i));
    if (capturer) {
      break;
    }
  }

  if (!capturer) {
    RTC_LOG(LERROR) << "Cannot found available video device";
    return -1;
  }

  renderer.reset(webrtc::test::VideoRenderer::Create("Camera", kWidth, kHeight)); // 显示窗体的标题，宽，高
  capturer->AddOrUpdateSink(renderer.get(), rtc::VideoSinkWants());

  std::this_thread::sleep_for(std::chrono::seconds(30));
  capturer->RemoveSink(renderer.get());

  RTC_LOG(WARNING) << "Demo exit";
  return 0;
}
#include <ctime>
#include <iostream>
#include <opencv2/aruco.hpp>
#include <opencv2/highgui.hpp>
#include <vector>

const char *about = "Detect ArUco marker images";
const char *keys =
    "{d        |16    | dictionary: DICT_4X4_50=0, DICT_4X4_100=1, "
    "DICT_4X4_250=2, DICT_4X4_1000=3, DICT_5X5_50=4, DICT_5X5_100=5, "
    "DICT_5X5_250=6, DICT_5X5_1000=7, DICT_6X6_50=8, DICT_6X6_100=9, "
    "DICT_6X6_250=10, DICT_6X6_1000=11, DICT_7X7_50=12, DICT_7X7_100=13, "
    "DICT_7X7_250=14, DICT_7X7_1000=15, DICT_ARUCO_ORIGINAL = 16}"
    "{h        |false | Print help }"
    "{v        |<none>| Custom video source, otherwise '0' }";

int main(int argc, char const *argv[]) {
  cv::CommandLineParser parser(argc, argv, keys);
  parser.about(about);

  if (parser.get<bool>("h")) {
    parser.printMessage();
    return 0;
  }

  int dictionaryId = parser.get<int>("d");
  cv::String camId = "0";
  int waitTime = 10; // 1000/10帧

  cv::VideoCapture inputVideo;
  if (parser.has("v")) {
    camId = parser.get<cv::String>("v");
    if (camId.empty()) {
      parser.printMessage();
      return 1;
    }

    char *end = nullptr;
    // 强制转换10进制
    int source = static_cast<int>(std::strtol(camId.c_str(), &end, 10));
    if (!end || end == camId.c_str()) {
      inputVideo.open(camId); // url
    } else {
      inputVideo.open(source); // 设备号
    }
  } else {
    inputVideo.open(0);
  }

  if (!parser.check()) {
    parser.printErrors();
    return 1;
  }

  // 判断相机是否打开
  if (!inputVideo.isOpened()) {
    std::cout << "failed to open video input: " << camId << std::endl;
    return 1;
  }

  // 获取tag族
  cv::Ptr<cv::aruco::Dictionary> dictionary =
      cv::aruco::getPredefinedDictionary(dictionaryId);

  while (inputVideo.grab()) {
    cv::Mat image, imageCopy;
    inputVideo.retrieve(image);
    image.copyTo(imageCopy);

    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f>> corners;
    cv::aruco::detectMarkers(image, dictionary, corners, ids); // 检测marker

    // 如果有marker
    if (ids.size() > 0) {
      cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);
    }

    cv::imshow("detect marker", imageCopy);
    char key = (char)cv::waitKey(waitTime);
    if (key == 27) {
      break;
    }
  }
  return 0;
}
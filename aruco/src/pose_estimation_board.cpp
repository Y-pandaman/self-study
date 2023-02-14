#include <iomanip>
#include <iostream>
#include <opencv2/aruco.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

const char *about = "Pose estimation of ArUco board images";
const char *keys =
    "{d        |16    | dictionary: DICT_4X4_50=0, DICT_4X4_100=1, \n"
    "DICT_4X4_250=2, DICT_4X4_1000=3, DICT_5X5_50=4, DICT_5X5_100=5, \n"
    "DICT_5X5_250=6, DICT_5X5_1000=7, DICT_6X6_50=8, DICT_6X6_100=9, \n"
    "DICT_6X6_250=10, DICT_6X6_1000=11, DICT_7X7_50=12, DICT_7X7_100=13, \n"
    "DICT_7X7_250=14, DICT_7X7_1000=15, DICT_ARUCO_ORIGINAL = 16}"
    "{width        |       | Number of markers in X direction }"
    "{height        |       | Number of markers in Y direction }"
    "{s        |       | Separation between two consecutive "
    "markers in the grid (in pixels)}"
    "{h        |false | Print help }"
    "{size        |      | Actual marker length in meter }"
    "{v        |<none>| Custom video source, otherwise '0' }";

int main(int argc, char const *argv[]) {
  cv::CommandLineParser parser(argc, argv, keys);
  parser.about(about);

  if (argc < 5 || parser.get<bool>("h")) {
    parser.printMessage();
    return 0;
  }

  // 获取参数
  int dictionaryId = parser.get<int>("d");         // tag族
  int w = parser.get<int>("width");                // x方向tag数量
  int h = parser.get<int>("height");               // y方向tag数量
  float markerSize = parser.get<float>("size");    // tag尺寸
  float markerSeparation = parser.get<float>("s"); // tag之间的间隙

  if (markerSize <= 0) {
    std::cout << "marker length must be a positive value in meter" << std::endl;
    return 0;
  }

  cv::String camId = "0";
  cv::VideoCapture inputVideo;

  // 获取相机设备号
  if (parser.has("v")) {
    camId = parser.get<cv::String>("v");
    if (camId.empty()) {
      parser.printMessage();
      return 0;
    }

    char *end = nullptr;
    int source = static_cast<int>(std::strtol(camId.c_str(), &end, 10));
    if (!end || end == camId.c_str()) {
      inputVideo.open(camId); // url
    } else {
      inputVideo.open(source); // 设备号
    }
  } else {
    inputVideo.open(0);
  }

  if (!inputVideo.isOpened()) {
    std::cout << "camera " << camId << " can not open" << std::endl;
    return 0;
  }

  if (!parser.check()) {
    parser.printErrors();
    return 0;
  }

  // 获得tag族
  cv::Ptr<cv::aruco::Dictionary> dictionary =
      cv::aruco::getPredefinedDictionary(dictionaryId);

  // tag 板的数据
  cv::Ptr<cv::aruco::GridBoard> board = cv::aruco::GridBoard::create(
      w, h, markerSize, markerSeparation, dictionary);

  // 读取相机参数
  cv::Mat cameraMatrix, distCoeffs;
  cv::FileStorage fs("../config/out.yaml", cv::FileStorage::READ);
  fs["camera_matrix"] >> cameraMatrix;
  fs["distortion_coefficients"] >> distCoeffs;

  std::cout << "camera_matrix:" << cameraMatrix << std::endl;
  std::cout << "distortion_coefficients:" << distCoeffs << std::endl;

  while (inputVideo.grab()) {
    cv::Mat image, imageCopy;
    inputVideo.retrieve(image);
    image.copyTo(imageCopy);

    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f>> corners;
    // 检测tag
    cv::aruco::detectMarkers(image, dictionary, corners, ids);

    std::ostringstream rvec, tvec, text; // 输出内容
    cv::Point pt;                        // 角点位置

    if (ids.size() > 0) {
      cv::Vec3d rvecs, tvecs;

      // 画出每个tag的边框
      cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);

      //   估计board的位姿
      int flag = cv::aruco::estimatePoseBoard(corners, ids, board, cameraMatrix,
                                              distCoeffs, rvecs, tvecs);
      if (flag > 0) {
        cv::aruco::drawAxis(imageCopy, cameraMatrix, distCoeffs, rvecs, tvecs,
                            0.1);

        text.str(std::string()); //清空text值
        text << "          "
             << "R"
             << "         "
             << "T";
        cv::putText(imageCopy, text.str(), cv::Point(20, 20),
                    cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255),
                    2);

        text.str(std::string());
        text << std::setprecision(4) << "x:   " << std::setw(4) << rvecs[0]
             << "  " << tvecs[0];
        cv::putText(imageCopy, text.str(), cv::Point(20, 40),
                    cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 0, 255));

        text.str(std::string());
        text << std::setprecision(4) << "y:   " << std::setw(4) << rvecs[1]
             << "  " << tvecs[1];
        cv::putText(imageCopy, text.str(), cv::Point(20, 60),
                    cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 255, 0));

        text.str(std::string());
        text << std::setprecision(4) << "z:   " << std::setw(4) << rvecs[2]
             << "  " << tvecs[2];
        cv::putText(imageCopy, text.str(), cv::Point(20, 80),
                    cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 0, 0));
      }
    }

    cv::imshow("pose estimation", imageCopy);
    char key = (char)cv::waitKey(10);
    if (key == 27) {
      break;
    }
  }

  return 0;
}

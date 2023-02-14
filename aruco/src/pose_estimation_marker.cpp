#include <iomanip>
#include <iostream>
#include <opencv2/aruco.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

const char *about = "Pose estimation of ArUco marker images";
const char *keys =
    "{d        |16    | dictionary: DICT_4X4_50=0, DICT_4X4_100=1, "
    "DICT_4X4_250=2, DICT_4X4_1000=3, DICT_5X5_50=4, DICT_5X5_100=5, "
    "DICT_5X5_250=6, DICT_5X5_1000=7, DICT_6X6_50=8, DICT_6X6_100=9, "
    "DICT_6X6_250=10, DICT_6X6_1000=11, DICT_7X7_50=12, DICT_7X7_100=13, "
    "DICT_7X7_250=14, DICT_7X7_1000=15, DICT_ARUCO_ORIGINAL = 16}"
    "{h        |false | Print help }"
    "{l        |      | Actual marker length in meter }"
    "{v        |<none>| Custom video source, otherwise '0' }";

int main(int argc, char const *argv[]) {
  cv::CommandLineParser parser(argc, argv, keys);
  parser.about(about);

  if (argc < 2 || parser.get<bool>("h")) {
    parser.printMessage();
    return 0;
  }

  // 获取参数
  int dictionaryId = parser.get<int>("d");
  float len = parser.get<float>("l");

  if (len <= 0) {
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
      inputVideo.open(camId);
    } else {
      inputVideo.open(source);
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

  cv::Mat cameraMatrix, distCoeffs;
  cv::Mat image, imageCopy;

  // 读取相机参数
  cv::FileStorage fs("../config/out.yaml", cv::FileStorage::READ);
  fs["camera_matrix"] >> cameraMatrix;
  fs["distortion_coefficients"] >> distCoeffs;

  std::cout << "camera_matrix:" << cameraMatrix << std::endl;
  std::cout << "distortion_coefficients:" << distCoeffs << std::endl;

  while (inputVideo.grab()) {
    inputVideo.retrieve(image);
    image.copyTo(imageCopy);

    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f>> corners;
    // 检测tag
    cv::aruco::detectMarkers(imageCopy, dictionary, corners, ids);

    std::ostringstream rvec, tvec, text; // 输出内容
    cv::Point pt;                        // 角点位置

    if (ids.size() > 0) {
      std::vector<cv::Vec3d> rvecs, tvecs;

      //   估计单个tag的位姿
      cv::aruco::estimatePoseSingleMarkers(corners, len, cameraMatrix,
                                           distCoeffs, rvecs, tvecs);

      for (int i = 0; i < ids.size(); i++) {
        //   显示坐标轴
        cv::aruco::drawAxis(imageCopy, cameraMatrix, distCoeffs, rvecs[i],
                            tvecs[i], 0.1);

        //显示矩阵
        // std::cout << tvecs[i] <<std::endl;
        // rvec << "rvec:" << rvecs[i];
        // cv::putText(imageCopy, rvec.str(), cv::Point(10, 30),
        //             cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 0, 0), 1,
        //             CV_AA);

        // tvec << "tvec:" << tvecs[i];
        // cv::putText(imageCopy, tvec.str(), cv::Point(10, 50),
        //             cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 0, 255), 1,
        //             CV_AA);

        // 获取角点坐标
        pt = corners.at(i).at(0); // 左上角
        // pt = corners.at(i).at(1);  // 右上角
        // pt = corners.at(i).at(2);  // 右下角
        // pt = corners.at(i).at(3);  // 左下角
        text.str(std::string());
        text << "          "
             << "R"
             << "         "
             << "T";
        cv::putText(imageCopy, text.str(), pt, cv::FONT_HERSHEY_SIMPLEX, 0.5,
                    cv::Scalar(255, 255, 255));

        text.str(std::string()); //清空text值
        text << std::setprecision(4) << "x:   " << std::setw(4) << rvecs[i][0]
             << "  " << tvecs[i][0];
        cv::putText(imageCopy, text.str(), pt + cv::Point(0, 20),
                    cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 0, 255));

        text.str(std::string());
        text << std::setprecision(4) << "y:   " << std::setw(4) << rvecs[i][1]
             << "  " << tvecs[i][1];
        cv::putText(imageCopy, text.str(), pt + cv::Point(0, 40),
                    cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 255, 0));

        text.str(std::string());
        text << std::setprecision(4) << "z:   " << std::setw(4) << rvecs[i][2]
             << "  " << tvecs[i][2];
        cv::putText(imageCopy, text.str(), pt + cv::Point(0, 60),
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

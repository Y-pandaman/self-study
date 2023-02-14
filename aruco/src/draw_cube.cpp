#include <iomanip>
#include <iostream>
#include <opencv2/aruco.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

const char *about = "Draw cube on ArUco marker images";
const char *keys =
    "{d        |16    | dictionary: DICT_4X4_50=0, DICT_4X4_100=1, "
    "DICT_4X4_250=2, DICT_4X4_1000=3, DICT_5X5_50=4, DICT_5X5_100=5, "
    "DICT_5X5_250=6, DICT_5X5_1000=7, DICT_6X6_50=8, DICT_6X6_100=9, "
    "DICT_6X6_250=10, DICT_6X6_1000=11, DICT_7X7_50=12, DICT_7X7_100=13, "
    "DICT_7X7_250=14, DICT_7X7_1000=15, DICT_ARUCO_ORIGINAL = 16}"
    "{h        |false | Print help }"
    "{l        |      | Actual marker length in meter }"
    "{v        |<none>| Custom video source, otherwise '0' }";

// 构建立方体
void drawCube(cv::Mat image, cv::Mat cameraMatrix, cv::Mat dist, float l,
              cv::Vec3d rvec, cv::Vec3d tvec) {
  CV_Assert(image.total() != 0 &&
            (image.channels() == 1 || image.channels() == 3));
  CV_Assert(l > 0);
  float r = l / 2.0;

  // 构建8个三维顶点
  std::vector<cv::Point3f> axisPoints;
  axisPoints.push_back(cv::Point3f(-r, -r, 0));
  axisPoints.push_back(cv::Point3f(-r, r, 0));
  axisPoints.push_back(cv::Point3f(r, -r, 0));
  axisPoints.push_back(cv::Point3f(r, r, 0));
  axisPoints.push_back(cv::Point3f(-r, -r, l));
  axisPoints.push_back(cv::Point3f(-r, r, l));
  axisPoints.push_back(cv::Point3f(r, -r, l));
  axisPoints.push_back(cv::Point3f(r, r, l));

  // 构建二维顶点
  std::vector<cv::Point2f> points;
  // 从三维空间映射到二维空间
  projectPoints(axisPoints, rvec, tvec, cameraMatrix, dist, points);

  // 画立方体的12条线
  cv::line(image, points[1], points[0], cv::Scalar(0, 255, 0), 2);
  cv::line(image, points[2], points[0], cv::Scalar(0, 255, 0), 2);
  cv::line(image, points[1], points[3], cv::Scalar(0, 255, 0), 2);
  cv::line(image, points[2], points[3], cv::Scalar(0, 255, 0), 2);

  cv::line(image, points[0], points[4], cv::Scalar(0, 255, 0), 2);
  cv::line(image, points[1], points[5], cv::Scalar(0, 255, 0), 2);
  cv::line(image, points[2], points[6], cv::Scalar(0, 255, 0), 2);
  cv::line(image, points[3], points[7], cv::Scalar(0, 255, 0), 2);

  cv::line(image, points[5], points[4], cv::Scalar(0, 255, 0), 2);
  cv::line(image, points[6], points[4], cv::Scalar(0, 255, 0), 2);
  cv::line(image, points[5], points[7], cv::Scalar(0, 255, 0), 2);
  cv::line(image, points[6], points[7], cv::Scalar(0, 255, 0), 2);
}

int main(int argc, char const *argv[]) {
  cv::CommandLineParser parser(argc, argv, keys);
  parser.about(about);

  if (!parser.has("l") || parser.get<bool>("h")) {
    parser.printMessage();
    return 0;
  }

  int dictionaryId = parser.get<int>("d");
  float len = parser.get<float>("l");

  // 相机设备号
  cv::String camId = "0";
  cv::VideoCapture inputVideo;
  if (parser.has("v")) {
    camId = parser.get<cv::String>("v");
    if (camId.empty()) {
      parser.printMessage();
      return 1;
    }
    char *end = nullptr;
    int source = static_cast<int>(strtol(camId.c_str(), &end, 10));
    if (!end || end == camId.c_str()) {
      inputVideo.open(camId); // url
    } else {
      inputVideo.open(source); // 相机设备号
    }
  } else {
    inputVideo.open(0);
  }

  if (!parser.check()) {
    parser.printErrors();
    return 0;
  }

  if (!inputVideo.isOpened()) {
    std::cout << "camera can not open." << std::endl;
  }

  // 相机参数
  cv::Mat cameraMatrix, dist;
  cv::FileStorage fs("../config/out.yaml", cv::FileStorage::READ);
  fs["camera_matrix"] >> cameraMatrix;
  fs["distortion_coefficients"] >> dist;
  std::cout << "camera_matrix:" << std::endl << cameraMatrix << std::endl;
  std::cout << "distortion_coefficients:" << std::endl << dist << std::endl;

  std::vector<int> ids;
  std::vector<std::vector<cv::Point2f>> corners;
  std::vector<cv::Vec3d> rvecs, tvecs;
  cv::Mat image, imageCopy;
  std::ostringstream text;
  cv::Point pt;

  // 获取tag族
  cv::Ptr<cv::aruco::Dictionary> dictionary =
      cv::aruco::getPredefinedDictionary(dictionaryId);

  // 定义视频参数
  int width = inputVideo.get(CV_CAP_PROP_FRAME_WIDTH);
  int height = inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT);
  int fps = 30;
  cv::VideoWriter video("out.mp4", CV_FOURCC('M', 'J', 'P', 'G'), fps,
                        cv::Size(width, height), true);

  while (inputVideo.grab()) {

    inputVideo.retrieve(image);
    image.copyTo(imageCopy);

    cv::aruco::detectMarkers(image, dictionary, corners, ids);
    if (ids.size() > 0) {
      cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);
      cv::aruco::estimatePoseSingleMarkers(corners, len, cameraMatrix, dist,
                                           rvecs, tvecs);

      for (int i = 0; i < ids.size(); i++) {
        drawCube(imageCopy, cameraMatrix, dist, len, rvecs[i], tvecs[i]);

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

    video.write(imageCopy); // 写入视频流
    cv::imshow("draw cube", imageCopy);
    char key = (char)cv::waitKey(10);
    if (key == 27) {
      break;
    }
  }

  return 0;
}

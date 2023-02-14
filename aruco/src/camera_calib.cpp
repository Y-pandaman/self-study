#include <ctime>
#include <iostream>
#include <opencv2/aruco.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

const char *about =
    "Calibration using a ArUco Planar Grid board\n"
    "  To capture a frame for calibration, press 'c',\n"
    "  If input comes from video, press any key for next frame\n"
    "  To finish capturing, press 'ESC' key and calibration starts.\n";
const char *keys =
    "{w        |       | 横向tag的个数 }"
    "{h        |       | 纵向tag的个数 }"
    "{l        |       | 单个tag的长度（米） }"
    "{s        |       | 两个tag之间的间隙距离（米）}"
    "{d        |       | dictionary: DICT_4X4_50=0, DICT_4X4_100=1, "
    "DICT_4X4_250=2,"
    "DICT_4X4_1000=3, DICT_5X5_50=4, DICT_5X5_100=5, DICT_5X5_250=6, "
    "DICT_5X5_1000=7, "
    "DICT_6X6_50=8, DICT_6X6_100=9, DICT_6X6_250=10, DICT_6X6_1000=11, "
    "DICT_7X7_50=12,"
    "DICT_7X7_100=13, DICT_7X7_250=14, DICT_7X7_1000=15, DICT_ARUCO_ORIGINAL = "
    "16}"
    "{@outfile |<none> | Output file with calibrated camera parameters }"
    "{v        |       | Input from video file, if ommited, input comes from "
    "camera }"
    "{ci       | 0     | Camera id if input doesnt come from video (-v) }"
    "{dp       |       | 自定义参数文件 }"
    "{rs       | false | Apply refind strategy }";

static bool readParameters(std::string filename,
                           cv::Ptr<cv::aruco::DetectorParameters> &params) {
  cv::FileStorage fs(filename, cv::FileStorage::READ);
  if (!fs.isOpened()) {
    return false;
  }
  fs["adaptiveThreshWinSizeMin"] >> params->adaptiveThreshWinSizeMin;
  fs["adaptiveThreshWinSizeMax"] >> params->adaptiveThreshWinSizeMax;
  fs["adaptiveThreshWinSizeStep"] >> params->adaptiveThreshWinSizeStep;
  fs["adaptiveThreashConstant"] >> params->adaptiveThreshConstant;
  fs["minMarkerPerimeterRate"] >> params->minMarkerPerimeterRate;
  fs["maxMarkerPerimeterRate"] >> params->maxMarkerPerimeterRate;
  fs["polygonalApproxAccuracyRate"] >> params->polygonalApproxAccuracyRate;
  fs["minCornerDistanceRate"] >> params->minCornerDistanceRate;
  fs["minDistanceToBoard"] >> params->minDistanceToBorder;
  fs["minMarkerDistanceRate"] >> params->minMarkerDistanceRate;
  fs["cornerRefinementMethod"] >> params->cornerRefinementMethod;
  fs["cornerRefinementWinSize"] >> params->cornerRefinementWinSize;
  fs["cornerRefinementMaxIterations"] >> params->cornerRefinementMaxIterations;
  fs["cornerRefinementMinAccuracy"] >> params->cornerRefinementMinAccuracy;
  fs["markerBorderBits"] >> params->markerBorderBits;
  fs["perspectiveRemovePixelPerCell"] >> params->perspectiveRemovePixelPerCell;
  fs["perspectiveRemoveIgnoredMarginPerCell"] >>
      params->perspectiveRemoveIgnoredMarginPerCell;
  fs["maxErroneousBitsInBorderRate"] >> params->maxErroneousBitsInBorderRate;
  fs["minOtsuStdDev"] >> params->minOtsuStdDev;
  fs["errorCorrectionRate"] >> params->errorCorrectionRate;
  return true;
}

static bool saveCameraParams(const std::string &filename, cv::Size ImageSize,
                             float aspectRatio, int flag,
                             const cv::Mat &cameraMatrix,
                             const cv::Mat &distCoeffs, double totalAvgError) {
  cv::FileStorage fs(filename, cv::FileStorage::WRITE);
  if (!fs.isOpened()) {
    return false;
  }

  fs << "image_width" << ImageSize.width;
  fs << "image_height" << ImageSize.height;

  if (flag & cv::CALIB_FIX_ASPECT_RATIO) {
    fs << "aspectRatio" << aspectRatio;
  }

  fs << "flag" << flag;
  fs << "camera_matrix" << cameraMatrix;
  fs << "distortion_coefficients" << distCoeffs;
  fs << "avg_reproject_error" << totalAvgError;
  return true;
}

int main(int argc, char const *argv[]) {
  cv::CommandLineParser parser(argc, argv, keys);
  parser.about(about);

  if (argc < 6) {
    parser.printMessage();
    return 0;
  }

  // 获取参数
  int w = parser.get<int>("w");
  int h = parser.get<int>("h");
  float len = parser.get<float>("l");
  float markerSeparation = parser.get<float>("s");
  int dictionaryId = parser.get<int>("d");
  std::string outFile = parser.get<cv::String>(0);

  int calibrationFlag = 0;
  float aspectRatio = 1;

  cv::Ptr<cv::aruco::DetectorParameters> detectorParams =
      cv::aruco::DetectorParameters::create();
  if (parser.has("dp")) {
    bool readOk = readParameters(parser.get<std::string>("dp"), detectorParams);
    if (!readOk) {
      std::cout << "参数文件不符合要求" << std::endl;
      return 0;
    }
  }

  bool refindStrategy = parser.get<bool>("rs");
  int camId = parser.get<int>("ci");

  cv::String video;
  if (parser.has("v")) {
    video = parser.get<cv::String>("v");
  }

  if (!parser.check()) {
    parser.printErrors();
    return 0;
  }

  cv::String videoInput;
  cv::VideoCapture inputVideo;

  bool opened;
  if (!video.empty()) {
    videoInput = video;
    opened = inputVideo.open(video);
  } else {
    videoInput = camId;
    opened = inputVideo.open(camId);
  }

  if (!opened) {
    std::cout << "打开设备失败：" << videoInput << std::endl;
    return 0;
  }

  // 获取tag族
  cv::Ptr<cv::aruco::Dictionary> dictionary =
      cv::aruco::getPredefinedDictionary(dictionaryId);

  // 创建tag板
  cv::Ptr<cv::aruco::GridBoard> gridBoard =
      cv::aruco::GridBoard::create(w, h, len, markerSeparation, dictionary);
  cv::Ptr<cv::aruco::Board> board = gridBoard.staticCast<cv::aruco::Board>();

  std::vector<std::vector<std::vector<cv::Point2f>>> allCorners;
  std::vector<std::vector<int>> allIds;
  cv::Size imageSize;

  while (inputVideo.grab()) {
    cv::Mat image, imageCopy;
    inputVideo.retrieve(image);

    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f>> corners, rejected;

    // 检测tag
    cv::aruco::detectMarkers(image, dictionary, corners, ids, detectorParams,
                             rejected);

    if (refindStrategy) {
      cv::aruco::refineDetectedMarkers(image, board, corners, ids, rejected);
    }

    image.copyTo(imageCopy);
    if (ids.size() > 0) {
      cv::aruco::drawDetectedMarkers(imageCopy, corners, ids,
                                     cv::Scalar(255, 0, 0));
    }
    cv::putText(
        imageCopy,
        "pressed 'C' to add frame, 'esc':finished and start calibration",
        cv::Point(10, 20), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 255, 0),
        2);

    cv::imshow("out", imageCopy);
    char key = (char)cv::waitKey(10);
    if (key == 27) {
      break;
    }
    if (key == 'c' && ids.size() > 0) {
      std::cout << "添加关键帧" << std::endl;
      allCorners.push_back(corners);
      allIds.push_back(ids);
      imageSize = image.size();
    }
  }

  if (allIds.size() < 1) {
    std::cout << "没有足够的图片" << std::endl;
    return 0;
  }

  cv::Mat cameraMatrix, dist;
  std::vector<cv::Mat> rvecs, tvecs;
  double repError;

  if (calibrationFlag & cv::CALIB_FIX_ASPECT_RATIO) {
    cameraMatrix = cv::Mat::eye(3, 3, CV_64F);
    cameraMatrix.at<double>(0, 0) = aspectRatio;
  }

  // 准备标定数据
  std::vector<std::vector<cv::Point2f>> allCornersConcatenated;
  std::vector<int> allIdsConcatenated;
  std::vector<int> markerCounterPerFrame;
  markerCounterPerFrame.reserve(allCorners.size());
  for (int i = 0; i < allCorners.size(); i++) {
    markerCounterPerFrame.push_back((int)allCorners[i].size());
    for (int j = 0; j < allCorners[i].size(); j++) {
      allCornersConcatenated.push_back(allCorners[i][j]);
      allIdsConcatenated.push_back(allIds[i][j]);
    }
  }

  // 标定
  repError = cv::aruco::calibrateCameraAruco(
      allCornersConcatenated, allIdsConcatenated, markerCounterPerFrame, board,
      imageSize, cameraMatrix, dist, rvecs, tvecs, calibrationFlag);
  bool saveOk = saveCameraParams(outFile, imageSize, aspectRatio,
                                 calibrationFlag, cameraMatrix, dist, repError);

  if (!saveOk) {
    std::cout << "不能保存文件" << std::endl;
    return 0;
  }

  std::cout << "重投影误差为：" << repError << std::endl;
  std::cout << "标定文件保存至：" << outFile << std::endl;

  return 0;
}

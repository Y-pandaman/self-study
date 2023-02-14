#include <opencv2/aruco.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

const char *about = "Create an ArUco marker image";
// keys是一个字符串，包含多个块，每一个都被装在大括号里且描述一个参数。每个参数都被
// “| ”符号分隔成三部分。 第一部分是参数名称。
// 第二部分是参数的默认值，可以为空。 第三部分是描述该参数的帮助信息，可以为空。
const char *keys = "{@outfile |<none> | Output image }"
                   "{d        |       | dictionary: DICT_4X4_50=0, "
                   "DICT_4X4_100=1, DICT_4X4_250=2,"
                   "DICT_4X4_1000=3, DICT_5X5_50=4, DICT_5X5_100=5, "
                   "DICT_5X5_250=6, DICT_5X5_1000=7, "
                   "DICT_6X6_50=8, DICT_6X6_100=9, DICT_6X6_250=10, "
                   "DICT_6X6_1000=11, DICT_7X7_50=12,"
                   "DICT_7X7_100=13, DICT_7X7_250=14, DICT_7X7_1000=15, "
                   "DICT_ARUCO_ORIGINAL = 16}"
                   "{id       |       | Marker id in the dictionary }"
                   "{ms       | 200   | Marker size in pixels }"
                   "{mb       | 1     | Number of bits in marker borders }"
                   "{si       | false | show generated image }";

int main(int argc, char *argv[]) {
  CommandLineParser parser(argc, argv, keys);
  parser.about(about);

  if (argc < 4) {
    parser.printMessage();
    return 0;
  }

  int dictionaryId = parser.get<int>("d");
  int markerId = parser.get<int>("id");
  int markerSize = parser.get<int>("ms");
  int markerBorder = parser.get<int>("mb");
  bool showImage = parser.get<bool>("si");
  String out_file = parser.get<String>(0);

  if (!parser.check()) {
    parser.printErrors();
    return 0;
  }

  // 获取tag族
  Ptr<aruco::Dictionary> dictionary =
      aruco::getPredefinedDictionary(dictionaryId);

  // 创建tag
  Mat markerImage;
  aruco::drawMarker(dictionary, markerId, markerSize, markerImage,
                    markerBorder);

  if (showImage) {
    imshow("marker", markerImage);
    waitKey(0);
  }

  imwrite(out_file, markerImage);

  return 0;
}

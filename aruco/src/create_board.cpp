#include <opencv2/aruco.hpp>
#include <opencv2/highgui.hpp>

// 帮助文档
const char *about = "Create an ArUco grid board image";
// keys是一个字符串，包含多个块，每一个都被装在大括号里且描述一个参数。每个参数都被
// “| ”符号分隔成三部分。 第一部分是参数名称。
// 第二部分是参数的默认值，可以为空。 第三部分是描述该参数的帮助信息，可以为空。
const char *keys = "{@outfile |<none> | Output image }"
                   "{w        |       | Number of markers in X direction }"
                   "{h        |       | Number of markers in Y direction }"
                   "{l        |       | Marker side length (in pixels) }"
                   "{s        |       | Separation between two consecutive "
                   "markers in the grid (in pixels)}"
                   "{d        |       | dictionary: DICT_4X4_50=0, "
                   "DICT_4X4_100=1, DICT_4X4_250=2,"
                   "DICT_4X4_1000=3, DICT_5X5_50=4, DICT_5X5_100=5, "
                   "DICT_5X5_250=6, DICT_5X5_1000=7, "
                   "DICT_6X6_50=8, DICT_6X6_100=9, DICT_6X6_250=10, "
                   "DICT_6X6_1000=11, DICT_7X7_50=12,"
                   "DICT_7X7_100=13, DICT_7X7_250=14, DICT_7X7_1000=15, "
                   "DICT_ARUCO_ORIGINAL = 16}"
                   "{m        |       | Margins size (in pixels). Default is "
                   "marker separation (-s) }"
                   "{mb       | 1     | Number of bits in marker borders }"
                   "{si       | false | show generated image }";

int main(int argc, char const *argv[]) {
  cv::CommandLineParser parser(argc, argv, keys);
  parser.about(about);

  if (argc < 7) {
    parser.printMessage();
    return 0;
  }

  // 获取参数
  int w = parser.get<int>("w");
  int h = parser.get<int>("h");
  int markerSize = parser.get<int>("l");
  int markerSeparation = parser.get<int>("s");
  int dictionaryId = parser.get<int>("d");
  int margin = markerSeparation;
  if (parser.has("m")) {
    margin = parser.get<int>("m");
  }

  int markerBorder = parser.get<int>("mb");
  bool showImage = parser.get<bool>("si");
  cv::String outFile = parser.get<cv::String>(0);

  if (!parser.check()) {
    parser.printErrors();
    return 0;
  }

  // 定义board尺寸
  cv::Size imageSize;
  imageSize.width = w * (markerSize + markerSeparation) + markerSeparation;
  imageSize.height = h * (markerSize + markerSeparation) + markerSeparation;

  cv::Ptr<cv::aruco::Dictionary> dictionary =
      cv::aruco::getPredefinedDictionary(dictionaryId);
  // 或者下面这种
  // cv::Ptr<cv::aruco::Dictionary> dictionary =
  //     cv::aruco::getPredefinedDictionary(
  //         cv::aruco::PREDEFINED_DICTIONARY_NAME(dictionaryId));

  // 创建board
  cv::Ptr<cv::aruco::GridBoard> board = cv::aruco::GridBoard::create(
      w, h, markerSize, markerSeparation, dictionary);

  // 创建tag
  cv::Mat boardImage;
  board->draw(imageSize, boardImage, margin, markerBorder);

  if (showImage) {
    cv::imshow("board", boardImage);
    cv::waitKey(0);
  }

  cv::imwrite(outFile, boardImage);

  return 0;
}

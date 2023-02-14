#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/stitching.hpp"
#include <iostream>
#include <sys/time.h>

bool try_use_gpu = false;
bool divide_images = false;
cv::Stitcher::Mode mode = cv::Stitcher::PANORAMA;
std::vector<cv::Mat> imgs;
std::string result_name = "result.jpg";

void printUsage(char **argv) {
    std::cout
        << "Images stitcher.\n\n"
        << "Usage :\n"
        << argv[0]
        << " [Flags] img1 img2 [...imgN]\n\n"
           "Flags:\n"
           "  --d3\n"
           "      internally creates three chunks of each image to increase "
           "stitching success\n"
           "  --try_use_gpu (yes|no)\n"
           "      Try to use GPU. The default value is 'no'. All default values\n"
           "      are for CPU mode.\n"
           "  --mode (panorama|scans)\n"
           "      Determines configuration of stitcher. The default is "
           "'panorama',\n"
           "      mode suitable for creating photo panoramas. Option 'scans' is "
           "suitable\n"
           "      for stitching materials under affine transformation, such as "
           "scans.\n"
           "  --output <result_img>\n"
           "      The default is 'result.jpg'.\n\n"
           "Example usage :\n"
        << argv[0] << " --d3 --try_use_gpu yes --mode scans img1.jpg img2.jpg\n";
}

int parseCmdArgs(int argc, char **argv) {
    if (argc == 1) {
        printUsage(argv);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "--help" || std::string(argv[i]) == "/?" ||
            std::string(argv[i]) == "-h") {
            printUsage(argv);
            return EXIT_FAILURE;
        } else if (std::string(argv[i]) == "--try_use_gpu") {
            if (std::string(argv[i + 1]) == "no") {
                try_use_gpu = false;
            } else if (std::string(argv[i + 1]) == "yes") {
                try_use_gpu = true;
            } else {
                std::cout << "错误的GPU参数\n";
                return EXIT_FAILURE;
            }
            i++;
        } else if (std::string(argv[i]) == "--d3") {
            divide_images = true;
        } else if (std::string(argv[i]) == "--output") {
            result_name = argv[i + 1];
            i++;
        } else if (std::string(argv[i]) == "--mode") {
            if (std::string(argv[i + 1]) == "panorama") {
                mode = cv::Stitcher::PANORAMA;
            } else if (std::string(argv[i + 1]) == "scans") {
                mode = cv::Stitcher::SCANS;
            } else {
                std::cout << "错误的mode参数" << std::endl;
                return EXIT_FAILURE;
            }
            i++;
        } else {
            cv::Mat img = cv::imread(cv::samples::findFile(argv[i]));
            if (img.empty()) {
                std::cout << "读取图片失败" << std::endl;
                return EXIT_FAILURE;
            }

            if (divide_images) {
                cv::Rect rect(0, 0, img.cols / 2, img.rows);
                imgs.push_back(img(rect).clone());
                rect.x = img.cols / 3;
                imgs.push_back(img(rect).clone());
                rect.x = img.cols / 2;
                imgs.push_back(img(rect).clone());
            } else {
                imgs.push_back(img);
            }
        }
    }
    return EXIT_SUCCESS;
}

int main(int argc, char **argv) {
    int retval = parseCmdArgs(argc, argv);
    if (retval) {
        return EXIT_FAILURE;
    }

    cv::Mat pano;
    cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(mode, try_use_gpu);

    struct timeval time;
    gettimeofday(&time, NULL);
    double t1 = time.tv_sec * 1000.0 + time.tv_usec / 1000.0;

    cv::Stitcher::Status status = stitcher->stitch(imgs, pano);

    gettimeofday(&time, NULL);
    double t2 = time.tv_sec * 1000.0 + time.tv_usec / 1000.0;
    std::cout << "拼接耗时：" << t2 - t1 << " 毫秒" << std::endl;

    if (status != cv::Stitcher::OK) {
        std::cout << "不能拼接图像，错误代码为：" << int(status) << std::endl;
        return EXIT_FAILURE;
    }
    cv::imshow("stitched image", pano);

    gettimeofday(&time, NULL);
    double t3 = time.tv_sec * 1000.0 + time.tv_usec / 1000.0;
    std::cout << "显示耗时：" << t3 - t2 << " 毫秒" << std::endl;

    cv::imwrite(result_name, pano);
    std::cout << "拼接成功，保存图片至" << result_name << std::endl;
    cv::waitKey();
    return EXIT_SUCCESS;
}

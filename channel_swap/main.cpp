#include <opencv2/opencv.hpp>
#include <iostream>

cv::Mat channel_swap(cv::Mat img)
{
    // チャンネルを分割
    std::vector<cv::Mat> channels(3);
    cv::split(img, channels);

    // 青と赤チャネルを入れ替え
    std::swap(channels[0], channels[2]);

    // チャンネルをマージして出力画像を作成
    cv::Mat out;
    cv::merge(channels, out);

    return out;
}

int main(int argc, const char *argv[])
{
    cv::Mat img = cv::imread("../image.jpg", cv::IMREAD_COLOR);

    // 画像の読み込みに失敗した場合
    if (img.empty())
    {
        std::cerr << "Error: Image not found or unable to open!" << std::endl;
        return -1;
    }

    cv::Mat out = channel_swap(img);

    cv::imshow("sample", out);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}

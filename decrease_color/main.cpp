#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <math.h>

cv::Mat decrease_color(cv::Mat img)
{
    int width = img.cols;
    int height = img.rows;
    int channels = img.channels();

    cv::Mat out = cv::Mat::zeros(height, width, CV_8UC3);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < channels; c++)
            {
                if (0 <= img.at<cv::Vec3b>(y, x)[c] && img.at<cv::Vec3b>(y, x)[c] < 64)
                {
                    out.at<cv::Vec3b>(y, x)[c] = 32;
                }
                else if (64 <= img.at<cv::Vec3b>(y, x)[c] && img.at<cv::Vec3b>(y, x)[c] < 128)
                {
                    out.at<cv::Vec3b>(y, x)[c] = 96;
                }
                else if (128 <= img.at<cv::Vec3b>(y, x)[c] && img.at<cv::Vec3b>(y, x)[c] < 192)
                {
                    out.at<cv::Vec3b>(y, x)[c] = 160;
                }
                else
                {
                    out.at<cv::Vec3b>(y, x)[c] = 224;
                }
            }
        }
    }
    return out;
}

int main(int argc, const char *argv[])
{
    cv::Mat img = cv::imread("../image.jpg", cv::IMREAD_COLOR);
    cv::Mat out = decrease_color(img);

    cv::imshow("sample", out);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
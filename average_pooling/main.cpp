#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <math.h>

cv::Mat average_pooling(cv::Mat img)
{
    int height = img.rows;
    int width = img.cols;
    int channels = img.channels();

    cv::Mat out = cv::Mat::zeros(height, width, CV_8UC3);

    int r = 8;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < channels; c++)
            {
                double v = 0;
                for (int dy = 0; dy < r; dy++)
                {
                    for (int dx = 0; dx < r; dx++)
                    {
                        v += (double)img.at<cv::Vec3b>(y + dy, x + dx)[c];
                    }
                }
                v /= (r * r);
                for (int dy = 0; dy < r; dy++)
                {
                    for (int dx = 0; dx < r; dx++)
                    {
                        out.at<cv::Vec3b>(y + dy, x + dx)[c] = (uchar)v;
                    }
                }
            }
        }
    }
    return out;
}

int main(int argc, const char *argv[])
{
    cv::Mat img = cv::imread("../image.jpg", cv::IMREAD_COLOR);
    cv::Mat out = average_pooling(img);

    cv::imshow("sample", out);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cmath>

cv::Mat BGR2HSV(cv::Mat img)
{
    int width = img.cols;
    int height = img.rows;

    cv::Mat hsv = cv::Mat::zeros(height, width, CV_32FC3);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            float r = img.at<cv::Vec3b>(y, x)[2] / 255.0f;
            float g = img.at<cv::Vec3b>(y, x)[1] / 255.0f;
            float b = img.at<cv::Vec3b>(y, x)[0] / 255.0f;

            float max = std::max({r, g, b});
            float min = std::min({r, g, b});

            float h, s, v;
            v = max;

            float delta = max - min;

            if (max == 0)
            {
                s = 0;
            }
            else
            {
                s = delta / max;
            }

            if (delta == 0)
            {
                h = 0;
            }
            else
            {
                if (max == r)
                {
                    h = 60 * (((g - b) / delta));
                }
                else if (max == g)
                {
                    h = 60 * (((b - r) / delta) + 2);
                }
                else
                {
                    h = 60 * (((r - g) / delta) + 4);
                }

                if (h < 0)
                {
                    h += 360;
                }
            }

            hsv.at<cv::Vec3f>(y, x)[0] = h;
            hsv.at<cv::Vec3f>(y, x)[1] = s;
            hsv.at<cv::Vec3f>(y, x)[2] = v;
        }
    }

    return hsv;
}

cv::Mat inverse_hue(cv::Mat hsv)
{
    int height = hsv.rows;
    int width = hsv.cols;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            hsv.at<cv::Vec3f>(y, x)[0] = fmod(hsv.at<cv::Vec3f>(y, x)[0] + 180, 360);
        }
    }
    return hsv;
}

int main(int argc, const char *argv[])
{
    cv::Mat img = cv::imread("../image.jpg", cv::IMREAD_COLOR);

    cv::Mat hsv = BGR2HSV(img);
    cv::Mat HSV = inverse_hue(hsv);

    cv::imshow("sample", HSV);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

cv::Mat HSV2BGR(cv::Mat hsv)
{
    int width = hsv.cols;
    int height = hsv.rows;

    cv::Mat bgr = cv::Mat::zeros(height, width, CV_8UC3);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            float h = hsv.at<cv::Vec3f>(y, x)[0];
            float s = hsv.at<cv::Vec3f>(y, x)[1];
            float v = hsv.at<cv::Vec3f>(y, x)[2];

            float c = s * v;
            float H = h / 60.0f;
            float X = c * (1 - fabs(fmod(H, 2) - 1));
            float m = v - c;

            float r, g, b;
            if (0 <= H && H < 1)
            {
                r = c;
                g = X;
                b = 0;
            }
            else if (1 <= H && H < 2)
            {
                r = X;
                g = c;
                b = 0;
            }
            else if (2 <= H && H < 3)
            {
                r = 0;
                g = c;
                b = X;
            }
            else if (3 <= H && H < 4)
            {
                r = 0;
                g = X;
                b = c;
            }
            else if (4 <= H && H < 5)
            {
                r = X;
                g = 0;
                b = c;
            }
            else
            {
                r = c;
                g = 0;
                b = X;
            }

            bgr.at<cv::Vec3b>(y, x)[0] = (uchar)((b + m) * 255);
            bgr.at<cv::Vec3b>(y, x)[1] = (uchar)((g + m) * 255);
            bgr.at<cv::Vec3b>(y, x)[2] = (uchar)((r + m) * 255);
        }
    }

    return bgr;
}

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
    cv::Mat inverted_hue = inverse_hue(hsv);
    cv::Mat bgr = HSV2BGR(inverted_hue);

    cv::imshow("Inverted Hue Image", bgr);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}

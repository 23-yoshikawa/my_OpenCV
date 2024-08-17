#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <math.h>

void gaussian_filter(unsigned char *input, unsigned char *output, int width, int height, int channels, double sigma, int kernel_size)
{
    int pad = kernel_size / 2;
    std::vector<std::vector<double>> kernel(kernel_size, std::vector<double>(kernel_size));
    double kernel_sum = 0.0;

    for (int y = 0; y < kernel_size; y++)
    {
        for (int x = 0; x < kernel_size; x++)
        {
            int Y = y - pad;
            int X = x - pad;
            kernel[y][x] = exp(-(X * X + Y * Y) / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
            kernel_sum += kernel[y][x];
        }
    }
    for (int y = 0; y < kernel_size; y++)
    {
        for (int x = 0; x < kernel_size; x++)
        {
            kernel[y][x] /= kernel_sum;
        }
    }
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < channels; c++)
            {
                double v = 0.0;
                for (int dy = -pad; dy <= pad; dy++)
                {
                    for (int dx = -pad; dx <= pad; dx++)
                    {
                        int yy = std::min(std::max(y + dy, 0), height - 1);
                        int xx = std::min(std::max(x + dx, 0), width - 1);
                        v += input[(yy * width + xx) * channels + c] * kernel[dy + pad][dx + pad];
                    }
                }
                output[(y * width + x) * channels + c] = cv::saturate_cast<uchar>(v);
            }
        }
    }
}

int main(int argc, const char *argv[])
{
    cv::Mat img = cv::imread("../imori_noise.jpg", cv::IMREAD_COLOR);

    int width = img.cols;
    int height = img.rows;
    int channels = img.channels();

    unsigned char *output = new unsigned char[width * height * channels];

    gaussian_filter(img.data, output, width, height, channels, 1.3, 3);

    cv::Mat out(height, width, CV_8UC3, output);

    cv::imshow("sample", out);
    cv::waitKey(0);
    cv::destroyAllWindows();

    delete[] output;

    return 0;
}
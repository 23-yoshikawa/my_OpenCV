#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>

void BGR2GRAY(const unsigned char *bgr, unsigned char *gray, int width, int height)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = (y * width + x) * 3;
            float gray_value = 0.2126f * bgr[index + 2] + 0.7152f * bgr[index + 1] + 0.0722f * bgr[index];
            gray[y * width + x] = static_cast<unsigned char>(gray_value);
        }
    }
}

void Binarize(const unsigned char *gray, unsigned char *binary, int width, int height, int th)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            binary[y * width + x] = (gray[y * width + x] > th) ? 255 : 0;
        }
    }
}

int main()
{
    cv::Mat img = cv::imread("../image.jpg", cv::IMREAD_COLOR);
    if (img.empty())
    {
        std::cerr << "Error loading image" << std::endl;
        return -1;
    }
    int width = img.cols;
    int height = img.rows;

    // Allocate memory for brg,gray,binary image data
    std::vector<unsigned char> bgr(img.total() * img.channels());
    std::vector<unsigned char> gray(img.total());
    std::vector<unsigned char> binary(img.total());

    // Copy BGR data
    std::memcpy(bgr.data(), img.data, bgr.size());

    // Convert BGR to Gray
    BGR2GRAY(bgr.data(), gray.data(), width, height);

    // Binarize the grayscale image
    Binarize(gray.data(), binary.data(), width, height, 128);

    cv::Mat binary_img(height, width, CV_8UC1, binary.data());
    cv::imshow("Binary Image", binary_img);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

// BGR -> Gray
unsigned char *BGR2GRAY(const unsigned char *img, int width, int height)
{
    // グレースケール画像用のバッファを確保
    unsigned char *out = new unsigned char[width * height];

    // 各ピクセルを処理
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // ピクセルインデックス計算
            // 2次元配列を1次元配列に変換
            int index = y * width + x;
            int bgr_index = index * 3;

            // BGR -> Gray
            out[index] = static_cast<unsigned char>(
                0.2126 * img[bgr_index + 2] + // Red
                0.7152 * img[bgr_index + 1] + // Green
                0.0722 * img[bgr_index]       // Blue
            );
        }
    }

    return out;
}

int main(int argc, const char *argv[])
{
    // 画像ファイルを読み込む
    cv::Mat imgMat = cv::imread("../image.jpg", cv::IMREAD_COLOR);

    if (imgMat.empty())
    {
        std::cerr << "Error: Image not found or unable to open!" << std::endl;
        return -1;
    }

    // 画像サイズを取得
    int width = imgMat.cols;
    int height = imgMat.rows;

    // 画像データをポインタで取得
    unsigned char *img = imgMat.data;

    // BGR -> Gray変換
    unsigned char *out = BGR2GRAY(img, width, height);

    // 結果をcv::Matとして表示するために再構築
    cv::Mat outMat(height, width, CV_8UC1, out);
    cv::imshow("sample", outMat);
    cv::waitKey(0);
    cv::destroyAllWindows();

    // メモリ解放
    delete[] out;

    return 0;
}

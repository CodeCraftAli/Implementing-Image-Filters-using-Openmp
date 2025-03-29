#include <iostream>
#include <vector>
#include <omp.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// Function to apply Gaussian Blur
void applyBlur(const Mat& input, Mat& output) {
    int kernelSize = 15;
    int halfKernel = kernelSize / 2;
    float kernelValue = 1.0f / (kernelSize * kernelSize);

    output = Mat(input.size(), input.type());

#pragma omp parallel for
    for (int i = 0; i < input.rows; ++i) {
        for (int j = 0; j < input.cols; ++j) {
            Vec3f pixelSum(0, 0, 0);
            for (int k = -halfKernel; k <= halfKernel; ++k) {
                for (int l = -halfKernel; l <= halfKernel; ++l) {
                    int x = min(max(i + k, 0), input.rows - 1);
                    int y = min(max(j + l, 0), input.cols - 1);
                    Vec3b pixel = input.at<Vec3b>(x, y);
                    pixelSum[0] += pixel[0] * kernelValue;
                    pixelSum[1] += pixel[1] * kernelValue;
                    pixelSum[2] += pixel[2] * kernelValue;
                }
            }
            output.at<Vec3b>(i, j) = Vec3b((uchar)pixelSum[0], (uchar)pixelSum[1], (uchar)pixelSum[2]);
        }
    }
}

// Function to convert to Grayscale
void applyGrayscale(const Mat& input, Mat& output) {
    Mat kernel = (Mat_<float>(1, 3) << 0.114, 0.587, 0.299);
    Mat floatInput;
    input.convertTo(floatInput, CV_32FC3);
    vector<Mat> channels(3);
    split(floatInput, channels);

    output = channels[0] * kernel.at<float>(0, 0) +
        channels[1] * kernel.at<float>(0, 1) +
        channels[2] * kernel.at<float>(0, 2);
    output.convertTo(output, CV_8UC1);
}

// Function to add a Bluish Tint
void applyBluishTint(const Mat& input, Mat& output) {
    output = Mat(input.size(), input.type());

#pragma omp parallel for
    for (int i = 0; i < input.rows; ++i) {
        for (int j = 0; j < input.cols; ++j) {
            Vec3b pixel = input.at<Vec3b>(i, j);
            output.at<Vec3b>(i, j) = Vec3b(
                min(255, static_cast<int>(pixel[0] * 1.8)),
                min(255, static_cast<int>(pixel[1] * 0.9)),
                min(255, static_cast<int>(pixel[2] * 0.9))
            );
        }
    }
}

int main() {
    string inputPath, outputPath;
    int choice;

    cout << "Enter the path to the input image: ";
    cin >> inputPath;

    Mat inputImage = imread(inputPath);
    if (inputImage.empty()) {
        cerr << "Error: Could not load the image." << endl;
        return -1;
    }

    Mat outputImage;

    while (true) {
        cout << "\nSelect an option to apply a filter on the image:\n";
        cout << "1. Blur the Image\n";
        cout << "2. Convert to Grayscale\n";
        cout << "3. Add Bluish Tint\n";
        cout << "4. Exit\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        if (choice == 4) {
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        }

        switch (choice) {
        case 1:
            applyBlur(inputImage, outputImage);
            cout << "Enter the path to save the blurred image: ";
            break;
        case 2:
            applyGrayscale(inputImage, outputImage);
            cout << "Enter the path to save the grayscale image: ";
            break;
        case 3:
            applyBluishTint(inputImage, outputImage);
            cout << "Enter the path to save the bluish-tint image: ";
            break;
        default:
            cout << "Invalid choice. Please select again." << endl;
            continue;
        }

        cin >> outputPath;
        if (imwrite(outputPath, outputImage)) {
            cout << "Image saved as " << outputPath << endl;
        }
        else {
            cerr << "Error: Could not save the image." << endl;
        }
    }

    return 0;
}
#include <gtest/gtest.h>
#include <chrono>
#include "BMP.h"

TEST(Test_1, Rotate90Clockwise) {
    BMP image_1("file.bmp");
    BMP image_1_paralell("file.bmp");

    auto start = std::chrono::high_resolution_clock::now();
    image_1.Rotate90Clockwise();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    auto start_paralell = std::chrono::high_resolution_clock::now();
    image_1_paralell.Rotate90Clockwise_paralell();
    auto end_paralell = std::chrono::high_resolution_clock::now();
    auto duration_paralell = std::chrono::duration_cast<std::chrono::microseconds>(end_paralell - start_paralell).count();

    std::cout << "Rotate90Clockwise: without parallelism = " << duration << ", with parallelism = " << duration_paralell << " us\n";
    EXPECT_TRUE(duration > duration_paralell);

}

TEST(Test_2, Rotate90CounterClockwise) {
    BMP image_1("file.bmp");
    BMP image_1_paralell("file.bmp");

    auto start = std::chrono::high_resolution_clock::now();
    image_1.Rotate90CounterClockwise();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    auto start_paralell = std::chrono::high_resolution_clock::now();
    image_1_paralell.Rotate90CounterClockwise_paralell();
    auto end_paralell = std::chrono::high_resolution_clock::now();
    auto duration_paralell = std::chrono::duration_cast<std::chrono::microseconds>(end_paralell - start_paralell).count();

    std::cout << "Rotate90CounterClockwise:  without parallelism = " << duration << ", with parallelism = " << duration_paralell << " us\n";
    EXPECT_TRUE(duration > duration_paralell);

}

TEST(Test_3, GaussianBlur_Performance) {
    BMP image_1("file.bmp");
    BMP image_1_paralell("file.bmp");

    auto start = std::chrono::high_resolution_clock::now();
    image_1.GaussianBlur();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    auto start_paralell = std::chrono::high_resolution_clock::now();
    image_1_paralell.GaussianBlur_paralell();
    auto end_paralell = std::chrono::high_resolution_clock::now();
    auto duration_paralell = std::chrono::duration_cast<std::chrono::microseconds>(end_paralell - start_paralell).count();

    std::cout << "GaussianBlur: without parallelism = " << duration << ", with parallelism = " << duration_paralell << " us\n";
    
    EXPECT_TRUE(duration > duration_paralell);

}

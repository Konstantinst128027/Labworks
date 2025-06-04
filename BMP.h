/* Berezkin Konstantin Evgenievich
./labwork st128027@student.spbu.ru*/
#ifndef BMP_H
#define BMP_H

#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <cstdint>
#include <thread>
#include <atomic>
#include <functional>

#pragma pack(push, 1)
struct BMPFileHeader
{
    uint16_t file_type{0x4D42};
    uint32_t file_size{0};
    uint16_t reserved1{0};
    uint16_t reserved2{0};
    uint32_t offset_data{0};
};

struct BMPInfoHeader
{
    uint32_t size{0};
    int32_t width{0};
    int32_t height{0};
    uint16_t planes{1};
    uint16_t bit_count{0};
    uint32_t compression{0};
    uint32_t size_image{0};
    int32_t x_pixels_per_meter{0};
    int32_t y_pixels_per_meter{0};
    uint32_t colors_used{0};
    uint32_t colors_important{0};
}; 

struct BMPColorHeader
{
    uint32_t red_mask{0x00ff0000};
    uint32_t blue_mask{0x000000ff};
    uint32_t green_mask{0x0000ff00};
    uint32_t alpha_mask{0xff000000};
    uint32_t color_space_type{0x73524742};
    uint32_t unused[16] {0};
};
#pragma pack(pop)

class BMP
{
public:

    BMP(const char* filename);
    void Rotate90Clockwise_paralell();
    void Rotate90CounterClockwise_paralell();
    void GaussianBlur_paralell();
    
    void Rotate90Clockwise();
    void Rotate90CounterClockwise();
    void GaussianBlur();

    void Save(const char* filename);

private:
    BMPFileHeader header;
    BMPInfoHeader info_header;
    BMPColorHeader color_header;
    std::vector<uint8_t> data;

    // a framework for flow control
    struct ThreadPool {
        std::vector<std::thread> workers; // vector for storing streams
        std::atomic<bool> stop{false}; // flag for stopping streams

        ~ThreadPool() { // destructor (threads are processed to the end)
            {
                stop = true; //sets the stop flag
            }
            for (std::thread& worker : workers) { // We let them finish
                if (worker.joinable()) { // checks if it's still working, and if it's working, lets it finish.
                    worker.join();  // waiting for the completion of threads
                }
            }
        }
    };
    
    void ParallelRowProcessing(std::function<void(int)> processRow, int totalRows);

};

#endif

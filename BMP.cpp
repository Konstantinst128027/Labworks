/* Berezkin Konstantin Evgenievich
./labwork1 st128027@student.spbu.ru*/
#include "BMP.h"

BMP::BMP(const char* filename)
{
    std::ifstream input(filename, std::ios_base::binary);
    if (!input)
    {
        throw std::runtime_error("File isn't open!");
    }

    input.read((char*)&header, sizeof(header));
    if (header.file_type != 0x4D42)
    {
        throw std::runtime_error("File isn't BMP");
    }

    input.read((char*)&info_header, sizeof(info_header));

    if (info_header.bit_count == 24)
    {
        input.read((char*)&color_header, sizeof(color_header));
    }
    input.seekg(header.offset_data, input.beg);
    data.resize(info_header.size_image);
    input.read((char*)data.data(), data.size());
}

void BMP::ParallelRowProcessing(std::function<void(int)> processRow, int totalRows) { // accepts a function that will process one row and pass the number of rows
    unsigned numThreads = std::thread::hardware_concurrency();// determining the number of threads
    ThreadPool pool; // a vector of workers is created, and a stop (flag for stopping) is set
    std::atomic<size_t> currentRow(0); // atomic guarantees that two cashiers will not give out the same number.

    auto worker = [&]() {
        while (true) {
            size_t row = currentRow.fetch_add(1); // gets the current value, increments it by 1, and returns the original value.
            if (row >= static_cast<size_t>(totalRows)) {
                break;
            }

            processRow(row);
        }
    };
    
    for (unsigned i = 0; i < numThreads; ++i) {
        pool.workers.emplace_back(worker);
    } // then the destructor runs and the threads finish their work.
}
void BMP::Rotate90Clockwise_paralell()
{
    int new_row_size = (info_header.height * 3 + 3) & (~3);
    std::vector<uint8_t> rotated_data(new_row_size * info_header.width);
    int old_row_stride = (info_header.width * 3 + 3) & (~3);

    auto processRow = [&](int y) {
        for (int x = 0; x < info_header.width; ++x) {
            int old_index = y * old_row_stride + x * 3;
            int new_index = (info_header.width - x - 1) * new_row_size + y * 3;

            rotated_data[new_index] = data[old_index];
            rotated_data[new_index + 1] = data[old_index + 1];
            rotated_data[new_index + 2] = data[old_index + 2];
        }
    };

    ParallelRowProcessing(processRow, info_header.height);

    std::swap(info_header.width, info_header.height);
    data = std::move(rotated_data);
}

void BMP::Rotate90CounterClockwise_paralell()
{
    int new_row_size = (info_header.height * 3 + 3) & (~3);
    std::vector<uint8_t> rotated_data(new_row_size * info_header.width);
    int old_row_stride = (info_header.width * 3 + 3) & (~3);

    auto processRow = [&](int y) {
        for (int x = 0; x < info_header.width; ++x) {
            int old_index = y * old_row_stride + x * 3;
            int new_index = x * new_row_size + (info_header.height - y - 1) * 3;

            rotated_data[new_index] = data[old_index];
            rotated_data[new_index + 1] = data[old_index + 1];
            rotated_data[new_index + 2] = data[old_index + 2];
        }
    };

    ParallelRowProcessing(processRow, info_header.height);

    std::swap(info_header.width, info_header.height);
    data = std::move(rotated_data);
}

void BMP::GaussianBlur_paralell()
{
    const float kernel[3][3] = {
        {1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f},
        {2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f},
        {1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f}
    };
    
    std::vector<uint8_t> blurred_data(data.size());
    int channels = info_header.bit_count / 8;
    int width = info_header.width;
    int height = info_header.height;

    auto processRow = [&](int y) {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < channels; c++)
            {
                float color = 0.0f;

                for (int ky = -1; ky <= 1; ky++)
                {
                    for (int kx = -1; kx <= 1; kx++)
                    {
                        int pixel_x = std::min(std::max(x + kx, 0), width - 1);
                        int pixel_y = std::min(std::max(y + ky, 0), height - 1);

                        color += data[(pixel_y * width + pixel_x) * channels + c] * kernel[ky + 1][kx + 1];
                    }
                }
                if (color < 0) color = 0;
                if (color > 255) color = 255;

                blurred_data[(y * width + x) * channels + c] = static_cast<uint8_t>(color);
            }
        }
    };

    ParallelRowProcessing(processRow, height);
    data = blurred_data;
}

void BMP::Rotate90Clockwise()
{
    int new_row_size = (info_header.height * 3 + 3) & (~3);
    std::vector<uint8_t> rotated_data(new_row_size * info_header.width);

    for (int y = 0; y < info_header.height; ++y)
    {
        for (int x = 0; x < info_header.width; ++x)
        {
            int old_index = y * ((info_header.width * 3 + 3) & (~3)) + x * 3;
            int new_index = (info_header.width - x - 1) * new_row_size + y * 3;

            rotated_data[new_index] = data[old_index];
            rotated_data[new_index + 1] = data[old_index + 1];
            rotated_data[new_index + 2] = data[old_index + 2];
        }
    }

    std::swap(info_header.width, info_header.height);
    data = std::move(rotated_data);
}

void BMP::Rotate90CounterClockwise()
{
    int new_row_size = (info_header.height * 3 + 3) & (~3);
    std::vector<uint8_t> rotated_data(new_row_size * info_header.width);

    for (int y = 0; y < info_header.height; ++y)
    {
        for (int x = 0; x < info_header.width; ++x)
        {
            int old_index = y * ((info_header.width * 3 + 3) & (~3)) + x * 3;
            int new_index = x * new_row_size + (info_header.height - y - 1) * 3;

            rotated_data[new_index] = data[old_index];
            rotated_data[new_index + 1] = data[old_index + 1];
            rotated_data[new_index + 2] = data[old_index + 2];
        }
    }

    std::swap(info_header.width, info_header.height);
    data = std::move(rotated_data);
}

void BMP::GaussianBlur()
{
    const float kernel[3][3] = {
        {1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f},
        {2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f},
        {1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f}
    };
    
    std::vector<uint8_t> blurred_data(data.size());
    int channels = info_header.bit_count / 8;
    int width = info_header.width;
    int height = info_header.height;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < channels; c++)
            {
                float color = 0.0f;

                for (int ky = -1; ky <= 1; ky++)
                {
                    for (int kx = -1; kx <= 1; kx++)
                    {
                        int pixel_x = std::min(std::max(x + kx, 0), width - 1);
                        int pixel_y = std::min(std::max(y + ky, 0), height - 1);

                        color += data[(pixel_y * width + pixel_x) * channels + c] * kernel[ky + 1][kx + 1];
                    }
                }
                if (color < 0) color = 0;
                if (color > 255) color = 255;

                blurred_data[(y * width + x) * channels + c] = static_cast<uint8_t>(color);
            }
        }
    }

    data = blurred_data;
}
void BMP::Save(const char* filename)
{
    std::ofstream output(filename, std::ios_base::binary);
    if (!output)
    {
        throw std::runtime_error("Error when opening a file for writing");
    }

    output.write((char*)&header, sizeof(header));
    output.write((char*)&info_header, sizeof(info_header));

    if (info_header.bit_count == 24)
    {
        output.write((char*)&color_header, sizeof(color_header));
    }

    output.write((char*)data.data(), data.size());
}

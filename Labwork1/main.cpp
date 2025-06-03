/* Berezkin Konstantin Evgenievich
./assignment4 st128027@student.spbu.ru*/
#include "BMP.h"
#include <chrono>

int main()
{
    try {
        auto start = std::chrono::high_resolution_clock::now();
        BMP image_1("file.bmp");
        image_1.Rotate90Clockwise();
        image_1.Save("Rotated90Clockwise.bmp");

        BMP image_2("file.bmp");
        image_2.Rotate90CounterClockwise();
        image_2.Save("Rotate90CounterClockwise.bmp");

        BMP image_3("file.bmp");
        image_3.GaussianBlur();
        image_3.Save("GaussianBlur.bmp");
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "all process completed in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
    }
    catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }

return 0;
}

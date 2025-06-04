/* Berezkin Konstantin Evgenievich
./labwork1 st128027@student.spbu.ru*/
#include "BMP.h"
#include <chrono>
#include <iomanip> // for working with tables

int main() {
    try {
    
        std::cout << std::left << std::setw(20) << "Process" << std::setw(20) << "without paralellism" << std::setw(20) << "with paralellism" << "\n";
        // Separator
        std::cout << std::setfill('-') << std::setw(60) << "" << std::setfill(' ') << "\n";
        
        // 1
        //Rotate90Clockwise without paralellism
        
        auto start = std::chrono::high_resolution_clock::now();
        
        BMP image_1("file.bmp");
        image_1.Rotate90Clockwise();
        image_1.Save("Rotated90Clockwise.bmp");
        
        auto end = std::chrono::high_resolution_clock::now();
        
        auto without_paralellism_Rotated90Clockwise = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        
        //Rotate90Clockwise with paralellism
        
        auto start_paralellism = std::chrono::high_resolution_clock::now();
        
        BMP image_1_paralell("file.bmp");
        image_1_paralell.Rotate90Clockwise_paralell();
        image_1_paralell.Save("Rotated90Clockwise_paralell.bmp");
        
        auto end_paralellism = std::chrono::high_resolution_clock::now();
        
        auto paralellism_Rotated90Clockwise = std::chrono::duration_cast<std::chrono::milliseconds>(end_paralellism - start_paralellism).count();
        
        // Output Rotate90Clockwise
        std::cout << std::left << std::setw(20) << "Rotate90Clockwise" << std::setw(20) << without_paralellism_Rotated90Clockwise << std::setw(20) << paralellism_Rotated90Clockwise << "\n";
        
        // 2
        //Rotate90CounterClockwise without paralellism
        
        start = std::chrono::high_resolution_clock::now();
        
        BMP image_2("file.bmp");
        image_2.Rotate90CounterClockwise();
        image_2.Save("Rotate90CounterClockwise.bmp");
        
        end = std::chrono::high_resolution_clock::now();
        
        auto without_paralellism_Rotate90CounterClockwise = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        
        //Rotate90Clockwise with paralellism
        
        start_paralellism = std::chrono::high_resolution_clock::now();
        
        BMP image_2_paralell("file.bmp");
        image_2_paralell.Rotate90CounterClockwise_paralell();
        image_2_paralell.Save("Rotate90CounterClockwise_paralell.bmp");
        
        end_paralellism = std::chrono::high_resolution_clock::now();
        
        auto paralellism_Rotate90CounterClockwise = std::chrono::duration_cast<std::chrono::milliseconds>(end_paralellism - start_paralellism).count();
        
        // Output Rotate90CounterClockwise
        std::cout << std::left << std::setw(20) << "Rotate90CoClockwise" << std::setw(20) << without_paralellism_Rotate90CounterClockwise << std::setw(20) << paralellism_Rotate90CounterClockwise << "\n";


        // 3
        //GaussianBlur without paralellism
        
        start = std::chrono::high_resolution_clock::now();
        
        BMP image_3("file.bmp");
        image_3.GaussianBlur();
        image_3.Save("GaussianBlur.bmp");
        
        end = std::chrono::high_resolution_clock::now();
        
        auto without_paralellism_GaussianBlur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        
        //GaussianBlur with paralellism
        
        start_paralellism = std::chrono::high_resolution_clock::now();
        
        BMP image_3_paralell("file.bmp");
        image_3_paralell.GaussianBlur_paralell();
        image_3_paralell.Save("GaussianBlur_paralell.bmp");
        
        end_paralellism = std::chrono::high_resolution_clock::now();
        
        auto paralellism_GaussianBlur = std::chrono::duration_cast<std::chrono::milliseconds>(end_paralellism - start_paralellism).count();
        
        // Output GaussianBlur
        std::cout << std::left << std::setw(20) << "GaussianBlur" << std::setw(20) << without_paralellism_GaussianBlur << std::setw(20) << paralellism_GaussianBlur << "\n";

        auto all = without_paralellism_Rotated90Clockwise + without_paralellism_Rotate90CounterClockwise + without_paralellism_GaussianBlur;
        auto all_paralellism = paralellism_Rotated90Clockwise + paralellism_Rotate90CounterClockwise + paralellism_GaussianBlur;
        
	//Output all
	std::cout << std::left << std::setw(20) << "All" << std::setw(20) << all << std::setw(20) << all_paralellism << "\n";
        
        
    }
    catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;

}

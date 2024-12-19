/* Berezkin Konstantin Evgenievich
./assignment4 st128027@student.spbu.ru*/
#include "BMP.h"

int main()
{
BMP image_1("file.bmp");
image_1.Rotate90Clockwise();
image_1.Save("Rotated90Clockwise.bmp");

BMP image_2("file.bmp");
image_2.Rotate90CounterClockwise();
image_2.Save("Rotate90CounterClockwise.bmp");

BMP image_3("file.bmp");
image_3.GaussianBlur();
image_3.Save("GaussianBlur.bmp");

return 0;
}

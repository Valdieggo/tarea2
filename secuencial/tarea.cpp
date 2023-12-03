#include <iostream>
#include <opencv2/opencv.hpp>
#include <ctime>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    // Verificar si se proporciona la ruta de la imagen como argumento
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <path_to_image>" << endl;
        return -1;
    }

    unsigned t0, t1;

    t0 = clock();
    // Lee el archivo de imagen desde la línea de comandos
    Mat image = imread(argv[1], IMREAD_COLOR);

    if (image.empty())
    {
        cerr << "Could not open or find the image." << endl;
        return -1;
    }

    int width = image.cols;
    int height = image.rows;

    // Lee cada píxel (píxel RGB).
    for (int r = 0; r < image.rows; r++)
    {
        for (int c = 0; c < image.cols; c++)
        {
            Vec3b *p = image.ptr<Vec3b>(r, c); // x:B y:G z:R

            // Calcula la suma ponderada de los valores RGB
            int sum = 0.11 * (*p)[0] + 0.59 * (*p)[1] + 0.3 * (*p)[2];

            // Asigna la suma a cada canal
            (*p)[0] = sum; // Canal azul
            (*p)[1] = sum; // Canal verde
            (*p)[2] = sum; // Canal rojo
        }
    }

    cout << "Image Width: " << width << endl;
    cout << "Image Height: " << height << endl;
    t1 = clock();

    double time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << " seconds" << endl;

    // Mostrar imagen
    imshow("image", image);
    waitKey(0);

    return 0;
}

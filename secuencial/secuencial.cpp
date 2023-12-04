#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace cv;
using namespace std;
using namespace chrono;

int main(int argc, char **argv)
{
    // Verificar si se proporciona la ruta de la imagen como argumento
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <path_to_image>" << endl;
        return -1;
    }

    // Iniciar el reloj
    auto start = high_resolution_clock::now();

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

    // Detener el reloj y calcular el tiempo de ejecución
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Image Width: " << width << endl;
    cout << "Image Height: " << height << endl;
    cout << "Execution Time: " << duration.count() / 1000.0 << " seconds" << endl;

    // Mostrar imagen
    imshow("image", image);
    waitKey(0);

    return 0;
}

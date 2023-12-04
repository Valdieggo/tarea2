#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace cv;
using namespace std;
using namespace chrono;

int main(int argc, char **argv)
{
    // Verificar si se proporciona la ruta de la imagen y el número de hilos como argumentos
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <path_to_image> <num_threads>" << endl;
        return -1;
    }

    // Obtener la ruta de la imagen desde la línea de comandos
    string imagePath = argv[1];

    // Obtener el número de hilos desde la línea de comandos
    int numThreads = atoi(argv[2]);

    // Iniciar el reloj
    auto start = high_resolution_clock::now();

    // Leer el archivo de imagen desde la línea de comandos
    Mat image = imread(imagePath, IMREAD_COLOR);

    if (image.empty())
    {
        cerr << "Could not open or find the image." << endl;
        return -1;
    }

    int width = image.cols;
    int height = image.rows;

#pragma omp parallel for num_threads(numThreads)
    for (int r = 0; r < image.rows; r++)
    {
        for (int c = 0; c < image.cols; c++)
        {
            Vec3b *p = image.ptr<Vec3b>(r, c);

            int sum = 0.11 * (*p)[0] + 0.59 * (*p)[1] + 0.3 * (*p)[2];

            (*p)[0] = sum;
            (*p)[1] = sum;
            (*p)[2] = sum;
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

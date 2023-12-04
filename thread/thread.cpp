#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>
#include <ctime>

using namespace cv;
using namespace std;

// Función para procesar una porción de la imagen en paralelo
void processImagePart(Mat &image, int startRow, int endRow)
{
    for (int r = startRow; r < endRow; r++)
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
}

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

    // Número de hilos a utilizar (ajústalo según tu hardware)
    const int numThreads = 4;

    // Vector para almacenar los hilos
    vector<thread> threads;

    // Dividir la imagen entre los hilos
    int rowsPerThread = height / numThreads;
    int remainingRows = height % numThreads;

    int startRow = 0;
    int endRow = rowsPerThread;

    // Crear y ejecutar hilos
    for (int i = 0; i < numThreads; i++)
    {
        // El último hilo se encarga de las filas restantes
        if (i == numThreads - 1)
        {
            endRow += remainingRows;
        }

        // Crear hilo y ejecutar la función processImagePart
        threads.emplace_back(processImagePart, ref(image), startRow, endRow);

        // Actualizar los índices para el siguiente hilo
        startRow = endRow;
        endRow += rowsPerThread;
    }

    // Esperar a que todos los hilos terminen
    for (auto &thread : threads)
    {
        thread.join();
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

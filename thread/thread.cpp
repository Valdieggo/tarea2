#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>
#include <chrono>

using namespace cv;
using namespace std;
using namespace chrono;

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
    // Verificar si se proporciona la ruta de la imagen y el número de hilos como argumentos
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <path_to_image> <num_threads>" << endl;
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

    // Número de hilos a utilizar (obtenido de la línea de comandos)
    const int numThreads = stoi(argv[2]);

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

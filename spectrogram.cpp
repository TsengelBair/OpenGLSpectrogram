#include "spectrogram.h"

Spectrogram::Spectrogram(QWidget *parent)
    : QOpenGLWidget(parent), currentY(0)
{
    srand(time(nullptr));
    connect(&timer, &QTimer::timeout, this, &Spectrogram::generateData);
    timer.start(100);
}

void Spectrogram::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void Spectrogram::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h); // на все окно

    // Явно указываю, что работаю с 2D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // чтобы изменения не накладывались друг на друга
}

void Spectrogram::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int width = this->width(); // Текущая ширина виджета для последюущей нормализаци

    glBegin(GL_POINTS);
    for (const auto& pixel : pixels) {
        // Используем pixel.z для красного канала, остальные каналы случайные
        float red = pixel.z;
        float green = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float blue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        glColor3f(red, green, blue);

        float normalizedX = pixel.x * width;
        glVertex2f(normalizedX, pixel.y);
    }
    glEnd();
}

void Spectrogram::generateData()
{
    int width = this->width();
    int height = this->height();

    // когда данные заполнили весь экран, начинаем отрисовку заново сверху
    if (currentY >= height) currentY = 0;

    for (int i = 0; i < 500; ++i) {
        Pixel pixel;

        pixel.x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        pixel.y = static_cast<float>(currentY);

        // Интенсивность для красного канала
        pixel.z = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

        pixels.push_back(pixel);
    }

    currentY += 5;
    update(); // обновление виджета для перерисовки
}

Spectrogram::~Spectrogram()
{
}



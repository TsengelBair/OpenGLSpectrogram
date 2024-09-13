#ifndef SPECTROGRAM_H
#define SPECTROGRAM_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>

struct Pixel{
    float x;
    float y;
    float z;
};

class Spectrogram : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Spectrogram(QWidget *parent = nullptr);
    ~Spectrogram();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private slots:
    void generateData();

private:
    QVector<Pixel>pixels;
    float currentY;
    QTimer timer;
};
#endif // SPECTROGRAM_H

// ======================================
// 3D-Computergrafik
// moodle.hpi3d.de
// ======================================
// 
// Sommersemester 2015 - Aufgabenblatt 1
//                     - Aufgabe 1,2,3
//
//
//
// ======================================

#include "exercise123.h"

//
// std
//
#include <math.h>

//
// Qt
//
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QtMath>
#include <QDebug>

using namespace Qt;

//[-------------------------------------------------------]
//[ Helper functions                                      ]
//[-------------------------------------------------------]
// Get pixel at position
QColor Exercise123::getPixel(const QImage &image, int x, int y)
{
    return QColor(image.pixel(qBound(0, x, image.width()-1), qBound(0, y, image.height() - 1)));
}

// clamp color components to [0.0, 1.0]
void Exercise123::clampColor(float &r, float &g, float &b)
{
    r = qBound(0.0f, r, 1.0f);
    g = qBound(0.0f, g, 1.0f);
    b = qBound(0.0f, b, 1.0f);
}

// return grayscale
float Exercise123::getGrayColor(const QColor &color)
{
    //////////////////////////////////////////////////
    // Aufgabe 1 (grayscale)
    //////////////////////////////////////////////////
    float gray = color.redF()*0.299 + color.greenF()*0.587 + color.blueF()*0.114;

    return gray;
}

// return grayscale
QColor Exercise123::getInvertColor(const QColor &color)
{
    //////////////////////////////////////////////////
    // Aufgabe 1 (invert color)
    //////////////////////////////////////////////////
    QColor invert = QColor(255-color.red(), 255-color.green(), 255-color.blue());

    return invert;
}

//[-------------------------------------------------------]
//[ Filter functions                                      ]
//[-------------------------------------------------------]

QColor Exercise123::getSharpenColor(const QImage &image, int x, int y)
{
    //////////////////////////////////////////////////
    // Aufgabe 2
    //////////////////////////////////////////////////
    ///	...	 ... ... ... ...
    ///	...	|_1_|_2_|_3_|...
    ///	...	|_4_|_5_|_6_|...	<- 3x3 filter components
    ///	...	|_7_|_8_|_9_|...
    ///	...	 ... ... ... ...

    //////////////////////////////////////////////////////////////////////////
    // TODO: Define filter kernel as Laplace-Operator
    //////////////////////////////////////////////////////////////////////////

    int kernel[] = {-1, -1, -1, -1, 9, -1, -1, -1, -1};

    float r = 0;
    float g = 0;
    float b = 0;
    QColor pixel;
    int i =0;

    //////////////////////////////////////////////////
    // TODO: Aufgabe 2a
    //////////////////////////////////////////////////

    // Apply kernel

    for (int yy= y-1; yy <= y+1; yy++)
    {
        for (int xx= x-1; xx <= x+1; xx++)
        {
            pixel = getPixel(image,xx,yy);
            r += (pixel.red() / 255.0) * kernel[i];
            g += (pixel.green() / 255.0) * kernel[i];
            b += (pixel.blue() / 255.0) * kernel[i];
            i++;
        }
    }

    clampColor(r, g, b);

    return QColor::fromRgbF(r, g, b);
}

QColor Exercise123::getGaussColor(const QImage &image, int x, int y)
{
    //////////////////////////////////////////////////
    // Aufgabe 2
    //////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    // TODO: Define filter kernel as Gauss-Operator
    //////////////////////////////////////////////////////////////////////////

    int kernel[] = {1, 2, 1, 2, 4, 2, 1, 2, 1};

    float r = 0.0;
    float g = 0.0;
    float b = 0.0;
    QColor pixel;
    int i = 0;
    int sum=0;
    for(int s=0; s<(sizeof(kernel)/sizeof(*kernel));s++){
       sum=sum+kernel[s];
    }
    // Apply kernel

    //////////////////////////////////////////////////
    // TODO: Aufgabe 2b
    //////////////////////////////////////////////////

    for (int yy= y-1; yy <= y+1; yy++)
    {
        for (int xx= x-1; xx <= x+1; xx++)
        {
            pixel = getPixel(image,xx,yy);
            r += (pixel.red() / 255.0) * kernel[i];
            g += (pixel.green() / 255.0) * kernel[i];
            b += (pixel.blue() / 255.0) * kernel[i];
            i++;
        }
    }
    r=r/sum;
    g=g/sum;
    b=b/sum;
    clampColor(r, g, b);

    return QColor::fromRgbF(r, g, b);
}

QColor Exercise123::getSobelColor(const QImage &image, int x, int y)
{
    //////////////////////////////////////////////////
    // Aufgabe 2
    //////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    // TODO: Define filter kernels as Sobel Operators for both directions
    //////////////////////////////////////////////////////////////////////////
    int kernelY[] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
    int kernelX[] = {1, 0, -1, 2, 0, -2, 1, 0, -1};
    int i = 0;
    int sumx=0;
    for(int s=0; s<(sizeof(kernelX)/sizeof(*kernelX));s++){
       sumx=sumx+kernelX[s];
    }
    int sumy=0;
    for(int s=0; s<(sizeof(kernelY)/sizeof(*kernelY));s++){
       sumy=sumy+kernelY[s];
    }
    QColor pixel;
    //////////////////////////////////////////////////
    // TODO: Aufgabe 2c
    //////////////////////////////////////////////////

    // apply kernel, use getGrayColor()!
    float c = 0.0f;
    float g = 0.0f;
    for (int yy= y-1; yy <= y+1; yy++)
    {
        for (int xx= x-1; xx <= x+1; xx++)
        {
            pixel = getPixel(image,xx,yy);
            c+= getGrayColor(pixel)*kernelX[i];
            g+= getGrayColor(pixel)*kernelY[i];
            i++;

        }
    }
    c = sqrt(c*c+g*g);
    c = qBound(0.0f, c, 1.0f);

    return QColor::fromRgbF(c, c, c);
}

QColor Exercise123::getMeanColorDynamicSize(const QImage &image, int x, int y, int kernelSize)
{
    //////////////////////////////////////////////////
    // Aufgabe 2
    //////////////////////////////////////////////////

    float r = 0.0;
    float g = 0.0;
    float b = 0.0;
    QColor pixel;

    //////////////////////////////////////////////////
    // TODO: Aufgabe 2d
    //////////////////////////////////////////////////

    for (int yy= y-(sqrt((float)kernelSize)-2); yy <= y+(sqrt((float)kernelSize)-2); yy++)
    {
        for (int xx= x-(sqrt((float)kernelSize)-2); xx <= x+(sqrt((float)kernelSize)-2); xx++)
        {
            pixel = getPixel(image,xx,yy);
            r += (pixel.red() / 255.0);
            g += (pixel.green() / 255.0);
            b += (pixel.blue() / 255.0);
        }
    }

    // TODO: normalize
    r=r/kernelSize;
    g=g/kernelSize;
    b=b/kernelSize;

    clampColor(r, g, b);

    return QColor::fromRgbF(r, g, b);
}

//getDitheringColor can work directly on image - use it
QColor Exercise123::getDitheringColor(QImage &image, int x, int y)
{
    //////////////////////////////////////////////////
    // Aufgabe 3
    //////////////////////////////////////////////////
    float newGray;
    QColor newGrayColor;

    float oldpixel = getGrayColor(getPixel(image, x, y));

    //quantize pixel

    float newpixel = round(oldpixel);
    float quantError = oldpixel - newpixel;

    //Dithering by Floyd-Steinberg
    if(x<1023){
        newGray = getGrayColor(image.pixel(x+1, y))+quantError*7/16;
        newGray = qBound(0.0f, newGray, 1.0f);
        newGrayColor = QColor::fromRgbF(newGray, newGray, newGray);
        image.setPixel(x+1, y, newGrayColor.rgb());
    }

    if(x>0 && y < 644) {
        newGray = getGrayColor(image.pixel(x-1, y+1))+quantError*3/16;
        newGray = qBound(0.0f, newGray, 1.0f);
        newGrayColor = QColor::fromRgbF(newGray, newGray, newGray);
        image.setPixel(x-1, y+1, newGrayColor.rgb());
    }

    if(y < 644) {
        newGray = getGrayColor(image.pixel(x, y+1))+quantError*5/16;
        newGray = qBound(0.0f, newGray, 1.0f);
        newGrayColor = QColor::fromRgbF(newGray, newGray, newGray);
        image.setPixel(x, y+1, newGrayColor.rgb());
    }

    if(x<1023 && y < 644) {
        newGray = getGrayColor(image.pixel(x+1, y+1))+quantError*1/16;
        newGray = qBound(0.0f, newGray, 1.0f);
        newGrayColor = QColor::fromRgbF(newGray, newGray, newGray);
        image.setPixel(x+1, y+1, newGrayColor.rgb());
    }

    newpixel = qBound(0.0f, newpixel, 1.0f);

    return QColor::fromRgbF(newpixel, newpixel, newpixel);
}

Exercise123::Exercise123(Filter_Type type, QWidget *parent) :
    ImageView(parent),
    m_type(type)
{
    // load image
    const QImage image("image1.png");
    QImage filterImage(image);

    if(type == ORIGINAL)
    {
        this->setImage(image);
    }
    else
    {
        // filter image
        for(int y = 0; y < image.height(); ++y)
        {
            for(int x = 0; x < image.width(); ++x)
            {
                QColor filteredColor;

                // choose filter
                if(type == LAPLACE)
                {
                    filteredColor = getSharpenColor(image, x, y);
                }
                else if(type == GAUSS)
                {
                    filteredColor = getGaussColor(image, x, y);
                }
                else if(type == SOBEL)
                {
                    filteredColor = getSobelColor(image, x, y);
                }
                else if(type == MEANFILTER)
                {
                    filteredColor = getMeanColorDynamicSize(image, x, y, 5);
                }
                else if(type == GRAYSCALE)
                {
                    float luminance = getGrayColor(getPixel(image, x, y));
                    filteredColor = QColor::fromRgbF(luminance, luminance, luminance);
                }
                else if(type == INVERT)
                {
                    filteredColor = getInvertColor(getPixel(image, x, y));
                }
                else if(type == DITHERED)
                {
                    filteredColor = getDitheringColor(filterImage, x, y);
                }
                else
                {
                    // ORIGINAL -> do nothing
                }

                // draw pixel
                filterImage.setPixel(x,y,filteredColor.rgb());
            }
        }

        this->setImage(filterImage);
        this->zoomOut();
    }
}

Exercise123::~Exercise123()
{
}

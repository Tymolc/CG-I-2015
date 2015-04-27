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

    //TODO: Implement grayscale function

    return gray;
}

// return grayscale
QColor Exercise123::getInvertColor(const QColor &color)
{
    //////////////////////////////////////////////////
    // Aufgabe 1 (invert color)
    //////////////////////////////////////////////////
    QColor invert = QColor(255-color.red(), 255-color.green(), 255-color.blue());

    //TODO: Implement invert color function

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

    int kernel[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

    float r = 0;
    float g = 0;
    float b = 0;
    QColor pixel;

    //////////////////////////////////////////////////
    // TODO: Aufgabe 2a
    //////////////////////////////////////////////////

    // Apply kernel
    /*
    for (int yy=-1; yy <= 1; yy++)
    {
        for (int xx=-1; xx <= 1; xx++)
        {
            pixel = getPixel(...);
            r += ...
            g += ...
            b += ...
        }
    }
    */

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

    int kernel[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

    float r = 0.0;
    float g = 0.0;
    float b = 0.0;
    
    // Apply kernel

    //////////////////////////////////////////////////
    // TODO: Aufgabe 2b
    //////////////////////////////////////////////////

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
    int kernelX[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    int kernelY[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

    //////////////////////////////////////////////////
    // TODO: Aufgabe 2c
    //////////////////////////////////////////////////

    // apply kernel, use getGrayColor()!

    float c = 0.0f;

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
    QColor color;

    //////////////////////////////////////////////////
    // TODO: Aufgabe 2d
    //////////////////////////////////////////////////

    // Apply kernel
    /*
    float sum = 0.0;
    for (int yy=-(int)kernelSize; yy <= (int)kernelSize; yy++)
    {
        for (int xx=-(int)kernelSize; xx <= (int)kernelSize; xx++)
        {
            //
        }
    }
    */

    // TODO: normalize

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

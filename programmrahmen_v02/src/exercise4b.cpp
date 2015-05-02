// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
// 
// Sommersemester 2015 - Aufgabenblatt 1
//                     - Aufgabe 4b
//
// Matrikel-Nr. 1: 770496
// Matrikel-Nr. 2: 771103
// ======================================

#include "exercise4b.h"
#include "stable.h"

//
// std
//
#include <math.h>

//
// Qt
//
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QPainter>

using namespace Qt;

//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
QImage images[13]; //used to store itterations so it doesn't have to calculate them every time (the slowdown was very annoying)
const bool fasterRender = true; //for the true mandelbrot experience change this to false
const float maxAbsSquare = 4.0f;
const int maxIterations  = 100;

//[-------------------------------------------------------]
//[ Helper functions                                      ]
//[-------------------------------------------------------]
namespace exercise4b
{

int computeIterations(float cx, float cy)
{
    float absSquare = 0;
    int iterationCount = 0;

    float x = 0, y = 0;

    while(x*x+y*y<maxAbsSquare && iterationCount < maxIterations) {
        float xtemp = x*x - y*y + cx;
        y = 2*x*y + cy;
        x = xtemp;
        iterationCount++;
    }

    return iterationCount;
}

QColor chooseColor(int value, int maxValue)
{
	float p = (float)value/maxValue;
	int i = (int)(299 * std::min(std::max(p, 0.0f), 1.0f));
	int k = i / 60;
	float m = 1.0f * (i % 60) / 59.0f;
	switch (k)
	{
		case 0: return QColor(255, m*255, 0);
		case 1: return QColor((1-m)*255, 255, 0);
		case 2: return QColor(0, 255, m);
		case 3: return QColor(m*255, (1-m)*255, 255);
		case 4: return QColor((1-m)*255, 0, 255);
	}

	return QColor(0, 0, 0);
}

}

using namespace exercise4b;

Exercise4b::Exercise4b(QWidget *parent) :
    ImageView(parent),
    m_currentLevel(0),
    m_currentDir(1),
    m_timer(NULL)
{
    // Render mandelbrot set (initially)
    if(fasterRender){
        QImage tmp(800,600,QImage::Format_RGB16);
        images[0] = tmp;
    }

    renderMandelbrot();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(500);
}

Exercise4b::~Exercise4b()
{
    // Destroy timer
    delete m_timer;
}

void Exercise4b::renderMandelbrot()
{
    // Create image
    int width = 800, height = 600;
    QPixmap mandelbrot(width, height);
    QPainter painter(&mandelbrot);
    painter.setPen(Qt::NoPen); //to avoid having a black picture in high itterations

    // Draw image using a quadtree
    drawRecursive(painter, 0, 0, width, height, m_currentLevel);

    // Update image
    this->setImage(mandelbrot.toImage());
}

/**
*  @brief
*    Draw function recursively by using a quadtree-method
*/
void Exercise4b::drawRecursive(QPainter &painter, int x, int y, int w, int h, int level)
{
    //////////////////////////////////////////////////////////////////////////
    // TODO: Render Mandelbrot recursively for current level m_currentLevel
    //////////////////////////////////////////////////////////////////////////

    float scaleX = 3.0f, scaleY = 3.0f;
    float cx = ((float)(x + w/2 - 600) / 800) * scaleX;
    float cy = ((float)(y + h/2 - 250) / 600) * scaleY;

    if(level == 0) {
        QColor color = chooseColor(computeIterations(cx, cy), maxIterations);
        painter.setBrush(color);

        if(fasterRender){
            for(int i = 0; i < w; i++) {
                for(int j = 0; j < h; j++) {
                    if(x+i < 800 && y + j < 600)
                        images[m_currentLevel].setPixel(x+i, y+j, color.rgb());
                }
            }
        }

        painter.drawRect(x, y, w, h);
    }
    //if level != 0, split every area into 4 subareas
    else {
        drawRecursive(painter, x    , y    , w/2, h/2, level-1);
        drawRecursive(painter, x    , y+h/2, w/2, h/2+1, level-1);
        drawRecursive(painter, x+w/2, y    , w/2+1, h/2, level-1);
        drawRecursive(painter, x+w/2, y+h/2, w/2+1, h/2+1, level-1);
    }
}

void Exercise4b::onTimer()
{
    // Render mandelbrot with current level
    m_currentLevel += m_currentDir;

    if(m_currentLevel >= 12 || m_currentLevel <= 0){
        m_currentDir *= -1;
    }

    if(fasterRender){
        if(images[m_currentLevel].isNull()) {
            QImage tmp(800, 600, QImage::Format_RGB16);
            images[m_currentLevel] = tmp;
            renderMandelbrot();
        }
        else
            this->setImage(images[m_currentLevel]);
    }

    else
        renderMandelbrot();
}

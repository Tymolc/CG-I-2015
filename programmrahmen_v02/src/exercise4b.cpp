// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
// 
// Sommersemester 2015 - Aufgabenblatt 1
//                     - Aufgabe 4b
//
//
//
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
    m_currentDir(1), //hopefully dir doesn't mean directory
    m_timer(NULL)
{
    // Render mandelbrot set (initially)
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
    painter.setPen(Qt::NoPen);

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
    // TODO: Render Mandelbrot recursively for current level m_level
    //////////////////////////////////////////////////////////////////////////

    float scaleX = 3.0f, scaleY = 3.0f;
    float cx = ((float)(x + w/2 - 600) / 800) * scaleX;
    float cy = ((float)(y + h/2 - 250) / 600) * scaleY;

    if(level == 0) {
        painter.setBrush(chooseColor(computeIterations(cx, cy), maxIterations));
        painter.drawRect(x, y, w, h);
    }
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
    if(m_currentLevel > 12)
        m_currentDir = -1;
    else if(m_currentLevel < 1)
        m_currentDir = 1;
    renderMandelbrot();
}

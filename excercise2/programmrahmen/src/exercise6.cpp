// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2015 - Aufgabenblatt 2
//                     - Aufgabe 6
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: 771103
// Matr.-Nr: 770496
//
// ======================================

#include "exercise6.h"

#include <Qt>
#include <QTimer>
#include <iostream>

Exercise6::Exercise6()
    : Painter()
    , m_tessellationDepth(0)
    , m_update(false)
    , m_timer(0)
{
    // Create timer
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout(void)), this, SLOT(onTimer(void)));

    // Hinweis: Zum Debuggen kann setSingleShot(true) gesetzt werden, um nur 1x tessellate() aufzurufen
    m_timer->setSingleShot(false);
    m_timer->start(1000);
}

Exercise6::~Exercise6()
{
    // Destroy timer
    delete m_timer;
}

bool Exercise6::initialize()
{
    if(!Painter::initialize())
        return false;

    m_triangles.push_back(Triangle(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f));
    m_triangles.push_back(Triangle(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f));

    m_currentBuffer = &m_triangles;

    m_vao.bind();
    transferGeometryToGPU();
    m_vao.release();

    return true;
}

void Exercise6::transferGeometryToGPU()
{    
    m_vertices.bind();
    m_vertices.allocate(m_currentBuffer->data(), Triangle::memorySize() * m_currentBuffer->size());
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
}

void Exercise6::tessellate(const Triangle &triangle, std::vector<Triangle> &triangleBuffer)
{
    triangleBuffer.push_back(Triangle(triangle.x0, triangle.y0, (triangle.x0 + triangle.x1)/2, (triangle.y0 + triangle.y1)/2, (triangle.x0 + triangle.x2)/2, (triangle.y0 + triangle.y2)/2));
    triangleBuffer.push_back(Triangle((triangle.x0 + triangle.x1)/2, (triangle.y0 + triangle.y1)/2, triangle.x1, triangle.y1, (triangle.x1 + triangle.x2)/2, (triangle.y1 + triangle.y2)/2));
    triangleBuffer.push_back(Triangle((triangle.x1 + triangle.x2)/2, (triangle.y1 + triangle.y2)/2, triangle.x2, triangle.y2, (triangle.x2 + triangle.x0)/2, (triangle.y2 + triangle.y0)/2));
    triangleBuffer.push_back(Triangle((triangle.x0 + triangle.x1)/2, (triangle.y0 + triangle.y1)/2, (triangle.x1 + triangle.x2)/2, (triangle.y1 + triangle.y2)/2, (triangle.x0 + triangle.x2)/2, (triangle.y0 + triangle.y2)/2));
}

void Exercise6::render()
{
    drawTriangles(0, m_currentBuffer->size());
}

void Exercise6::drawTriangles(int start, int count)
{
    m_vao.bind();

    if(m_update)
    {
        transferGeometryToGPU();
        m_update = false;
    }
    glDrawArrays(GL_TRIANGLES, start * 3, count * 3);

    m_vao.release();
}

void Exercise6::onTimer()
{
    if(m_tessellationDepth == 0)
    {
        m_currentBuffer = &m_triangles;
        m_helperBuffer = &m_trianglesRefined;
    }

    for(int i = 0; i < m_currentBuffer->size(); i++)
        tessellate((*m_currentBuffer)[i], (*m_helperBuffer));

    std::vector<Triangle>* tmp = m_currentBuffer;
    m_currentBuffer = m_helperBuffer;
    m_helperBuffer = tmp;
    m_helperBuffer->clear();

    m_update = true;

    // Count tesselation depth from 0 to 8 and restart
    ++m_tessellationDepth;

    if(m_tessellationDepth >= 8 )
    {
        m_tessellationDepth = 0;

        m_triangles.clear();
        m_trianglesRefined.clear();
        m_triangles.push_back(Triangle(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f));
        m_triangles.push_back(Triangle(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f));

        m_update = true;
    }
}

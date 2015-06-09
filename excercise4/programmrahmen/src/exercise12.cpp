// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2015 - Aufgabenblatt 4
//                     - Aufgabe 12
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: 771103
// Matr.-Nr: 770496
//
// ======================================

#include <QKeyEvent>
#include <QMatrix4x4>
#include <QMatrix3x3>
#include <QOpenGLShaderProgram>

#include "util/camera.h"

#include <glm/vec3.hpp>
#include <glm/trigonometric.hpp>
#include <glm/geometric.hpp>

#include "exercise12.h"

Exercise12::Exercise12()
{
    m_cubeTransform.scale(0.5f);
}

Exercise12::~Exercise12()
{
}

QMatrix4x4 Exercise12::rotateClockwise(int frame)
{
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 12
    // Apply correct transformations (rotate, translate, scale) with respect to the current frame
    /////////////////////////////////////////////////////////////////////////////////////////////////

    QMatrix4x4 transform;

    //we need 4 180° turns = 720 frames
    frame = frame%720;
    float angle;

    transform.setToIdentity();

    switch((int)(frame/180)){
        case 0:{ //top-right edge
            //angle in radians
            angle = ((float)((frame+45)/360.0f)*(2.0f*M_PI));
            //translate in a circular motion
            transform.translate(0.5f-cos(angle)/sqrt(2), 0.5f+sin(angle)/sqrt(2), 0.0f);
            //rotate around z-axis
            transform.rotate(frame, 0, 0, -1);
            break;
        }
        case 1: {//bottom-right edge
            angle = ((float)(frame+135)/360.0f*(2.0f*M_PI));
            transform.translate(0.5f+cos(angle)/sqrt(2), -0.5f-sin(angle)/sqrt(2), 0.0f);
            transform.rotate(frame, 0, 0, -1);
            break;
        }
        case 2: {//bottom-left edge
            angle = ((float)(frame+225)/360.0f*(2.0f*M_PI));
            transform.translate(-0.5f-cos(angle)/sqrt(2), -0.5f+sin(angle)/sqrt(2), 0.0f);
            transform.rotate(frame, 0, 0, -1);
            break;
        }
        case 3: {//top-left edge
            angle = ((float)(frame+315)/360.0f*(2.0f*M_PI));
            transform.translate(-0.5f+cos(angle)/sqrt(2), 0.5f-sin(angle)/sqrt(2), 0.0f);
            transform.rotate(frame, 0, 0, -1);
            break;
        }
    }
    return transform;
}

const QString Exercise12::hints() const
{
	return QString("Press [SPACE] to pause or resume animation.");
}

bool Exercise12::initialize()
{
    AbstractExercise::initialize();

    m_program.reset(createBasicShaderProgram("data/cube12.vert", "data/cube12.frag"));
    m_program->bind();

    m_cube.initialize(*m_program);

    glClearColor(0.6, 0.6, 0.6, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

	return true;
}

void Exercise12::render()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    m_program->setUniformValue("lightsource", QVector3D(0.0, 10.0, 0.0));
    m_program->setUniformValue("viewprojection", camera()->viewProjection());

    m_program->setUniformValue("transform", m_cubeTransform);
    m_program->setUniformValue("normalMatrix", (camera()->view() * m_cubeTransform).normalMatrix());
    m_program->setUniformValue("color", QVector4D(1.0, 0.0, 0.0, 1.0));

    m_cube.draw(*this);

    m_program->setUniformValue("transform", rotateClockwise(m_frame) * m_cubeTransform);
    m_program->setUniformValue("normalMatrix", (camera()->view() * rotateClockwise(m_frame) * m_cubeTransform).normalMatrix());
    m_program->setUniformValue("color", QVector4D(1.0, 1.0, 0.0, 1.0));

    m_cube.draw(*this);
}

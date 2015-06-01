// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2015 - Aufgabenblatt 4
//                     - Aufgabe 13
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: xxxxx
// Matr.-Nr: xxxxx
//
// ======================================

#include <QDebug>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

#include <glm/gtc/constants.hpp>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include "util/camera.h"

#include "exercise13.h"

namespace 
{
    const QString TEXTURE_FILENAME = "data/luxo.png";
}

Exercise13::Exercise13()
: m_textureID(-1)
, m_sphere(3)
{
    m_sphereScale.scale(0.3);
}

Exercise13::~Exercise13()
{
	if (m_textureID != -1)
        glDeleteTextures(1, &m_textureID);
}

QMatrix4x4 Exercise13::applyBallTransformation(const int frame)
{
    static const float fX = 0.01f;
    static const int numFramesPerAnimation = static_cast<int>(4.0f / fX);

    static const float r = 0.3f;
    static const float d = 0.3f * r;
    static const float z = 0.0f;

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 13
    // - Calculate correct translation, scaling and rotation matrices with respect to the current frame
    // - The sphere's environment is defined as follows:
    //              start at    x = -2.0 and y = 0.8
    //              left  cliff x = -0.9
    //              bottom at   y = -1.05;
    //              right cliff x = +0.9 and y = 0.4
    //              end at      x = +2.0
    // - Apply matrices in the correct order, using matrix multiplication
    /////////////////////////////////////////////////////////////////////////////////////////////////

    //get x-value depending on frame between -2.0 and +2.0
    float x = (float)(frame % numFramesPerAnimation)/(float)numFramesPerAnimation*4.0f-2.0f;

    //get y-value depending on different states
    float y;
    if(x < -0.9f)   //left plateau
        y = 0.8f;
    else if(x < 0.1f)   //reaching the left cliff
        y = -(1.85 + r) * pow(x + 0.9f, 2) + 0.8f;
    else if(x < 0.9f) //ascending after hitting the bottom
        y = -(1.45f + r) * pow(x/0.8f - 0.9f/0.8f, 2) + 0.4f;
    else //right plateau
        y = 0.4f;

    const QMatrix4x4 translate(1, 0, 0, x, 0, 1, 0, y+r, 0, 0, 1, z, 0, 0, 0, 1);

    float angle = x/r;
    const QMatrix4x4 rotate(cos(angle), sin(angle), 0, 0, -sin(angle), cos(angle), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

    QMatrix4x4 scale(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    if(y < -1.05f){
      scale.scale(1, 3.033*y + 4.185, 1);
    }

    return translate * scale * rotate;

    //return QMatrix4x4();
}

void Exercise13::drawEnvironment()
{
    m_program0->bind();
    m_program0->setUniformValue("lightsource", QVector3D(0.0, 10.0, 0.0));
    m_program0->setUniformValue("viewprojection", camera()->viewProjection());

    // Draw big cubes

    m_program0->setUniformValue("color", QVector4D(0.8, 0.8, 0.8, 1.0));

    QMatrix4x4 transform;
    transform.translate(-4.9f, -1.201f, 0.0f);
    transform.scale(4.f, 2.0f,  4.0f);

    m_program0->setUniformValue("transform", transform);
    m_program0->setUniformValue("normalMatrix", (camera()->view() * transform).normalMatrix());

    m_cube.draw(*this);


    transform.setToIdentity();
    transform.translate(4.9f, -1.401f, 0.0f);
    transform.scale(4.f, 1.8f, 4.0f);

    m_program0->setUniformValue("transform", transform);
    m_program0->setUniformValue("normalMatrix", (camera()->view() * transform).normalMatrix());

    m_cube.draw(*this);


    transform.setToIdentity();
    transform.translate(0.0f, -3.0501f, 0.0f);
    transform.scale(1.0f, 2.0f,  4.0f);

    m_program0->setUniformValue("transform", transform);
    m_program0->setUniformValue("normalMatrix", (camera()->view() * transform).normalMatrix());

    m_cube.draw(*this);


    // Draw trail

    m_program0->setUniformValue("color", QVector4D(0.9, 0.9, 0.9, 1.0));

    transform.setToIdentity();
    transform.translate(-4.9f, 0.8f, 0.0f);
    transform.scale(4.f, 0.0f, 0.2f);

    m_program0->setUniformValue("transform", transform);
    m_program0->setUniformValue("normalMatrix", (camera()->view() * transform).normalMatrix());

    m_cube.draw(*this);


    transform.setToIdentity();
    transform.translate(4.9f, 0.4f, 0.0f);
    transform.scale(4.f, 0.0f, 0.2f);

    m_program0->setUniformValue("transform", transform);
    m_program0->setUniformValue("normalMatrix", (camera()->view() * transform).normalMatrix());

    m_cube.draw(*this);

    transform.setToIdentity();
    transform.translate(0.0f, -1.05f, 0.0f);
    transform.scale(1.0f, 0.0f,  0.2f);

    m_program0->setUniformValue("transform", transform);
    m_program0->setUniformValue("normalMatrix", (camera()->view() * transform).normalMatrix());

    m_cube.draw(*this);
}

void Exercise13::render()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    drawEnvironment();

	glBindTexture(GL_TEXTURE_2D, m_textureID);
    glActiveTexture(GL_TEXTURE0);

    QMatrix4x4 transform = applyBallTransformation(m_frame) * m_sphereScale;

    m_program1->bind();
    m_program1->setUniformValue("lightsource", QVector3D(0.0, 10.0, 0.0));
    m_program1->setUniformValue("viewprojection", camera()->viewProjection());

    m_program1->setUniformValue("transform", transform);
    m_program1->setUniformValue("normalMatrix", (camera()->view() * transform).normalMatrix());
    m_program1->setUniformValue("diffuse", 0);

    m_sphere.draw(*this);
}

bool Exercise13::initialize()
{
    AbstractExercise::initialize();

    m_textureID = getOrCreateTexture(TEXTURE_FILENAME);


    m_program0.reset(createBasicShaderProgram("data/cube13.vert", "data/cube13.frag"));

    m_cube.initialize(*m_program0);

    m_program1.reset(createBasicShaderProgram("data/sphere.vert", "data/sphere.frag"));

    m_sphere.initialize(*m_program1);

    glClearColor(0.6, 0.6, 0.6, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    return true;
}

const QString Exercise13::hints() const
{
    return QString("Press [SPACE] to pause or resume animation.");
}

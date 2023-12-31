/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#ifndef QT_NO_OPENGL

#include "private/glwidget_p.h"
#include "private/glxyseriesdata_p.h"
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLBuffer>

//#define QDEBUG_TRACE_GL_FPS
#ifdef QDEBUG_TRACE_GL_FPS
#  include <QElapsedTimer>
#endif

QT_CHARTS_BEGIN_NAMESPACE

GLWidget::GLWidget(GLXYSeriesDataManager *xyDataManager, QWidget *parent)
    : QOpenGLWidget(parent),
      m_program(0),
      m_shaderAttribLoc(-1),
      m_colorUniformLoc(-1),
      m_minUniformLoc(-1),
      m_deltaUniformLoc(-1),
      m_pointSizeUniformLoc(-1),
      m_xyDataManager(xyDataManager)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_AlwaysStackOnTop);
    setAttribute(Qt::WA_TransparentForMouseEvents);

    QSurfaceFormat surfaceFormat;
    surfaceFormat.setDepthBufferSize(0);
    surfaceFormat.setStencilBufferSize(0);
    surfaceFormat.setRedBufferSize(8);
    surfaceFormat.setGreenBufferSize(8);
    surfaceFormat.setBlueBufferSize(8);
    surfaceFormat.setAlphaBufferSize(8);
    surfaceFormat.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    surfaceFormat.setRenderableType(QSurfaceFormat::DefaultRenderableType);
    setFormat(surfaceFormat);

    connect(xyDataManager, &GLXYSeriesDataManager::seriesRemoved,
            this, &GLWidget::cleanXYSeriesResources);
}

GLWidget::~GLWidget()
{
    cleanup();
}

void GLWidget::cleanup()
{
    makeCurrent();

    delete m_program;
    m_program = 0;

    foreach (QOpenGLBuffer *buffer, m_seriesBufferMap.values())
        delete buffer;
    m_seriesBufferMap.clear();

    doneCurrent();
}

void GLWidget::cleanXYSeriesResources(const QXYSeries *series)
{
    makeCurrent();
    if (series) {
        delete m_seriesBufferMap.take(series);
    } else {
        // Null series means all series were removed
        foreach (QOpenGLBuffer *buffer, m_seriesBufferMap.values())
            delete buffer;
        m_seriesBufferMap.clear();
    }
    doneCurrent();
}

static const char *vertexSource =
        "attribute highp vec2 points;\n"
        "uniform highp vec2 min;\n"
        "uniform highp vec2 delta;\n"
        "uniform highp float pointSize;\n"
        "void main() {\n"
        "  vec2 normalPoint = vec2(-1, -1) + ((points - min) / delta);\n"
        "  gl_Position = vec4(normalPoint, 0, 1);\n"
        "  gl_PointSize = pointSize;\n"
        "}";
static const char *fragmentSource =
        "uniform highp vec3 color;\n"
        "void main() {\n"
        "  gl_FragColor = vec4(color,1);\n"
        "}\n";

void GLWidget::initializeGL()
{
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);

    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 0);

    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentSource);
    m_program->bindAttributeLocation("points", 0);
    m_program->link();

    m_program->bind();
    m_colorUniformLoc = m_program->uniformLocation("color");
    m_minUniformLoc = m_program->uniformLocation("min");
    m_deltaUniformLoc = m_program->uniformLocation("delta");
    m_pointSizeUniformLoc = m_program->uniformLocation("pointSize");


    // Create a vertex array object. In OpenGL ES 2.0 and OpenGL 2.x
    // implementations this is optional and support may not be present
    // at all. Nonetheless the below code works in all cases and makes
    // sure there is a VAO when one is needed.
    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    glEnableVertexAttribArray(0);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);

#if !defined(QT_OPENGL_ES_2)
    if (!QOpenGLContext::currentContext()->isOpenGLES()) {
        // Make it possible to change point primitive size and use textures with them in
        // the shaders. These are implicitly enabled in ES2.
        glEnable(GL_PROGRAM_POINT_SIZE);
    }
#endif

    m_program->release();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
    m_program->bind();

    GLXYDataMapIterator i(m_xyDataManager->dataMap());
    while (i.hasNext()) {
        i.next();
        QOpenGLBuffer *vbo = m_seriesBufferMap.value(i.key());
        GLXYSeriesData *data = i.value();

        if (data->visible) {
            m_program->setUniformValue(m_colorUniformLoc, data->color);
            m_program->setUniformValue(m_minUniformLoc, data->min);
            m_program->setUniformValue(m_deltaUniformLoc, data->delta);

            if (!vbo) {
                vbo = new QOpenGLBuffer;
                m_seriesBufferMap.insert(i.key(), vbo);
                vbo->create();
            }
            vbo->bind();
            if (data->dirty) {
                vbo->allocate(data->array.constData(), data->array.count() * sizeof(GLfloat));
                data->dirty = false;
            }

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
            if (data->type == QAbstractSeries::SeriesTypeLine) {
                glLineWidth(data->width);
                glDrawArrays(GL_LINE_STRIP, 0, data->array.size() / 2);
            } else { // Scatter
                m_program->setUniformValue(m_pointSizeUniformLoc, data->width);
                glDrawArrays(GL_POINTS, 0, data->array.size() / 2);
            }
            vbo->release();
        }
    }

#ifdef QDEBUG_TRACE_GL_FPS
    static QElapsedTimer stopWatch;
    static int frameCount = -1;
    if (frameCount == -1) {
        stopWatch.start();
        frameCount = 0;
    }
    frameCount++;
    int elapsed = stopWatch.elapsed();
    if (elapsed >= 1000) {
        elapsed = stopWatch.restart();
        qreal fps = qreal(0.1 * int(10000.0 * (qreal(frameCount) / qreal(elapsed))));
        qDebug() << "FPS:" << fps;
        frameCount = 0;
    }
#endif

    m_program->release();
}

void GLWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w)
    Q_UNUSED(h)
}

QT_CHARTS_END_NAMESPACE

#endif

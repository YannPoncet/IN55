#include "mainwidget.h"


MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    geometries(0),
    texture(0),
    angularSpeed(0),
    userTranslation(0,0,0)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(this->addLabel("Global size :"));
    layout->addWidget(this->addSlider(parameters.globalSizeFactor, 0.1, 2));

    layout->addWidget(this->addLabel("Curvature variance :"));
    layout->addWidget(this->addSlider(parameters.curvatureVariance, 0.008, 0.5));

    layout->addWidget(this->addLabel("Radius at base :"));
    layout->addWidget(this->addSlider(parameters.radiusAtBaseFactor, 1, 4));

    layout->addWidget(this->addLabel("Stem height part :"));
    layout->addWidget(this->addSlider(parameters.stemHeightPart, 0.1, 0.9));

    layout->addWidget(this->addLabel("Perlin power :"));
    layout->addWidget(this->addSlider(parameters.capGlobalPerlinPower, 0.10, 2));

    layout->addWidget(this->addLabel("Holes density :"));
    layout->addWidget(this->addSlider(parameters.holesDensityFactor, 0.10, 2));

    QPushButton *submitButton = new QPushButton("Regenerate \n a morel", this);
    submitButton->setFixedSize(100,50);
    QObject::connect(submitButton, SIGNAL(clicked()), this, SLOT(redrawMorel()));
    layout->addWidget(submitButton,0,Qt::AlignTop);


    // Global checkboxes
    QGroupBox* horizontalGroupBox2 = new QGroupBox(tr("Bezier - System - Lights - Soil:"));
    horizontalGroupBox2->setFixedSize(200,60);
    layout->addWidget(horizontalGroupBox2);
    QHBoxLayout *groupBoxLayout2 = new QHBoxLayout;
    horizontalGroupBox2->setLayout(groupBoxLayout2);

    addGlobalBox(showBezier, groupBoxLayout2);
    addGlobalBox(showSystem, groupBoxLayout2);
    addGlobalBox(showLights, groupBoxLayout2);
    addGlobalBox(showSoil, groupBoxLayout2);


    // Lights checkboxes
    QGroupBox* horizontalGroupBox = new QGroupBox(tr("Enable/disable the lights:"));
    horizontalGroupBox->setFixedSize(200,60);
    layout->addWidget(horizontalGroupBox);
    QHBoxLayout *groupBoxLayout = new QHBoxLayout;
    horizontalGroupBox->setLayout(groupBoxLayout);
    for (int i=0; i<lightsEnabled.size(); i++) {
        QCheckBox* c = new QCheckBox(this);
        if(lightsEnabled[i]) {
            c->setCheckState(Qt::Checked);
        }
        QObject::connect(c, SIGNAL(clicked(bool)), this, SLOT(setLight(bool)));
        c->setFixedSize(15,15);
        groupBoxLayout->addWidget(c);
        this->lightBoxes.append(c);
    }

    this->setLayout(layout);
}


void MainWidget::addGlobalBox(bool state, QLayout* layout) {
    QCheckBox* c = new QCheckBox(this);
    c->setFixedSize(15,15);
    if(state) {
        c->setCheckState(Qt::Checked);
    }
    QObject::connect(c, SIGNAL(clicked(bool)), this, SLOT(redrawElements(bool)));
    this->globalsBoxes.append(c);
    layout->addWidget(c);
}


void MainWidget::redrawElements(bool state) {
    QObject* c = sender();
    int checkBoxId = -1;
    for (int i=0; i<this->globalsBoxes.size(); i++) {
        if(this->globalsBoxes[i] == c) {
            checkBoxId = i;
        }
    }
    switch (checkBoxId) {
        case 0:
            showBezier = state;
        break;
        case 1:
            showSystem = state;
        break;
        case 2:
            showLights = state;
        break;
        case 3:
            showSoil = state;
        break;
    }
    //this->geometries->drawGeometry(&program);
    update();
}


void MainWidget::setLight(bool state) {
    QObject* c = sender();
    for (int i=0; i<this->lightBoxes.size(); i++) {
        if(this->lightBoxes[i] == c) {
            lightsEnabled[i] = state;
        }
    }
    update();
}


QLabel* MainWidget::addLabel(QString text) {
    QLabel *label = new QLabel(this);
    label->setText(text);
    label->setFixedSize(100,20);
    return label;
}


QSlider* MainWidget::addSlider(double value, double min, double max) {
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setFocusPolicy(Qt::StrongFocus);
    slider->setSingleStep(1);
    slider->setFixedSize(100,20);

    slider->setValue(100*abs(value-min)/abs(max-min));

    SliderParameters p = {min, max, value, slider};
    this->sliders.append(p);
    return slider;
}


void MainWidget::redrawMorel(){
    for(auto&& s: this->sliders) {
        double sval = s.slider->value()/100.0;
        s.value = s.min+sval*abs(s.max-s.min);
    }

    parameters.globalSizeFactor = this->sliders[0].value;
    parameters.curvatureVariance = this->sliders[1].value;
    parameters.radiusAtBaseFactor = this->sliders[2].value;
    parameters.stemHeightPart = this->sliders[3].value;
    parameters.capGlobalPerlinPower = this->sliders[4].value;
    parameters.holesDensityFactor = this->sliders[5].value;

    this->geometries->createAndBindMorels();
    this->geometries->drawMorels(&program);
    update();
}


MainWidget::~MainWidget() {
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete geometries;
    doneCurrent();
}


void MainWidget::mousePressEvent(QMouseEvent *e) {
    previousMousePosition = QVector2D(0.0, 0.0);
}


void MainWidget::wheelEvent(QWheelEvent *e){
    if(e->delta() < 0){
        userTranslation.setZ(userTranslation.z()-0.5f);
    }
    else{
        userTranslation.setZ(userTranslation.z()+0.5f);
    }
    update();
}


void MainWidget::mouseMoveEvent(QMouseEvent *e) {
    QVector2D prev = previousMousePosition;
    QVector2D diff = QVector2D(e->localPos()) - previousMousePosition;
    previousMousePosition = QVector2D(e->localPos());
    if(prev == QVector2D(0.0f,0.0f)) return;

    // Rotation axis is perpendicular to the mouse position difference
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Update rotation
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();
    rotation = QQuaternion::fromAxisAndAngle(rotationAxis, acc*50) * rotation;
    update();
}


void MainWidget::keyPressEvent(QKeyEvent *event) {
    //Right left
    if(event->key() == Qt::Key_D) {
        isDPressed = true;
    }
    if(event->key() == Qt::Key_Q) {
        isQPressed = true;
    }

    //Up down
    if(event->key() == Qt::Key_Z) {
        isZPressed = true;
    }
    if(event->key() == Qt::Key_S) {
        isSPressed = true;
    }
}


void MainWidget::keyReleaseEvent(QKeyEvent *event) {
    //Right left
    if(event->key() == Qt::Key_D) {
        isDPressed = false;
    }
    if(event->key() == Qt::Key_Q) {
        isQPressed = false;
    }

    //Up down
    if(event->key() == Qt::Key_Z) {
        isZPressed = false;
    }
    if(event->key() == Qt::Key_S) {
        isSPressed = false;
    }
}


void MainWidget::timerEvent(QTimerEvent *)
{
    bool needToUpdate = false;
    if(isQPressed) {
        this->userTranslation.setX(this->userTranslation.x()+0.1);
        needToUpdate = true;
    }
    if(isDPressed) {
        this->userTranslation.setX(this->userTranslation.x()-0.1);
        needToUpdate = true;
    }
    if(isZPressed) {
        this->userTranslation.setY(this->userTranslation.y()-0.1);
        needToUpdate = true;
    }
    if(isSPressed) {
        this->userTranslation.setY(this->userTranslation.y()+0.1);
        needToUpdate = true;
    }
    if(needToUpdate) {
        update();
    }
}


void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(120.0/255.0, 120.0/255.0, 120.0/255.0, 1);

    initShaders();
    initTextures();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    //glEnable(GL_CULL_FACE);
    // glCullFace(GL_FRONT);

    // Enable point size manipulation
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_POINT_SMOOTH);

    geometries = new GeometryEngine;

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}


void MainWidget::initShaders() {
    QString vshader;
    QString fshader;
    vshader = ":/vshader.glsl";
    fshader = ":/fshader.glsl";

    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, vshader))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, fshader))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}


void MainWidget::initTextures()
{
    // Load soil.png image
    texture = new QOpenGLTexture(QImage(":/soil.png").mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}


void MainWidget::resizeGL(int w, int h) {
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 500, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}


void MainWidget::paintGL() {
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();
    // Use texture unit 0 which contains soil.png
    program.setUniformValue("texture", 0);

    drawCube();
}


void MainWidget::drawCube() {
    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0, 0, -10);
    matrix.translate(userTranslation);
    matrix.rotate(rotation);
    matrix.scale(1.5,1.5,1.5);
    program.setUniformValue("mv", matrix);
    QMatrix4x4 normal = (matrix.inverted()).transposed();
    program.setUniformValue("nm", normal);
    // Set modelview-projection matrix
    program.setUniformValue("mvp", projection * matrix);

    //lights positions
    int nbLights = 5;
    QVector3D LightPositions[nbLights];
    LightPositions[0] = QVector3D(matrix*QVector4D(-3.0f, 2.0f, 3.0f,1.0f));
    LightPositions[1] = QVector3D(matrix*QVector4D(3.0f, 2.0f, 3.0f,1.0f));
    LightPositions[2] = QVector3D(matrix*QVector4D(3.0f, -2.0f, 3.0f,1.0f));
    LightPositions[3] = QVector3D(matrix*QVector4D(-3.0f, -2.0f, 3.0f,1.0f));
    LightPositions[4] = QVector3D(0.0f,0.0f,0.0f); //Camera light

    int nbLightsEnabled = 0;
    int IndexLightsEnabled[nbLights];
    for(int i=0; i<lightsEnabled.size(); i++){
        if(lightsEnabled[i]){
            IndexLightsEnabled[nbLightsEnabled] = i;
            nbLightsEnabled++;
        }
    }

    QVector3D LEP[nbLightsEnabled];
    for(int i=0; i<nbLightsEnabled; i++){
        LEP[i] = LightPositions[IndexLightsEnabled[i]];
    }

    program.setUniformValue("nbLights", nbLightsEnabled);
    program.setUniformValueArray("LightPositions", LEP, nbLightsEnabled);


    // Draw cube geometry
    geometries->drawGeometry(&program);
}


/* The C++ File which has the classes and methods to Implement
* Upper arm of right hand
* Lower arm of the right hand
* Upper arm of left hand
* Lower arm of left hand
* The torso
* The Head
*/

#include "UpperBody.h"


//Head
Head::Head(ref_ptr<MatrixTransform> transform) : BodyCredential(transform)
    {
    shape->setShape(new Sphere(Vec3(0.0f, 0.0f, 0.4f), 0.85f));
    }


Head::~Head(void)
    {

    }

bool Head::handle( const GUIEventAdapter & eventAdapter, GUIActionAdapter & actionAdapter )
    {

    switch ( eventAdapter.getEventType() )
	{
	
    case osgGA::GUIEventAdapter::KEYDOWN:
	switch ( eventAdapter.getKey() )
	    {
	case '1':
	    shape->setColor(Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	    break;
	case '0': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8':
	case '9': 
	    shape->setColor(Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	    break;

	    }
	}

    return false;
    }

//Torso
Torso::Torso(ref_ptr<MatrixTransform> transform) : BodyCredential(transform)
    {
    shape->setShape(new Cylinder(Vec3(0.0f, 0.0f, -0.25f), 1.0f, 3.5f));
    }

Torso::~Torso(void)
    {
    }

bool Torso::handle( const GUIEventAdapter & eventAdapter, GUIActionAdapter & actionAdapter )
    {
    Matrix m;
    switch ( eventAdapter.getEventType() )
	{
	
    case osgGA::GUIEventAdapter::KEYDOWN:
	switch ( eventAdapter.getKey() )
	    {
	    
	case 'a':
	    m = Matrix::translate(-0.1f, 0.0f, 0.0f);
	    transform->setMatrix(m*transform->getMatrix());
	    break;
	case 'd':
	     m = Matrix::translate(0.1f, 0.0f, 0.0f);
	    transform->setMatrix(m*transform->getMatrix());
	    break;
	case 'w':
	     m = Matrix::translate(0.0f, 0.1f, 0.0f);
	    transform->setMatrix(m*transform->getMatrix());
	    break;
	case 's':
	     m = Matrix::translate(0.0f, -0.10f, 0.f);
	    transform->setMatrix(m*transform->getMatrix());
	    break;
	case '0':
	    shape->setColor(Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	    break;
	case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8':
	case '9': 
	    shape->setColor(Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	    break;
	    }
	}
    return false;
    }

// Upper left arm
LeftHandTop::LeftHandTop(ref_ptr<MatrixTransform> transform) : BodyCredential(transform)
    {
    shape->setShape(new Capsule(Vec3(0.0f, 0.0f, -0.7f), 0.5f, 1.4f));
    rotationAngleX = rotationAngleY = 0.0f;
    rotationAxisY = Vec3(0.0f, 2.0f, 0.0f);
    rotationAxisX = Vec3(-1.0f, 0.0f, 0.0f);
    }

bool LeftHandTop::handle(const GUIEventAdapter & eventAdapter, GUIActionAdapter & actionAdapter)
    {
    Matrix matrixX, matrixY;
    switch ( eventAdapter.getEventType() )
	{
    case osgGA::GUIEventAdapter::KEYDOWN:
	switch ( eventAdapter.getKey() )
	    {

	case GUIEventAdapter::KEY_Up:
	    if(isSelected)
		{
		if(rotationAngleX < DegreesToRadians(90.0)){
		    rotationAngleX += PI/180;
		    matrixX = Matrix::rotate(Quat(PI/180, rotationAxisX));
		    transform->setMatrix(matrixX*matrixY*transform->getMatrix());
		    }
		}
	    break;

	case GUIEventAdapter::KEY_Down:
	    if(isSelected)
		{
		if(rotationAngleX > DegreesToRadians(0.0f)){
		    rotationAngleX -= PI/180;
		    matrixX = Matrix::rotate(Quat(-PI/180, rotationAxisX));
		    transform->setMatrix(matrixX*matrixY*transform->getMatrix());
		    }
		}
	    break;

	    case GUIEventAdapter::KEY_Left:
	    if(isSelected)
		{
		if(rotationAngleY < DegreesToRadians(45.0))
		    {
		    rotationAngleY += PI/180;
		    matrixY = Matrix::rotate(Quat(PI/180, rotationAxisY));
		    transform->setMatrix(matrixY*matrixX*transform->getMatrix());
		    }
		}
	    break;

	case GUIEventAdapter::KEY_Right:
	    if(isSelected)
		{
		if(rotationAngleY > DegreesToRadians(0.0))
		    {
		    rotationAngleY -= PI/180;
		    matrixY = Matrix::rotate(Quat(-PI/180, rotationAxisY));
		    transform->setMatrix(matrixY*matrixX*transform->getMatrix());
		    }
		}
	    break;

	case '2':
	    shape->setColor(Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	    isSelected = true;
	    break;
	case '1': case '9': case '3': case '4':
	case '5': case '6': case '7': case '8':
	case '0': 
	    shape->setColor(Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	    isSelected = false;
	    break;

	    }
	}
    return false;
    }

LeftHandTop::~LeftHandTop(void)
    {

    }

//Lower left arm
LeftHandBottom::LeftHandBottom(ref_ptr<MatrixTransform> transform) : BodyCredential(transform)
    {
    shape->setShape(new Capsule(Vec3(0.0f, 0.0f, -0.7f), 0.42f, 1.4f));
    rotationVector = Vec3(-1.0f, 0.0f, 0.0f);
    rotationAngle = 0.0f;
    }

bool LeftHandBottom::handle(const GUIEventAdapter & eventAdapter, GUIActionAdapter & actionAdapter)
    {
    Matrix m;
    switch ( eventAdapter.getEventType() )
	{
	
    case osgGA::GUIEventAdapter::KEYDOWN:
	switch ( eventAdapter.getKey() )
	    {

	    case GUIEventAdapter::KEY_Up:
	    if(isSelected)
		{
		if(rotationAngle < DegreesToRadians(80.0)){
		    rotationAngle += PI/180;
		    m = Matrix::rotate(PI/180, rotationVector);
		    transform->setMatrix(m*transform->getMatrix());
		    }
		}
	    break;

	case GUIEventAdapter::KEY_Down:
	    if(isSelected)
		{
		if(rotationAngle > DegreesToRadians(0.0f)){
		    rotationAngle -= PI/180;
		    m = Matrix::rotate(-PI/180, rotationVector);
		    transform->setMatrix(m*transform->getMatrix());
		    }
		}
	    break;
	case '4':
	    shape->setColor(Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	    isSelected = true;
	    break;
	case '1': case '2': case '3': case '9':
	case '5': case '6': case '7': case '8':
	case '0': 
	    shape->setColor(Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	    isSelected = false;
	    break;

	    }
	}
    return false;
    }


LeftHandBottom::~LeftHandBottom(void)
    {

    }

//Upper right arm
RightHandTop::RightHandTop(ref_ptr<MatrixTransform> transform) : BodyCredential(transform)
    {
    shape->setShape(new Capsule(Vec3(0.0f, 0.0f, -0.7f), 0.5f, 1.4f));
    rotationAngleX = rotationAngleY = 0.0f;
    rotationAxisY = Vec3(0.0f, -1.0f, 0.0f);
    rotationAxisX = Vec3(-1.0f, 0.0f, 0.0f);
    }

RightHandTop::~RightHandTop(void)
    {
    }

bool RightHandTop::handle(const GUIEventAdapter & eventAdapter, GUIActionAdapter & actionAdapter)
    {
    Matrix m;
    switch ( eventAdapter.getEventType() )
	{
    case osgGA::GUIEventAdapter::KEYDOWN:
	switch ( eventAdapter.getKey() )
	    {

	case GUIEventAdapter::KEY_Up:
	    if(isSelected)
		{
		if(rotationAngleX < DegreesToRadians(90.0))
		    {
		    rotationAngleX += PI/180;
		    m = Matrix::rotate(PI/180, rotationAxisX);
		    transform->setMatrix(m*transform->getMatrix());
		    }
		}
	    break;

	case GUIEventAdapter::KEY_Down:
	    if(isSelected)
		{
		if(rotationAngleX > DegreesToRadians(0.0f))
		    {
		    rotationAngleX -= PI/180;
		    m = Matrix::rotate(-PI/180, rotationAxisX);
		    transform->setMatrix(m*transform->getMatrix());
		    }
		}
	    break;

	case GUIEventAdapter::KEY_Right:
	    if(isSelected)
		{
		if(rotationAngleY < DegreesToRadians(45.0))
		    {
		    rotationAngleY += PI/180;
		    m = Matrix::rotate(PI/180, rotationAxisY);
		    transform->setMatrix(m*transform->getMatrix());
		    }
		}
	    break;

	case GUIEventAdapter::KEY_Left:
	    if(isSelected)
		{
		if(rotationAngleY > DegreesToRadians(0.0) && rotationAngleX > DegreesToRadians(0.0f))
		    {
		    rotationAngleY -= PI/180;
		    m = Matrix::rotate(-PI/180, rotationAxisY);
		    transform->setMatrix(m*transform->getMatrix());
		    }
		}
	    break;

	case '3':
	    shape->setColor(Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	    isSelected = true;
	    break;
	case '1': case '2': case '9': case '4':
	case '5': case '6': case '7': case '8':
	case '0': 
	    shape->setColor(Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	    isSelected = false;
	    break;

	    }
	}
    return false;
    }

//Lower right arm
RightHandBottom::RightHandBottom(ref_ptr<MatrixTransform> transform) : BodyCredential(transform)
    {
    shape->setShape(new Capsule(Vec3(0.0f, 0.0f, -0.7f), 0.42f, 1.4f));
    rotationVector = Vec3(-1.0f, 0.0f, 0.0f);
    rotationAngle = 0.0f;
    }

bool RightHandBottom::handle(const GUIEventAdapter & eventAdapter, GUIActionAdapter & actionAdapter)
    {
    Matrix m;
    switch ( eventAdapter.getEventType() )
	{
	
    case osgGA::GUIEventAdapter::KEYDOWN:
	switch ( eventAdapter.getKey() )
	    {

	case GUIEventAdapter::KEY_Up:
	    if(isSelected)
		{
		if(rotationAngle < DegreesToRadians(80.0)){
		    rotationAngle += PI/180;
		    m = Matrix::rotate(PI/180, rotationVector);
		    transform->setMatrix(m*transform->getMatrix());
		    }

		}
	    break;

	case GUIEventAdapter::KEY_Down:
	    if(isSelected)
		{
		if(rotationAngle > DegreesToRadians(0.0f)){
		    rotationAngle -= PI/180;
		    m = Matrix::rotate(-PI/180, rotationVector);
		    transform->setMatrix(m*transform->getMatrix());
		    }
		}
	    break;

	case '5':
	    shape->setColor(Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	    isSelected = true;
	    break;
	case '1': case '2': case '3': case '4':
	case '9': case '6': case '7': case '8':
	case '0': 
	    shape->setColor(Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	    isSelected = false;
	    break;

	    }
	}
    return false;
    }

RightHandBottom::~RightHandBottom(void)
    {
    }


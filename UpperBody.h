
/* The header File which has the classes and methods to Implement
* Upper arm of right hand
* Lower arm of the right hand
* Upper arm of left hand
* Lower arm of left hand
* The torso
* The Head
*/
#pragma once
#include "BodyCredential.h"

class Head : public BodyCredential
    {
    public:
	Head(ref_ptr<MatrixTransform> transform);
	virtual bool handle( const GUIEventAdapter & eventAdapter, GUIActionAdapter & actionAdapter );
	~Head(void);
    };

class Torso : public BodyCredential
    {
    public:
	Torso(ref_ptr<MatrixTransform> transform);
	virtual bool handle( const GUIEventAdapter & eventAdapter, GUIActionAdapter & actionAdapter );
	~Torso(void);
    };

class LeftHandTop : public BodyCredential
    {
    public:
	LeftHandTop(ref_ptr<MatrixTransform> transform);
	virtual bool handle(const GUIEventAdapter & eventAdapter, GUIActionAdapter & actionAdapter);
	~LeftHandTop(void);

    private:
	float rotationAngleX, rotationAngleY;
	Vec3 rotationAxisX, rotationAxisY;
    };

class LeftHandBottom :
    public BodyCredential
    {
    public:
	LeftHandBottom(ref_ptr<MatrixTransform> transform);
	virtual bool handle( const GUIEventAdapter & eventAdapter, GUIActionAdapter & actionAdapter );
	~LeftHandBottom(void);

    private:
	float rotationAngle;
	Vec3 rotationVector;
    };

class RightHandTop : public BodyCredential
    {
    public:
	RightHandTop(ref_ptr<MatrixTransform> transform);
	virtual bool handle( const GUIEventAdapter & eventAdapter, GUIActionAdapter & actionAdapter);
	~RightHandTop(void);

    private:
	float rotationAngleX, rotationAngleY;
	Vec3 rotationAxisX, rotationAxisY;
    };
class RightHandBottom :
    public BodyCredential
    {
    public:
	RightHandBottom(ref_ptr<MatrixTransform> transform);
	virtual bool handle( const GUIEventAdapter & eventAdapter, GUIActionAdapter & actionAdapter );
	~RightHandBottom(void);

    private:
	float rotationAngle;
	Vec3 rotationVector;
    };


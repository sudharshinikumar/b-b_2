#include "TrackedSphere.h"

#include <iostream>
using namespace std;
using namespace osgve;

TrackedSphere::TrackedSphere()
{
    sphereTransform = new PoseTransform();
	navTransform = new PoseTransform();
	trackingTransform = new PoseTransform();
 
	Group::addChild(navTransform);

    setUnitSphere(osg::Vec4(1.0,0.0,0.0,0.5));
    trackerData=NULL;
    objectOffset = osg::Vec3(0,0,0);
    orientation.makeRotate( osg::DegreesToRadians(270.0f), osg::Vec3d(0.0, 1.0, 0.0), 0, osg::Vec3d(1.0, 0.0, 0.0), osg::DegreesToRadians(90.0f), osg::Vec3d(0.0, 0.0, 1.0));
}

TrackedSphere::TrackedSphere(osg::Vec4 color)
{
    sphereTransform = new PoseTransform();
	navTransform = new PoseTransform();
	trackingTransform = new PoseTransform();
 
	Group::addChild(navTransform);

    setUnitSphere(color);
    trackerData=NULL;
    objectOffset = osg::Vec3(0,0,0);
    orientation.makeRotate( osg::DegreesToRadians(0.0f), osg::Vec3d(0.0, 1.0, 0.0), osg::DegreesToRadians(270.0f), osg::Vec3d(1.0, 0.0, 0.0), osg::DegreesToRadians(0.0f), osg::Vec3d(0.0, 0.0, 1.0));
}

void TrackedSphere::setUnitSphere(osg::Vec4 color)
{
    trackedSphere = new osg::Capsule (osg::Vec3(1.0f,0,0),-0.25, 2.5);
    trackedSphere ->setRotation(Quat(90*PI/180,Vec3(0,1,0)));
    trackedSphereDrawable = new osg::ShapeDrawable(trackedSphere);
    trackedSphereGeode = new osg::Geode();
    stateset = new osg::StateSet();
    osg::Depth* depth = new osg::Depth;

    trackedSphereGeode->addDrawable(trackedSphereDrawable);

    trackedSphereDrawable->setColor(color);

    stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
    stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
    depth->setWriteMask( true );
    stateset->setAttributeAndModes(depth, osg::StateAttribute::ON);
    stateset->setMode( GL_LIGHTING, osg::StateAttribute::OFF );

    trackedSphereGeode->setStateSet(stateset);
    
    sphereTransform->addChild(trackedSphereGeode);
	navTransform->addChild(trackingTransform);
    trackingTransform->addChild(sphereTransform);
 }

bool TrackedSphere::addChild( Node *child )
{
    return sphereTransform->addChild(child);
}

Vec3 TrackedSphere::getPosition()
{
    return sphereTransform->getPosition();
}

void TrackedSphere::setPosition(Vec3 p)
{
    sphereTransform->setPosition(p);
}

Quat TrackedSphere::getRotation()
{
    return  sphereTransform->getAttitude();
}

void TrackedSphere::setRotation(Quat rotation)
{
    sphereTransform->setAttitude(rotation);

}

void TrackedSphere::setTrackerData(TrackerData* _trackerData)
{
    trackerData = _trackerData;
}

void TrackedSphere::update()
{
    if(trackerData!=NULL)
    {
		setPosition(osg::Vec3d(trackerData->x, trackerData->y, trackerData->z) + objectOffset);
		setRotation(orientation * osg::Quat(trackerData->qx, trackerData->qy, trackerData->qz, trackerData->qw));
    }
}


void TrackedSphere::setTrackingTransform(const osg::Vec3 v)
{
    trackingTransform->setPosition(v);
}

void TrackedSphere::setTrackingAttitude(const osg::Quat q)
{
    trackingTransform->setAttitude(q);
}

void TrackedSphere::setNavTransformPosition(osg::Vec3d p)
{
    navTransform->setPosition(p);
}

void TrackedSphere::setNavTransformAttitude(osg::Quat orient)
{
    navTransform->setAttitude(orient);
}

void TrackedSphere::setScale(double _scale)
{
    scale = _scale;
}

double TrackedSphere::getRadius()
{
    return trackedSphere->getRadius();
}

void TrackedSphere::setObjectOffset(osg::Vec3 _offset)
{
    objectOffset = _offset; 
}


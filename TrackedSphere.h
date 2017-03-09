#ifndef OSGVE_TrackedSphere
#define OSGVE_TrackedSphere

#include <osgVirtualEnvironment/Export.h>
#include <osgVirtualEnvironment/Sound.h>
#include <osgVirtualEnvironment/PluginInterface.h>
#include <osgVirtualEnvironment/PoseTransform.h>

#include <osg/MatrixTransform>
#include <osg/PolygonMode>
#include <osg/ShapeDrawable>
#include <osg/Depth>
#include <osg/PositionAttitudeTransform>

#include <osgDB/ReadFile>
#include <osg/Texture2D>
#include <osg/Image>
using namespace osg;

#include <string>
using namespace std;


class OSGVE_EXPORT TrackedSphere: public Group
{
public:
    TrackedSphere(); // default color = red (0.5 alpha)
    TrackedSphere(osg::Vec4);

    virtual bool addChild( Node *child );

    void setTrackerData(osgve::TrackerData*);
    void update();


    void setPosition(Vec3);
    void setRotation(Quat);
    void setScale(double);
	
	void setTrackingTransform(const osg::Vec3);
    void setTrackingAttitude(const osg::Quat q);
    void setNavTransformPosition(osg::Vec3d);
    void setNavTransformAttitude(osg::Quat);

	osg::Vec3 getNavTransformPosition(){return navTransform->getPosition();};
    osg::Quat getNavTransformAttitude(){return navTransform->getAttitude();};
    osg::Vec3 getTrackingTransformPosition(){return trackingTransform->getPosition();};
    osg::Quat getTrackingTransformAttitude(){return trackingTransform->getAttitude();};

    void setObjectOffset(osg::Vec3);
 
    osg::Vec3 getPosition();
    osg::Quat getRotation();
 
    osgve::PoseTransform *sphereTransform;
    osgve::PoseTransform *navTransform;
    osgve::PoseTransform *trackingTransform;


    double getRadius();

private:
    void setUnitSphere(osg::Vec4);

    osg::Vec3 objectOffset;
    osg::Vec3 position;
    osg::Quat orientation;

    osgve::TrackerData *trackerData;

    osg::Capsule* trackedSphere;
    osg::ShapeDrawable* trackedSphereDrawable;
    osg::Geode* trackedSphereGeode;
    osg::StateSet* stateset;

    double scale;
};

#endif
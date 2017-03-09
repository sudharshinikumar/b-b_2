#include "TestEnvironment.h"

using namespace osg;

#include <osg/ShapeDrawable>
#include <osg/Texture2D>
#include <osg/Image>
#include <osgText/Text>
#include <osgText/Font>

using namespace osgve;
long double score = 0.0;
long double level = 1;
Vec3 centre[20];
osgText::Font *g_font;
VirtualObject *object1 =  new VirtualObject();
bool flag = false;
float timeBall = 0.0;
int i = 0, j = 0;
// constructor
TestEnvironment::TestEnvironment()
{
	//cube = new Cube(20.0);
	brick1 = new Brick();
	brick2 = new Brick();
	brick3 = new Brick();
	brick4 = new Brick();
	brick5 = new Brick();
	brick6 = new Brick();
	brick7 = new Brick();
	brick8 = new Brick();
	brick9 = new Brick();
	brick10 = new Brick();
	brick11 = new Brick();
	brick12 = new Brick();
	brick13 = new Brick();
	brick14 = new Brick();
	brick15 = new Brick();
	brick16 = new Brick();
	brick17 = new Brick();
	brick18 = new Brick();
	brick19 = new Brick();
	brick20 = new Brick();
	for(int itr = 0;itr<20;itr++)
		brick[itr] = new Brick();
	paddle = new TrackedSphere(osg::Vec4(1,0,0,1));
	//leftHand = new TrackedSphere(osg::Vec4(0,1,0,1));
	roofCube = new Cube(140.0,90.0,1.0);
    roofCube->setTexture("data/Images/roof_cement_Texture.jpg");

    leftCube = new Cube(1.0,90.0,60.0);
    leftCube->setTexture("data/Images/wall_texture.jpg");

    rightCube = new Cube(1.0,90.0,60.0);
    rightCube->setTexture("data/Images/wall_texture.jpg");

    backCube = new Cube(140.0,1.0,60.0);
    backCube->setTexture("data/Images/wall_texture.jpg");

    floorCube = new Cube(140.0,90.0,1.0);
    floorCube->setTexture("data/Images/Floor_Texture3.jpg");

    //paddle = new TrackedSphere();
    //root->addChild(objectGroup);
}

// setup environment function - executed once upon initializiation of environment
// anything not related to the scene graph should be set up here
void TestEnvironment::setup()
{
	if(pluginManager->getInputPlugin()->loaded())
	{
		InteractiveManipulator *cam = ((InteractiveManipulator*)camera.get());
		cam->setPanLeftButton(5);
		cam->setPanRightButton(6);
		cam->setMoveForwardButton(7);
		cam->setMoveBackButton(8);
		cam->setMoveLeftButton(9);
		cam->setMoveRightButton(10);
		callbackManager->registerCallback(new ButtonCallback<TestEnvironment>(this, &TestEnvironment::testCallback, 0, 11, 1.0)); // device 0, button 3, timeout 2.5 seconds 
	}

	callbackManager->registerCallback(new KeyboardCallback<TestEnvironment>(this, &TestEnvironment::testCallback, osgGA::GUIEventAdapter::KEYDOWN, 't')); // key down event, t key	
	
	callbackManager->registerCallback(new KeyboardCallback<TestEnvironment>(this, &TestEnvironment::normalCallback, osgGA::GUIEventAdapter::KEYDOWN, '1', 1.0)); 
	callbackManager->registerCallback(new KeyboardCallback<TestEnvironment>(this, &TestEnvironment::swapCallback, osgGA::GUIEventAdapter::KEYDOWN, '2', 1.0)); 
	callbackManager->registerCallback(new KeyboardCallback<TestEnvironment>(this, &TestEnvironment::leftCallback, osgGA::GUIEventAdapter::KEYDOWN, '3', 1.0)); 
	callbackManager->registerCallback(new KeyboardCallback<TestEnvironment>(this, &TestEnvironment::rightCallback, osgGA::GUIEventAdapter::KEYDOWN, '4', 1.0)); 

	InteractiveManipulator *cam = dynamic_cast<InteractiveManipulator*>(camera.get());
	
	//leftHand->setTrackerData(pluginManager->getTrackerPlugin()->getTrackerData(1));
	paddle->setTrackerData(pluginManager->getTrackerPlugin()->getTrackerData(3));
}

void SetWallPosition(osg::MatrixTransform* transform,Cube* wall,Vec3 pos)
{
    transform->setMatrix(osg::Matrix::translate(pos.x(),pos.y(),pos.z()));
    transform->addChild(wall);
}

void CreateText(osg::Geode* textGeode,string strtext,Vec3 textPos,string strFont,Vec4 color)
    {
    g_font = osgText::readFontFile(strFont);
    osg::MatrixTransform* textTransform = new osg::MatrixTransform;
    osg::Projection* projection = new osg::Projection;
    osgText::Text* text = new osgText::Text;
    textTransform->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    textTransform->addChild(projection);
    projection->setMatrix(osg::Matrix::ortho2D(0,1366,0,786));
    projection->addChild(textGeode);
    textGeode->addDrawable(text);
    text->setAxisAlignment(osgText::Text::SCREEN);
    text->setText(strtext);
    text->setPosition(osg::Vec3(textPos.x(),textPos.y(),textPos.z()));
    text->setColor(osg::Vec4(color.x(),color.y(),color.z(),color.w()));
    text->setCharacterSize(5);
    text->setFont(g_font);
    }

// create scene graph function - executed once upon initializiation of environment
void TestEnvironment::create()
{
	float xPos = -50.0;
	float yPos = 15.0;
	float zPos = 150.0f;

	float xCol = 0;
	float yCol = 1;
	float zCol = 0.5;
	
	osg::Geode* geode = new osg::Geode();
	ShapeDrawable* sd = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3d(1.0f, 0.0f, 0.0f), 3));
	sd->setColor(osg::Vec4(0.0f,1.0f,0.0f,1.0f));
	geode->addDrawable(sd);
	object1->setModel(geode);
	//for(float i = 0.0; i< 10.0; i+=0.5)
	object1->setPosition(osg::Vec3d(20.0, 155.0, 60.0));
	
	osg::MatrixTransform* leftWallTransform = new osg::MatrixTransform();
	osg::MatrixTransform* rightWallTransform = new osg::MatrixTransform();
	osg::MatrixTransform* backWallTransform = new osg::MatrixTransform();
	osg::MatrixTransform* roofWallTransform= new osg::MatrixTransform();
	osg::MatrixTransform*  floorTransform= new osg::MatrixTransform();

	//creating walls for room
      leftCube->setPosition(osg::Vec3(-55.0f,200.0f,0.0f));
    rightCube->setPosition(osg::Vec3(55.0f,200.0f,0.0f));
    backCube->setPosition(osg::Vec3(0.0f,270.0f,0.0f));
    roofCube->setPosition(osg::Vec3(0.0f,200.0f,30.0f));
    root->addChild(leftCube);
    root->addChild(rightCube);
    root->addChild(backCube);
    root->addChild(roofCube);
	//game texts
	osg::Geode* scoreTextGeode = new osg::Geode;
	CreateText(scoreTextGeode,"Score:",osg::Vec3(45.0f,140.0f,-42.0f),"fonts/dirtydoz.ttf",osg::Vec4(255.0f,255.0f,255.0f,1.0f));
	osg::Geode* levelTextGeode = new osg::Geode;
	CreateText(levelTextGeode,"Level:",osg::Vec3(-85.0f,140.0f,-42.0f),"fonts/dirtydoz.ttf",osg::Vec4(255.0f,255.0f,255.0f,1.0f));
	osg::Geode* gameTextGeode = new Geode;
	CreateText(gameTextGeode,"BRICK-BASH",osg::Vec3(-20.0f,140.0f,40.0f),"fonts/dirtydoz.ttf",osg::Vec4(255.0f,255.0f,255.0f,1.0f));

	/*brick1->DrawBricks(Vec3(xPos,zPos,yPos),Vec4(0,1,0.5,1));xPos += 12;
	brick2->DrawBricks(Vec3(xPos,zPos,yPos),Vec4(0.1,0.9,0.6,1));xPos += 12;
	brick3->DrawBricks(Vec3(xPos,zPos,yPos),Vec4(0.2,0.8,0.7,1));xPos += 12;
	brick4->DrawBricks(Vec3(xPos,zPos,yPos),Vec4(0.3,0.7,0.8,1));xPos += 12;
	brick5->DrawBricks(Vec3(xPos,zPos,yPos),Vec4(0.4,0.6,0.6,1));xPos += 12;
	brick6->DrawBricks(Vec3(xPos,zPos,yPos),Vec4(0.5,0.5,0.5,1));xPos += 12;
	brick7->DrawBricks(Vec3(xPos,zPos,yPos),Vec4(0.6,0.4,0.2,1));xPos += 12;
	brick8->DrawBricks(Vec3(xPos,zPos,yPos),Vec4(0.7,0.3,0.9,1));xPos += 12;
	brick9->DrawBricks(Vec3(xPos,zPos,yPos),Vec4(0.4,0.4,0.4,1));xPos += 12;
	brick10->DrawBricks(Vec3(xPos,zPos,yPos),Vec4(0.5,0.9,0.0,1));xPos += 12;

	yPos -= 4;
	xPos = -48;

	brick11->DrawBricks(Vec3(xPos,zPos,yPos),Vec4(0,1,0.5,1));xPos += 12;
	brick12->DrawBricks(Vec3(xPos,zPos,yPos),Vec4(0.1,0.9,0.6,1));xPos += 12;
	brick13->DrawBricks(Vec3(xPos,zPos,yPos),Vec4(0.2,0.8,0.7,1));xPos += 12;
	brick14->DrawBricks(Vec3(xPos,zPos,yPos),Vec4(0.3,0.7,0.8,1));xPos += 12;
	brick15->DrawBricks(Vec3(xPos,zPos,yPos),Vec4(0.4,0.6,0.6,1));xPos += 12;
	brick16->DrawBricks(Vec3(xPos,zPos,yPos),Vec4(0.5,0.5,0.5,1));xPos += 12;
	brick17->DrawBricks(Vec3(xPos,zPos,yPos),Vec4(0.6,0.4,0.2,1));xPos += 12;
	brick18->DrawBricks(Vec3(xPos,zPos,yPos),Vec4(0.7,0.3,0.9,1));xPos += 12;
	brick19->DrawBricks(Vec3(xPos,zPos,yPos),Vec4(0.4,0.4,0.4,1));xPos += 12;*/
	
	for(int itr = 0 ;itr<19;itr++)
	{
		brick[itr]->DrawBricks(Vec3(xPos,zPos,yPos),Vec4(xCol,yCol,zCol,1));
		xPos+=12;
		if(itr==9)
		{
			yPos-=4;
			xPos = -48;
			xCol = 0;
			yCol = 1;
		}
		xCol+=0.1;
		yCol-=0.1;
		if(itr%3 == 0) zCol +=0.2;
		else if(itr%5 == 0) zCol -=0.1;
	}
	root->addChild(scoreTextGeode);
	root->addChild(levelTextGeode);
	root->addChild(gameTextGeode);
	
	paddle->setPosition(osg::Vec3(-5,-5,0));
	//leftHand->setPosition(osg::Vec3(5,-5,0));

	for(int itr = 0;itr<19;itr++) root->addChild(brick[itr]);
	root->addChild(object1);
	root->addChild(paddle);
	//root->addChild(leftHand);
	
	viewer->setSceneData(root);
	
}

// update function - per frame updates occur here
void TestEnvironment::update()
{
	i++;
	timeBall = 1;
	//leftHand->update();
	paddle->update();
	    //rect = new osg::BoundingBox(sd->getBound());
	 Vec3 curPos = object1->getPosition();
	 Vec3 *newPos;
	//double angle = SetBallAngle(rand()%12);
	 
	 Vec3 roofPos = roofCube->getPosition();

	 if(!flag && curPos.z() <= 30)//roofPos.z())
	 {
		newPos = new Vec3(curPos.x(),curPos.y(),curPos.z()+ timeBall );
		if(curPos.z() == 30)
		{
			//newPos->x() += angle*PI/180;
			flag = true;
		}
	 }
	 else
	 {
		 newPos = new Vec3(curPos.x(),curPos.y(),curPos.z()- timeBall );
		 if(curPos.z() < 0) 
			 {
				 //newPos->x() += angle*PI/180;
				 flag = false;
			}
	 }
	 object1->setPosition(Vec3(newPos->x(),newPos->y(),newPos->z()));
	//if(i%50 == 0) root->removeChild(brick[j++]);

}

void TestEnvironment::testCallback()
{
	using namespace std;
	cout << "void TestEnvironment::testCallback()" << endl;
}
void TestEnvironment::normalCallback()
{
	displayManager->setStereoSetting(DisplayManager::NORMAL);
}

void TestEnvironment::swapCallback()
{
	displayManager->setStereoSetting(DisplayManager::SWAPPED);
}

void TestEnvironment::leftCallback()
{
	displayManager->setStereoSetting(DisplayManager::LEFT_ONLY);
}

void TestEnvironment::rightCallback()
{
	displayManager->setStereoSetting(DisplayManager::RIGHT_ONLY);
}


#include "Ogre.h"

using namespace Ogre;

int main()
{
	RenderWindow* window = 0;
	Viewport* viewport = 0;
	SceneManager* sceneManager = 0;
	SceneNode* rootNode = 0;
	Camera* camera = 0;

	float viewportWidth = 1.0f;
	float viewportHeight = 1.0f;

	Root* root = new Root();
	root->loadPlugin("RenderSystem_GL_d");
	if(!root->restoreConfig())
		root->showConfigDialog();
	root->initialise(true, "StealthMechanics");
	
	window = root->getAutoCreatedWindow();

	sceneManager = root->createSceneManager(SceneType::ST_INTERIOR, "DemoScene");
	rootNode = sceneManager->getRootSceneNode();
	camera = sceneManager->createCamera("MainCamera");
	rootNode->attachObject(camera);
	window->removeAllViewports();

	viewport = window->addViewport(camera);
	viewport->setAutoUpdated(true);
	viewport->setBackgroundColour(ColourValue(0.4f,0.4f,0.6f,0.4f));
	camera->setAspectRatio(static_cast<float>(viewport->getActualWidth()) / static_cast<float>(viewport->getActualHeight()));
	camera->setNearClipDistance(0.1f);
	camera->setFarClipDistance(3000.0f);
	window->setActive(true);
	root->clearEventTimes();
	sceneManager->setAmbientLight(Ogre::ColourValue(0.5f,0.5f,0.5f,0.5f));

	String assetFolder = "../assets/mesh";
	String toLoad = "Testbox.mesh";
	String resourceType = "FileSystem";
	String resourceGroupName = "AssetFolder";
	ResourceGroupManager& content = ResourceGroupManager::getSingleton();
	content.createResourceGroup(resourceGroupName);
	content.addResourceLocation(assetFolder, resourceType, resourceGroupName,false);
	content.addResourceLocation("../assets/material", resourceType, resourceGroupName,false);
	content.initialiseResourceGroup(resourceGroupName);
	content.loadResourceGroup(resourceGroupName);

	Entity* cube = sceneManager->createEntity(toLoad);
	SceneNode* node = rootNode->createChildSceneNode();
	node->attachObject(cube);
	node->setPosition(0.0f,0.0f,-10.0f);

	Plane* plane = new Plane(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane("Playfield", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
		*plane, 1500,1500,10,10, true, 1, 5.0f, 5.0f, Vector3::UNIT_Z);

	Entity* ground = sceneManager->createEntity("PlayfieldEntity", "Playfield");
	SceneNode* groundNode = rootNode->createChildSceneNode();
	groundNode->attachObject(ground);
	groundNode->setPosition(0,-10,-100);
	//ground->setMaterialName("NoMaterial", resourceGroupName);
	camera->lookAt(Vector3(0,-10.0f,-50.0f));

	Light* pointLight = sceneManager->createLight("pointlight");
	pointLight->setType(Light::LT_POINT);
	pointLight->setPosition(0,20,-20);
	pointLight->setDiffuseColour(0.8f,0.3f,0.7f);

	Ogre::Radian pitch;
	Ogre::Degree rotationEachFrame(0.02f);
	Ogre::Quaternion cubeRotation;
	while(!window->isClosed())
	{
		window->update();
		
		root->renderOneFrame();
		pitch += rotationEachFrame;
		cubeRotation.IDENTITY;
		cubeRotation.FromAngleAxis(pitch, Vector3::UNIT_X);
		node->setOrientation(node->convertWorldToLocalOrientation(cubeRotation));
		//groundNode->pitch(pitch, Node::TransformSpace::TS_LOCAL);
		
		WindowEventUtilities::messagePump();
	}



	
}
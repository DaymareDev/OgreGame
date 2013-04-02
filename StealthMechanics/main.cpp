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
	viewport->setBackgroundColour(ColourValue(0.0f,0.0f,0.0f,0.0f));
	camera->setAspectRatio(static_cast<float>(viewport->getActualWidth()) / static_cast<float>(viewport->getActualHeight()));
	camera->setNearClipDistance(0.1f);
	camera->setFarClipDistance(3000.0f);
	window->setActive(true);
	root->clearEventTimes();
	sceneManager->setAmbientLight(Ogre::ColourValue(0.8f,0.5f,0.5f,0.5f));

	String assetFolder = "../assets/mesh";
	String toLoad = "Testbox.mesh";
	String resourceType = "FileSystem";
	String resourceGroupName = "AssetFolder";
	ResourceGroupManager& content = ResourceGroupManager::getSingleton();
	content.createResourceGroup(resourceGroupName);
	content.addResourceLocation(assetFolder, resourceType, resourceGroupName,false);
	content.initialiseResourceGroup(resourceGroupName);
	content.loadResourceGroup(resourceGroupName);

	Entity* cube = sceneManager->createEntity(toLoad);
	SceneNode* node = rootNode->createChildSceneNode();
	node->attachObject(cube);
	node->setPosition(0.0f,0.0f,-200.0f);


	float pitch = 0.0f;
	while(!window->isClosed())
	{
		window->update();
		root->renderOneFrame();
		pitch+= 0.01f;
		node->pitch(Ogre::Radian(pitch));
		WindowEventUtilities::messagePump();
	}



	
}
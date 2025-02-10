#include "SceneManager.h"

SceneManager::SceneManager() : currentScene(Scene::Title) 
{
  
}

SceneManager::~SceneManager() { }

void SceneManager::SetScene(Scene scene) {
    currentScene = scene;
}

SceneManager::Scene SceneManager::GetCurrentScene() const {
    return currentScene;
}




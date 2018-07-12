//
//  ResourceManager.cpp
//  bird
//
//  Created by 汪依尘 on 6/14/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "ResourceManager.hpp"
#include "GameObject.hpp"
#include "Cube.hpp"
#include "Camera.hpp"
#include <iostream>
#include "Texture.hpp"
//#include <filesystem>
//
//namespace fs = std::filesystem;


const char* ResourceManager::TexturePath = "res/images/";

ResourceManager* ResourceManager::m_Instance = NULL;

GAMEOBJECT_GENERATORS ResourceManager::m_Generators = { std::vector<const char*>(), std::vector<std::function<GameObject*()> >() };

std::unordered_map<std::string, Texture* const> ResourceManager::m_Textures = std::unordered_map<std::string, Texture* const>();


ResourceManager* ResourceManager::GetInstance()
{
    if (m_Instance==NULL)
        m_Instance = new ResourceManager();
    return m_Instance;
}

void ResourceManager::Init()
{
    LoadGenerators();
    LoadMedia();
}

ResourceManager::~ResourceManager()
{
    if (m_Instance!=NULL)
        delete m_Instance;
}

ResourceManager::ResourceManager()
{
    // TODO: nothing here yet.
    Init();
}

void ResourceManager::LoadMedia()
{
    // TODO: load all media resources.
//    for (auto & p : fs::directory_iterator(ResourceManager::TexturePath))
//        std::cout << p << std::endl;
    const char* res_path1 = "res/images/kilua.jpg";
    const char* res_path2 = "res/images/dragonball.jpg";
    const char* res_path3 = "res/images/gon.jpg";

    ResourceManager::m_Textures.insert(std::make_pair(std::string(res_path1), new Texture(res_path1)));
    ResourceManager::m_Textures.insert(std::make_pair(std::string(res_path2), new Texture(res_path2)));
    ResourceManager::m_Textures.insert(std::make_pair(std::string(res_path3), new Texture(res_path3)));

//    ResourceManager::m_Textures[res_path1] = new Texture(res_path1);
//    ResourceManager::m_Textures[res_path3] = new Texture(res_path3);
//    ResourceManager::m_Textures[res_path2] = new Texture(res_path2);
}

void ResourceManager::LoadGenerators()
{
    Register<Cube>("Cube");
    Register<Camera>("Camera");
    // Waiting for more game objects...
    
//    Component::Register<MeshRenderer>("Mesh Renderer");
    // Waiting for more components...
    
}

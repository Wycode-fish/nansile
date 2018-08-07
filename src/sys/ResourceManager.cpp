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
#include "LuaScript.hpp"
#include "TextEditor.hpp"

//#include <filesystem>
//
//namespace fs = std::filesystem;


const char* ResourceManager::TexturePath = "res/images/";
const char* ResourceManager::ShaderPath = "src/gl/shaders/";

ResourceManager* ResourceManager::m_Instance = NULL;

GAMEOBJECT_GENERATORS ResourceManager::m_Generators = { std::vector<const char*>(), std::vector<std::function<GameObject*()> >() };

std::unordered_map<std::string, Texture* const> ResourceManager::m_Textures = std::unordered_map<std::string, Texture* const>();
std::unordered_map<std::string, LuaScript* const> ResourceManager::m_LuaScripts = std::unordered_map<std::string, LuaScript* const>();


ResourceManager* ResourceManager::GetInstance()
{
    if (m_Instance==NULL)
        m_Instance = new ResourceManager();
    return m_Instance;
}

void ResourceManager::Init()
{
    LoadGenerators();
    LoadScript();
    LoadMedia();
}

ResourceManager::~ResourceManager()
{
    for (auto pair: m_Textures)
    {
        if (pair.second != NULL)
            delete pair.second;
    }
    for (auto pair: m_LuaScripts)
    {
        if (pair.second != NULL)
            delete pair.second;
    }
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
    ResourceManager::m_Textures.insert(std::make_pair(std::string(TexturePath)+"kilua.jpg",
                                                      Texture::GetTexture("res/images/kilua.jpg")));
    
    ResourceManager::m_Textures.insert(std::make_pair(std::string(TexturePath)+"dragonball.jpg",
                                                      Texture::GetTexture("res/images/dragonball.jpg")));
    
    ResourceManager::m_Textures.insert(std::make_pair(std::string(TexturePath)+"gon.jpg",
                                                      Texture::GetTexture("res/images/gon.jpg")));
}

void ResourceManager::LoadScript()
{
    // TODO: load all script resources.
    
    // ---------- Behavior Scripts ----------
    ResourceManager::m_LuaScripts.insert(std::make_pair("src/game/script/SpinningCube.lua", new LuaScript(nullptr, "src/game/script/SpinningCube.lua", TextEditor::Str2ValuePtr(TextEditor::StripLuaFileName("src/game/script/SpinningCube.lua").c_str()))));
    
    // ---------- Resource Scripts ----------
    ResourceManager::m_LuaScripts.insert(std::make_pair("src/game/basic/script/info/mesh/Cube.lua", new LuaScript(nullptr, "src/game/basic/script/info/mesh/Cube.lua", "Mesh", RESOURCE_SCRIPT)));
    ResourceManager::m_LuaScripts.insert(std::make_pair("src/game/basic/script/info/mesh/SkyBox.lua", new LuaScript(nullptr, "src/game/basic/script/info/mesh/SkyBox.lua", "Mesh", RESOURCE_SCRIPT)));
}

void ResourceManager::LoadGenerators()
{
    Register<Cube>("Cube");
    Register<Camera>("Camera");
    // Waiting for more game objects...
    
//    Component::Register<MeshRenderer>("Mesh Renderer");
    // Waiting for more components...
    
}

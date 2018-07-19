//
//  ResourceManager.hpp
//  bird
//
//  Created by 汪依尘 on 6/14/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <stdio.h>
#include <functional>
#include <unordered_map>
#include <vector>
#include <utility>
#include <string>

class Texture;
class Shader;
class GameObject;
class LuaScript;


struct GAMEOBJECT_GENERATORS
{
    std::vector<const char*> names;
    std::vector<std::function<GameObject*()> > generators;
};


class ResourceManager
{
public:
    static const char* TexturePath;
    static const char* ShaderPath;
    
public:
    static ResourceManager* GetInstance();
    void Init();
    ~ResourceManager();
  
private:
    static std::unordered_map<std::string, Texture* const> m_Textures;
    static std::unordered_map<std::string, LuaScript* const> m_LuaScripts;
public:
    static inline GAMEOBJECT_GENERATORS GetGenerators() { return m_Generators; }
    static inline std::unordered_map<std::string, Texture* const> GetTextureResourceMap() { return m_Textures; }
    static inline std::unordered_map<std::string, LuaScript* const> GetLuaScriptResourceMap() { return m_LuaScripts; }

private:
//    static std::vector<std::pair<const char*, OBJ_GENERATOR> > m_Generators;
    static GAMEOBJECT_GENERATORS m_Generators;
private:
    ResourceManager();
    ResourceManager(ResourceManager& rm) = delete;
    ResourceManager& operator=(const ResourceManager rm) = delete;
    
    void LoadMedia();
    void LoadGenerators();
    void LoadScript();
    
public:
    template<typename T>
    void Register(const char* gameObjectName)
    {
        m_Generators.names.push_back(gameObjectName);
        m_Generators.generators.push_back([](){ return new T();});
    }
    
private:
    static ResourceManager* m_Instance;
    
};
#endif /* ResourceManager_hpp */

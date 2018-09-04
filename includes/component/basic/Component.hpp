//
//  Component.hpp
//  bird
//
//  Created by 汪依尘 on 6/16/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Component_hpp
#define Component_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

#define COMPONENT_MESH_RENDERER     0
#define COMPONENT_COLLIDER          1

class GameObject;
class Component;

struct COMPONENT_GENERATORS
{
    std::vector<const char*> names;
    std::vector<std::function<Component*()> > generators;
};

class Component
{
public:
    static      const char* const       AvailableComponents[];
    static      int                     AvailableComponentsCount;
    
public:
    static      inline     COMPONENT_GENERATORS   GetGenerators()  { return m_Generators;}
private:
    static      COMPONENT_GENERATORS                            m_Generators;
    static      unsigned int                                    m_GeneratorsSeqNo;
    static      std::unordered_map<const char*, unsigned int>   m_GeneratorIDMap;
    
public:
    Component(  std::string componentTag = "default"    );
    Component(  GameObject* gameObject  );
    Component(  GameObject* gameObject, const std::string& tag  );
    virtual     ~Component();
    virtual     void                    Update();
    virtual     void                    OnRender();
    
public:
    inline      void                    SetTag(const char* tag) { m_Tag = tag; }
    inline      std::string             GetTag()                { return m_Tag; }
    inline      const char*             GetTagCstr()    const   { return m_Tag.c_str(); }
    inline      GameObject*             GetGameObject()         { return m_GameObject; }
    
public:
    inline      void                    SetGameObject(GameObject* gameObject)         { m_GameObject = gameObject; }
//public:
//    template<typename T>
//    static void Register(const char* componentName)
//    {
//        m_Generators.names.push_back(componentName);
//        m_Generators.generators.push_back([](){ return new T();});
//        m_GeneratorIDMap[componentName] = m_GeneratorsSeqNo++;
//    }
    
private:
    GameObject*                         m_GameObject;
    std::string                         m_Tag;
};
#endif /* Component_hpp */

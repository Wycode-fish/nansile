//
//  Scene.hpp
//  bird
//
//  Created by 汪依尘 on 7/6/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <utility>

class GameObject;

class Scene
{
public:
    Scene();
    ~Scene();
    inline std::vector<GameObject*> GetGameObjects() const { return m_GameObjects; }
    inline std::unordered_map<const char*, unsigned int> GetCounter() const { return m_GameObjectCounter; }
//    inline std::vector<const char*> GetNames() { return m_ObjNames;}
public:
    void Render();
    void Update();
    
public:
    void AddGameObject(GameObject* gameObject);
    
public:
    inline void SetSelectedGameObject(const int& idx) { m_SelectedGameObject = m_GameObjects[idx]; }

private:
    std::vector<GameObject*> m_GameObjects;
//    std::vector<const char*> m_ObjNames;
    std::unordered_map<const char*, unsigned int> m_GameObjectCounter;
    
private:
    GameObject* m_SelectedGameObject;
};
#endif /* Scene_hpp */

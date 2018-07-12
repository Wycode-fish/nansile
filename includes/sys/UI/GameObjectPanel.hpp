//
//  GameObjectPanel.hpp
//  bird
//
//  Created by 汪依尘 on 7/11/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef GameObjectPanel_hpp
#define GameObjectPanel_hpp

#include <stdio.h>
#include "UI.hpp"
#include "GameObject.hpp"
#include <unordered_map>
#include <utility>
#include <functional>

namespace gui {
    
    //========= ComponentPanel ==========
    
    class ComponentPanel: public Gui
    {
    public:
        static inline std::unordered_map<std::string, std::function<ComponentPanel*(Component*)> > GetPanelGenerators() { return m_ComponentPanelGenerators; }
    public:
        template<typename T, typename C>
        static void Register(std::string componentName)
        {
            auto lambda = [](Component* component){ return dynamic_cast<ComponentPanel*>(new T( dynamic_cast<C*>(component) ) ); };
            m_ComponentPanelGenerators[componentName] = lambda;
        }
    private:
        static std::unordered_map<std::string, std::function<ComponentPanel*(Component*)> > m_ComponentPanelGenerators;
    public:
        virtual void OnRender() {}
        virtual void OnUpdate() {}
    public:
        virtual void BindComponent(Component* component) {}
    };
    
    
    
    //========= GameObjectPanel ==========
    
    class GameObjectPanel: public Gui
    {
    public:
        GameObjectPanel(GameObject* gameObject);
        ~GameObjectPanel();
    public:
        void OnRender();
        void OnUpdate();
    private:
        void m_OnRender_Transform();
    public:
        void BindGameObject(GameObject* gameObject);
        void LoadComponentPanels();
    public:
        inline GameObject* GetGameObject() const { return m_GameObject; }
    private:
        GameObject* m_GameObject;
        std::vector<ComponentPanel*> m_ComponentPanels;
    };
    
};
#endif /* GameObjectPanel_hpp */

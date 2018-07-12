//
//  ScenePanel.hpp
//  bird
//
//  Created by 汪依尘 on 7/10/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef ScenePanel_hpp
#define ScenePanel_hpp

#include <stdio.h>
#include "UI.hpp"
#include "Scene.hpp"

namespace gui {
    
    class GameObjectPanel;
    
    class ScenePanel : public Gui
    {
    public:
        ScenePanel(Scene* scene);
        ~ScenePanel();
    public:
        void OnRender();
        void OnUpdate();
    public:
        inline void BindScene(Scene*& scene) { m_Scene = scene; }
        
    private:
        Scene* m_Scene;
        GameObjectPanel* m_GameObjectPanel;
    private:
        int m_CurrSelected;
        int m_CurrToBeCreated;
    };
};

#endif /* ScenePanel_hpp */

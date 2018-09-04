//
//  MeshRendererPanel.hpp
//  bird
//
//  Created by 汪依尘 on 7/11/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef MeshRendererPanel_hpp
#define MeshRendererPanel_hpp

#include <stdio.h>
#include "GameObjectPanel.hpp"
#include "MeshRendererAssimp.hpp"
#include <vector>

namespace rl
{
    class Mesh;
}

namespace gui {
    
    class MeshEditor: public Gui
    {
    public:
        MeshEditor(rl::Mesh* mesh);
        ~MeshEditor();
    public:
        void OnRender();
        void OnUpdate();
        
    private:
        rl::Mesh* m_Mesh;
    private:
        int     m_CurrSelectedTexture;
//        bool    m_IsTextureActive;
    };
    
    
    class ModelEditor: public Gui
    {
    public:
        ModelEditor( rl::Model* model);
        ~ModelEditor();
    public:
        void OnRender();
        void OnUpdate();
    private:
        rl::Model* m_Model;
    private:
        int         m_CurrSeletedMesh;
        int         m_CurrToBeCreatedMesh;
        MeshEditor* m_CurrSelectedMeshEditor;
    };
    
    
    class MeshRendererPanel: public ComponentPanel
    {
    public:
        MeshRendererPanel(rl::MeshRenderer* meshRenderer);
        ~MeshRendererPanel();
    public:
        void OnRender();
        void OnUpdate();
    private:
        void m_OnRender_MaterialEdit();
//        void m_OnRender_ModelEdit();
//        void m_OnRender_MeshSelected();
//        void m_OnRender_TextureSelect();
    public:
        inline void BindMeshRenderer(rl::MeshRenderer* meshRenderer) { m_MeshRenderer = meshRenderer; }
        inline void BindComponent(Component* component) { m_MeshRenderer = dynamic_cast<rl::MeshRenderer*>(component);}
    private:
        rl::MeshRenderer*   m_MeshRenderer;
        ModelEditor*        m_ModelEditor;
    };
};
#endif /* MeshRendererPanel_hpp */

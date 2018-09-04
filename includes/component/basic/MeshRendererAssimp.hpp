//
//  MeshRendererAssimp.hpp
//  bird
//
//  Created by 汪依尘 on 8/12/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef MeshRendererAssimp_hpp
#define MeshRendererAssimp_hpp

#include <stdio.h>
#include <vector>
#include <unordered_map>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Component.hpp"
#include "Renderer.hpp"

class GameObject;
class Light;

namespace rl {
    
    class Model;
    class Shader;
    class Material;
    struct ShaderSources;
    
    /** Use Assimp to load models **/
    class MeshRenderer: public Component
    {
    public:
        static  MeshRenderer* BuildFromLuaScript( GameObject* thz, const char* scriptPath);
        
    public:
        MeshRenderer( GameObject* thz, Model* model, Material* mat);
        ~MeshRenderer();
        
    public:
        inline Model*       GetModel() const { return m_Model; }
        inline Material*    GetMaterial() const { return m_Material; }
        inline bool&        GetIsActive() { return m_IsActive; }
      
    public:
        void Update() override;
        
    public:
        inline void SetRendererMode(const unsigned char& mode) { m_Renderer->SetDrawMode(mode); }
        inline void SetActiveRendererMode(const unsigned char& mode) { m_ActiveMode = mode; }
    public:
        void Draw() const;
        void DrawOutline() const;
        void DrawInstances( unsigned instanceNum) const;
    private:
        void RenderPrepare() const;
        void ApplyLight(Light* light) const;

    private:
        Model*      m_Model;
        Material*   m_Material;
        Renderer*   m_Renderer;
        
    private:
        bool            m_IsActive;
        unsigned char   m_ActiveMode;
    };
}

#endif /* MeshRendererAssimp_hpp */

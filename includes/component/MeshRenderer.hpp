//
//  MeshRenderer.hpp
//  bird
//
//  Created by 汪依尘 on 6/17/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef MeshRenderer_hpp
#define MeshRenderer_hpp

#include "Component.hpp"
#include "Renderer.hpp"
#include <stdio.h>
#include <memory>
#include <vector>
#include "Material.hpp"
#include "Model.hpp"

extern float DefaultVPos[];
extern float DefaultTcs[];
extern unsigned int DefaultIndexData[];

class Light;

class MeshRenderer: public Component
{
public:
    MeshRenderer(GameObject* gameObject, const std::vector<ModelElement> elements, Material* material = new Material());
    
    MeshRenderer(GameObject* gameObject, ModelElement_Group mElement, Material* material = new Material());
    ~MeshRenderer();
    
    void ModelInit(const std::vector<ModelElement>& elements);
    void RenderPrepare();
    void ApplyLight(Light* light);
    
    void Draw();
    void Render();
    
    inline Model* GetModel() const { return m_Model; }
    inline Material* GetMaterial() const { return m_Material; }
    inline Renderer* GetRenderer() const { return m_Renderer; }
    inline bool& GetIsActive() { return m_IsActive; }
    
public:
    void Reload(ModelElement_Group mElement, Shader* shader, Texture* texture);
private:
    Model* m_Model;
    Material* m_Material;
    Renderer* m_Renderer;
    bool m_IsActive;
};
#endif /* MeshRenderer_hpp */

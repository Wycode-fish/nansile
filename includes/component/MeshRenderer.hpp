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
    static MeshRenderer* BuildFromScript(const char* meshInfoPath);
public:
    MeshRenderer(GameObject* gameObject, const std::vector<rl::MeshElement> elements, rl::Material* material = new rl::Material());
    MeshRenderer(GameObject* gameObject, rl::MeshElement_Group mElement, rl::Material* material = new rl::Material());
    ~MeshRenderer();
    
    void MeshInit(const std::vector<rl::MeshElement>& elements);
    void RenderPrepare();
    void ApplyLight(Light* light);
    
    void Draw();
    void Render();
    
    inline rl::Mesh* GetMesh() const { return m_Mesh; }
    inline rl::Material* GetMaterial() const { return m_Material; }
    inline rl::Renderer* GetRenderer() const { return m_Renderer; }
    inline bool& GetIsActive() { return m_IsActive; }
    
public:
    void Reload(rl::MeshElement_Group mElement, rl::Shader* shader, rl::Texture* texture);
private:
    rl::Mesh* m_Mesh;
    rl::Material* m_Material;
    rl::Renderer* m_Renderer;
    bool m_IsActive;
};
#endif /* MeshRenderer_hpp */

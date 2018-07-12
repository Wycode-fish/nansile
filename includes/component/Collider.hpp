//
//  Collider.hpp
//  bird
//
//  Created by 汪依尘 on 6/21/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Collider_hpp
#define Collider_hpp

#include <stdio.h>
#include "Component.hpp"
#include <stdio.h>

class Transform;
class Collision;

class Collider: public Component
{
public:
    bool IsTrigger;
    bool IsPositionLocked[3];
public:
    Collider(GameObject* gameobject);
    void OnCollision(Collision collision);
    void OnTriggerEnter();
    void ColliderInit();
    ~Collider();
public:
    void Update();
    void SetIsPositionLocked(bool* lock_status);
    inline Transform* GetTransform() {return m_Transform;}
private:
    Transform* m_Transform;
};
#endif /* Collider_hpp */

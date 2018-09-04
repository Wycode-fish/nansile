//
//  CollisionSys.hpp
//  bird
//
//  Created by 汪依尘 on 6/25/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef CollisionSys_hpp
#define CollisionSys_hpp

#include <stdio.h>
#include <vector>
#include "System.h"
#include "ml.h"

class Collider;

class CollisionSys: public System
{
public:
    static CollisionSys* GetInstance();
    static std::vector<Collider*> Colliders;
    static void CollisionProcess();
    static bool IsAABBCollide(Collider* a, Collider* b, ml::Vector3f* res);
public:
    int Init();
    int Update();
private:
    CollisionSys();
    ~CollisionSys();
    CollisionSys& operator=(const CollisionSys&) = delete;
    CollisionSys(const CollisionSys&) = delete;
    
private:
    static CollisionSys* m_Instance;
    
};
#endif /* CollisionSys_hpp */

//
//  IndexBuffer.hpp
//  bird
//
//  Created by 汪依尘 on 6/10/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef IndexBuffer_hpp
#define IndexBuffer_hpp

#include <stdio.h>

class IndexBuffer
{
public:
    IndexBuffer(const unsigned int* data = NULL, const int& cnt = 0);
    ~IndexBuffer();
    void Init(const unsigned int* data, const int& cnt);
    void Bind() const;
    void Unbind() const;
    inline unsigned int GetCount() { return m_Count; }
private:
    unsigned int m_RendererID;
    unsigned int m_Count;
};
#endif /* IndexBuffer_hpp */

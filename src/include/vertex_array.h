#ifndef __VERTEX_ARRAY_H__
#define __VERTEX_ARRAY_H__

class VertexArray {
    public:
        VertexArray();
        
        void init();
        void destroy();
        
        void bind();
        void unbind();

        // Getters
        unsigned int getID();

    private:
        unsigned int m_id;
};

#endif
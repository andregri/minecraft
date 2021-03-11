#ifndef __VERTEX_BUFFER_H__
#define __VERTEX_BUFFER_H__

class VertexBuffer {
    public:
        VertexBuffer();

        void init();
        void destroy();
        
        void bind();
        void unbind();

        void loadVertices(int num, float* vertices);

        // Getters
        unsigned int getID();

    private:
        unsigned int m_id;
};

#endif
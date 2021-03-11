#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <string>

class Texture {
    public:
        Texture();

        void init();
        void destroy();

        void bind();
        void unbind();

        void loadData(const std::string&);

        // Getters
        unsigned int getID();

    private:
        unsigned int m_id;
};

#endif
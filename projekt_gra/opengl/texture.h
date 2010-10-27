#ifndef TEXTURE_H
#define TEXTURE_H

class Texture {
public:
    enum Type {
        Ambient,
        Diffuse,
        TypeCount
    };

    unsigned char *data;
    unsigned int width, height;
    unsigned int devilId;
    unsigned int openGLId;
};

#endif // TEXTURE_H

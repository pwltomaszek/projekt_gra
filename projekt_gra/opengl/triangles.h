#ifndef TRIANGLES_H
#define TRIANGLES_H

#include <string>

class Triangles {
public:
    Triangles();
    Triangles( const Triangles &other );
    void operator=( const Triangles &other );
    ~Triangles();

    unsigned int* indices() const;
    unsigned int indicesCount() const;
    std::string materialName() const;
    void setIndices( const unsigned int &count, unsigned int *array );
    void setMaterialName( const std::string &name );

private:
    std::string mMaterialName;
    unsigned int *mIndices;
    unsigned int mIndicesCount;
};

#endif // TRIANGLES_H

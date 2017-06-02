#ifndef GLPRESS_MESHFACTORY_H
#define GLPRESS_MESHFACTORY_H


#include "Mesh.h"

class OBJParser {
public:

    static std::shared_ptr<Mesh> loadFromFile(std::string fileName);

    static std::shared_ptr<Mesh> loadFromObjFile(std::string fileName);

    static void genearateCodeFrmObj(std::string fileName);
};


#endif //GLPRESS_MESHFACTORY_H

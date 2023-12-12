//#include "meshprimitive.h"
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <sstream>
//MeshPrimitive::MeshPrimitive(glm::mat4 CTM, SceneMaterial material, std::string filepath) : ShapePrimitive(CTM, material)
//{
//    m_filepath = filepath;
//    m_ptype = PrimitiveType::PRIMITIVE_MESH;
//    setVertexData();
//};

//void MeshPrimitive::updateParams(int param1, int param2) {
//    return;
//}

//void MeshPrimitive::setVertexData() {
//    std::ifstream file(m_filepath);
//    if (!file.is_open()) {
//        std::cerr << "Error opening file: " << m_filepath << std::endl;
//        return;
//    }
//    std::vector<float> vertices;
//    std::vector<float> normals;

//    std::string line;
//    while (std::getline(file, line)) {
//        std::istringstream iss(line);
//        std::string token;
//        iss >> token;

//        if (token == "v") {
//            for (int i = 0; i < 3; i++) {
//                float ele;
//                iss >> ele;
//                vertices.push_back(ele);
//            }
//        } else if (token == "vn") {
//            for (int i = 0; i < 3; i++) {
//                float ele;
//                iss >> ele;
//                normals.push_back(ele);
//            }
//        } else if (token == "f") {
//            bool noNormal = false;
//            for (int i = 0; i < 3; ++i) {
//                int vIndex, nIndex;
//                iss >> vIndex;
//                if (iss.peek() == '/') {
//                    iss.ignore(); // Ignore the '/' character
//                    iss.ignore(); // Ignore the texture index (assuming it is not used)
//                    iss >> nIndex;

//                    vIndex = (vIndex - 1) * 3;
//                    nIndex = (nIndex - 1) * 3;
//                    m_vertexData.push_back(vertices[vIndex + 0]);
//                    m_vertexData.push_back(vertices[vIndex + 1]);
//                    m_vertexData.push_back(vertices[vIndex + 2]);

//                    m_vertexData.push_back(normals[nIndex + 0]);
//                    m_vertexData.push_back(normals[nIndex + 1]);
//                    m_vertexData.push_back(normals[nIndex + 2]);
//                } else {
//                    noNormal = true;
//                    vIndex = (vIndex - 1) * 3;
//                    m_vertexData.push_back(vertices[vIndex + 0]);
//                    m_vertexData.push_back(vertices[vIndex + 1]);
//                    m_vertexData.push_back(vertices[vIndex + 2]);
//                }

//            }
//            if (noNormal) {
//                int l1 = m_vertexData.size() - 9;
//                int l2 = l1 + 3;
//                int l3 = l2 + 3;

//                glm::vec3 v1 = {m_vertexData[l1], m_vertexData[l1 + 1], m_vertexData[l1 + 2]};
//                glm::vec3 v2 = {m_vertexData[l2], m_vertexData[l2 + 1], m_vertexData[l2 + 2]};
//                glm::vec3 v3 = {m_vertexData[l3], m_vertexData[l3 + 1], m_vertexData[l3 + 2]};

//                glm::vec3 e1 = v2 - v1;
//                glm::vec3 e2 = v3 - v1;

//                glm::vec3 normal = glm::normalize(glm::cross(e1, e2));

//                for (int i = 0; i < 9; i++) {
//                    m_vertexData.pop_back();
//                }

//                m_vertexData.push_back(v1[0]);
//                m_vertexData.push_back(v1[1]);
//                m_vertexData.push_back(v1[2]);
//                m_vertexData.push_back(normal[0]);
//                m_vertexData.push_back(normal[1]);
//                m_vertexData.push_back(normal[2]);

//                m_vertexData.push_back(v2[0]);
//                m_vertexData.push_back(v2[1]);
//                m_vertexData.push_back(v2[2]);
//                m_vertexData.push_back(normal[0]);
//                m_vertexData.push_back(normal[1]);
//                m_vertexData.push_back(normal[2]);

//                m_vertexData.push_back(v3[0]);
//                m_vertexData.push_back(v3[1]);
//                m_vertexData.push_back(v3[2]);
//                m_vertexData.push_back(normal[0]);
//                m_vertexData.push_back(normal[1]);
//                m_vertexData.push_back(normal[2]);
//            }
//        }
//    }

//    file.close();
//}

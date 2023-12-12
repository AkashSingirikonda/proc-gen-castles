#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "sceneprimitive.h"
void pushVec3(glm::vec3 vec, std::vector<float>* data)
{
    data->push_back(vec.x);
    data->push_back(vec.y);
    data->push_back(vec.z);
}

void pushPointAndNorm3(glm::vec3 p, glm::vec3 n, std::vector<float>* data)
{
    pushVec3(p, data);
    pushVec3(n, data);
}

void pushUV(glm::vec2 uv, std::vector<float>* data)
{
    data->push_back(uv.x);
    data->push_back(uv.y);
}

void makeFace(std::vector<float>* data, glm::vec3 topLeft, glm::vec3 topRight, glm::vec3 bottomLeft, glm::vec3 bottomRight)
{
    glm::vec3 n = glm::normalize(glm::cross(bottomLeft - topLeft, topRight - topLeft));

    pushPointAndNorm3(topLeft, n, data);
    pushUV(glm::vec2(0.f, 1.f), data);
    pushPointAndNorm3(bottomLeft, n, data);
    pushUV(glm::vec2(0.f, 0.f), data);
    pushPointAndNorm3(bottomRight, n, data);
    pushUV(glm::vec2(1.f, 0.f), data);

    pushPointAndNorm3(topLeft, n, data);
    pushUV(glm::vec2(0.f, 1.f), data);
    pushPointAndNorm3(bottomRight, n, data);
    pushUV(glm::vec2(1.f, 0.f), data);
    pushPointAndNorm3(topRight, n, data);
    pushUV(glm::vec2(1.f, 1.f), data);
}

void PrimitivePlane::generate(int k1, int k2)
{
    VBO.clear();

    makeFace(&VBO,
             glm::vec3( 0.5f, 0.5f,  0.5f),
             glm::vec3(-0.5f, 0.5f,  0.5f),
             glm::vec3( 0.5f, 0.5f, -0.5f),
             glm::vec3(-0.5f, 0.5f, -0.5f));
}

void PrimitiveCube::generate(int k1, int k2)
{
    VBO.clear();

    makeFace(&VBO,
             glm::vec3(-0.5f,  0.5f, 0.5f),
             glm::vec3( 0.5f,  0.5f, 0.5f),
             glm::vec3(-0.5f, -0.5f, 0.5f),
             glm::vec3( 0.5f, -0.5f, 0.5f));

    makeFace(&VBO,
             glm::vec3( 0.5f,  0.5f, -0.5f),
             glm::vec3(-0.5f,  0.5f, -0.5f),
             glm::vec3( 0.5f, -0.5f, -0.5f),
             glm::vec3(-0.5f, -0.5f, -0.5f));

    makeFace(&VBO,
             glm::vec3( 0.5f, 0.5f,  0.5f),
             glm::vec3(-0.5f, 0.5f,  0.5f),
             glm::vec3( 0.5f, 0.5f, -0.5f),
             glm::vec3(-0.5f, 0.5f, -0.5f));

    makeFace(&VBO,
             glm::vec3(-0.5f, -0.5f,  0.5f),
             glm::vec3( 0.5f, -0.5f,  0.5f),
             glm::vec3(-0.5f, -0.5f, -0.5f),
             glm::vec3( 0.5f, -0.5f, -0.5f));

    makeFace(&VBO,
             glm::vec3(0.5f, -0.5f,  0.5f),
             glm::vec3(0.5f,  0.5f,  0.5f),
             glm::vec3(0.5f, -0.5f, -0.5f),
             glm::vec3(0.5f,  0.5f, -0.5f));

    makeFace(&VBO,
             glm::vec3(-0.5f,  0.5f,  0.5f),
             glm::vec3(-0.5f, -0.5f,  0.5f),
             glm::vec3(-0.5f,  0.5f, -0.5f),
             glm::vec3(-0.5f, -0.5f, -0.5f));
}

void PrimitiveCone::generate(int phiTesselations, int thetaTesselations) {
    thetaTesselations = fmax(thetaTesselations, 3);
    float PI = 3.14159265358979323;
    VBO.clear();
    VBO.reserve(phiTesselations * phiTesselations * 6 * 2);
    thetaTesselations = 17;
        phiTesselations= 5;

//    for(int iTheta = 0; iTheta < thetaTesselations; iTheta++) {
//        for(int iPhi = 0; iPhi < phiTesselations; iPhi++) {
//            float phi1 = 1.0f  * iPhi / phiTesselations - 0.5f;
//            float phi2 = 1.0f  * (iPhi + 1.0f) / phiTesselations - 0.5f;

//            float r1 = 0.5f - 0.5f  * iPhi / phiTesselations;
//            float r2 = 0.5f - 0.5f  * (iPhi + 1.0f) / phiTesselations;

//            float the1 = 1.0f * iTheta / thetaTesselations * 2.0f * PI;
//            float the2 = 1.0f * (iTheta + 1.0f) / thetaTesselations * 2.0f * PI;

//            glm::vec3 p1 = glm::vec3(glm::sin(the1) * r1, phi1, glm::cos(the1) * r1);
//            glm::vec3 p2 = glm::vec3(glm::sin(the2) * r1, phi1, glm::cos(the2) * r1);
//            glm::vec3 p3 = glm::vec3(glm::sin(the1) * r2, phi2, glm::cos(the1) * r2);
//            glm::vec3 p4 = glm::vec3(glm::sin(the2) * r2, phi2, glm::cos(the2) * r2);

//            glm::vec3 n1 = glm::normalize(glm::vec3(glm::sin(the1), .5, glm::cos(the1)));
//            glm::vec3 n2 = glm::normalize(glm::vec3(glm::sin(the2), .5, glm::cos(the2)));


//            if(iPhi == phiTesselations - 1){
//                float the3 = 1.0f * (iTheta + .5f) / thetaTesselations * 2.0f * PI;
//                glm::vec3 n3 = glm::normalize(glm::vec3(glm::sin(the3), .5, glm::cos(the3)));

//                pushPointAndNorm3(p1, n1, &VBO);
//                pushPointAndNorm3(p2, n2, &VBO);
//                pushPointAndNorm3(p3, n3, &VBO);
//            } else {
//                pushPointAndNorm3(p1, n1, &VBO);
//                pushPointAndNorm3(p2, n2, &VBO);
//                pushPointAndNorm3(p3, n1, &VBO);

//                pushPointAndNorm3(p2, n2, &VBO);
//                pushPointAndNorm3(p4, n2, &VBO);
//                pushPointAndNorm3(p3, n1, &VBO);
//            }


//        }
//    }

    float phiStep = 0.5f / phiTesselations;

    for(int iPhi = 0; iPhi < phiTesselations; iPhi++) {
        for(int iTheta = 0; iTheta < thetaTesselations; iTheta++) {
            float phi1 = iPhi * phiStep;
            float phi2 = (iPhi + 1) * phiStep;

            float the1 = 1.0f * iTheta / thetaTesselations * 2.0f * PI;
            float the2 = 1.0f * (iTheta + 1.0f) / thetaTesselations * 2.0f * PI;

            glm::vec3 p1 = glm::vec3(phi1 * glm::sin(the1), -.5, phi1 * glm::cos(the1));
            glm::vec3 p2 = glm::vec3(phi1 * glm::sin(the2), -.5, phi1 * glm::cos(the2));
            glm::vec3 p3 = glm::vec3(phi2 * glm::sin(the1), -.5, phi2 * glm::cos(the1));
            glm::vec3 p4 = glm::vec3(phi2 * glm::sin(the2), -.5, phi2 * glm::cos(the2));

            glm::vec3 n = glm::vec3(0, -1, 0);

            pushPointAndNorm3(p1, n, &VBO);
            pushPointAndNorm3(p2, n, &VBO);
            pushPointAndNorm3(p3, n, &VBO);

            pushPointAndNorm3(p2, n, &VBO);
            pushPointAndNorm3(p4, n, &VBO);
            pushPointAndNorm3(p3, n, &VBO);

        }
    }
}

// Primitive Mesh Function

void PrimitiveMesh::input_filename(std::string filepath) {
    m_filepath = filepath;
}

void PrimitiveMesh::generate(int phiTesselations, int thetaTesselations) {
    m_filepath = "../../resources/assets/castle/Models/towerSquareMidOpen.obj";
    VBO.clear();
    // Getting the filepath
    std::ifstream file(m_filepath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << m_filepath << std::endl;
        return;
    }
    std::vector<glm::vec3> c_vertices;
    std::vector<glm::vec3> c_normals;
    std::vector<glm::vec2> c_uvs;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "v") {
            glm::vec3 to_add = {0, 0, 0};
            for (int i = 0; i < 3; i++) {
                iss >> to_add[i];
            }
            c_vertices.push_back(to_add);
        } else if (token == "vn") {
            glm::vec3 to_add = {0, 0, 0};
            for (int i = 0; i < 3; i++) {
                iss >> to_add[i];
            }
            c_normals.push_back(to_add);
        } else if (token == "vt") {
            glm::vec2 to_add = {0, 0};
            for (int i = 0; i < 2; i++) {
                iss >> to_add[i];
            }
            c_uvs.push_back(to_add);
        } else if (token == "f") {
            bool noNormal = false;
            for (int i = 0; i < 3; ++i) {
                int vIndex, nIndex, tIndex;
                iss >> vIndex;
                iss.ignore();
                iss >> nIndex;
                iss.ignore();
                iss >> tIndex;

                pushPointAndNorm3(c_vertices[vIndex-1], c_normals[nIndex-1], &VBO);
                pushUV(c_uvs[tIndex-1], &VBO);
            }
        }
    }
    file.close();

}

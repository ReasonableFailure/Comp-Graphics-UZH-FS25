#include "Torus.h"
#include <math.h>       // for M_PI
#include <glm/glm.hpp>  // for glm::vec3, etc.
#include <glm/gtc/constants.hpp>

namespace cgCourse
{
    Torus::Torus(float majorRadius, float minorRadius,int majorSeg, int minorSeg, float off, float twist) : R(majorRadius),
          r(minorRadius),
          numSegments(majorSeg),
          numTubeSegments(minorSeg),
          offset(off),
          twistFactor(twist)
    {
        // 1) Generate torus geometry
        generateMesh();

        // 2) Offset vertices along normal
        applyOffset();
    }

    void Torus::generateMesh()
    {
        // Clear old data
        positions.clear();
        normals.clear();
        colors.clear();
        faces.clear();        
        // **TODO**: Implement parametric torus with a warp
        // Use angles: theta in [0..2π), phi in [0..2π).
        // Example of warping:
        // float thetaWarp = theta + twistFactor * sin(phi);
        
        
        // Loop over i in [0..numSegments)
        //   float theta = ...
        // Loop over j in [0..numTubeSegments)
        //   float phi = ...
        // Then compute (x, y, z)

        // Also store normals and a color. Example color:
        // glm::vec3 color = glm::vec3(abs(cos(thetaWarp)), abs(sin(phi)), 0.5f);
        const float PHI = 2* M_PI;
        const float THETA = 2*M_PI;
        for(int i = 0; i < this->numSegments; ++i){
            for(int j = 0; j <this->numTubeSegments;++j){
                float phi = i * PHI/numSegments;
                float theta =  j * THETA/numTubeSegments;
                float thetaWarp = theta + twistFactor * sin(phi*theta);
                float x = this-> R * cos(phi) + this->r * cos(phi) * cos(thetaWarp);
                float y = this-> R * sin(phi) + this->r * sin(phi) * cos(thetaWarp);
                float z = this->r * sin(thetaWarp);
                glm::vec3 point = glm::vec3(x,y,z);
                glm::vec3 point_color = glm::vec3(abs(cos(thetaWarp)), abs(sin(phi)), 0.5f);
                positions.push_back(point);
                colors.push_back(point_color);
            }
        }
        // **TODO**: Build triangle faces
        // Each cell has two triangles:
        //   (i, j), (i+1, j), (i, j+1)
        //   (i, j+1), (i+1, j), (i+1, j+1)
        for(int i = 0; i < this->numSegments; ++i){
            for(int j = 0; j < this->numTubeSegments; ++j){
                int iplus1 = 0;
                int jplus1 = 0;
                if(this->numSegments-1 > i){
                    iplus1 = i+1;
                }
                if(this->numTubeSegments-1 > j){
                    jplus1 = j+1;
                }
                glm::uvec3 tri1 = glm::uvec3(Torus::indexOfVertex(i,j), Torus::indexOfVertex(iplus1,j),indexOfVertex(i,jplus1));
                glm::uvec3 tri2 =glm::uvec3(indexOfVertex(i,jplus1), indexOfVertex(iplus1,j), indexOfVertex(iplus1,jplus1));
                faces.push_back(tri1);
                faces.push_back(tri2);
            }
        }
        //triangle ( v1, v2, v3 ) 
        //edge1 = v2-v1
        //edge2 = v3-v1
        //triangle.normal = cross(edge1, edge2).normalize()
        for(glm::uvec3 &triangle : faces){
            glm::vec3 edge1 = positions[triangle[1]]-positions[triangle[0]];
            glm::vec3 edge2 = positions[triangle[2]]-positions[triangle[0]];
            glm::vec3 faceNormal = glm::cross(edge1,edge2);
            faceNormal = glm::normalize(faceNormal);
            faceNormals.push_back(faceNormal);
        }

        /*vertex v1, v2, v3, ....
        triangle tr1, tr2, tr3 // all share vertex v1
        v1.normal = normalize( tr1.normal + tr2.normal + tr3.normal )
         */
        std::vector<std::vector<unsigned int>> associate; //associate the 3 faces to particle i
        for(unsigned int i = 0; i < positions.size(); ++i){
            std::vector<unsigned int> oneVertexAssoc = {i};
            for(unsigned int j = 0; j < faces.size() /*&& oneVertexAssoc.size() < 5*/; ++j){
                if(faces[j][0] == i || faces[j][1] == i ||faces[j][2] == i ){ //inspect face[j]'s components, which are indices into positions
                    oneVertexAssoc.push_back(j); //save index of face which is associated
                }
            }
            /*if(oneVertexAssoc.size() == 4){*/
                associate.push_back(oneVertexAssoc);
            /*}            */
        }
        for(int i = 0; i < positions.size(); ++i){
            glm::vec3 vertexnormal=glm::vec3(0);

            for(int j = 1; j < associate[i].size(); ++j){ //unpack the std vector unsigned int
                vertexnormal += faceNormals[associate[i][j]]; //index is a faces index. faceNormals has the same order
            }

            normals.push_back(glm::normalize(vertexnormal));
        }
        

        
        
    }

    int Torus::indexOfVertex(int i, int j){
        return i * this->numTubeSegments + j;
    }

    void Torus::applyOffset()
    {
        // **TODO**: For each vertex, add: positions[i] += offset * normals[i];
        for(int i = 0; i < positions.size(); ++i){
            positions[i] += offset * normals[i];
        }
    }

    void Torus::draw()
    {
        glBindVertexArray(vaoID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

        // Each face is a uvec3 => 3 indices per face
        glDrawElements(GL_TRIANGLES,
                       GLsizei(faces.size() * 3),
                       GL_UNSIGNED_INT,
                       nullptr);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}

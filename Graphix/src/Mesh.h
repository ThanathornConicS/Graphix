#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <glad/glad.h> 

namespace gpx
{
    struct Vertex
    {
        Vertex(void)
        {
            m_pos = glm::vec3(0, 0, 0);
            m_texCoord = glm::vec2(0, 0);
        }
        Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
        {
            m_pos = pos;
            m_texCoord = texCoord;
        }

        inline glm::vec3* GetPos()
        {
            return &m_pos;
        }
        inline glm::vec2* GetTexCoord()
        {
            return &m_texCoord;
        }

        glm::vec3 m_pos;
        glm::vec2 m_texCoord;
    };

    class Mesh
    {
        public:
            Mesh(Vertex* vertices, uint32_t numVertice);
            virtual ~Mesh();

            void Draw();
        
        private:
            enum
            {
                POSITION_VB = 0,
                TEXCOORD_VB,
                NUM_BUFFERS
            };
            
            uint32_t VAO;
            uint32_t VAB[NUM_BUFFERS];
            uint32_t drawCount;
    };

}
#endif
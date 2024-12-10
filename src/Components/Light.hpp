//
// Created by Chase Nagle on 12/8/24.
//

#ifndef OPENGLPROJECT_LIGHT_HPP
#define OPENGLPROJECT_LIGHT_HPP


/* The Plan:
 * So there is going to be one unified lighting shader that builds our shadow map.
 * There will be a bool uniform, Sampler uniform for Dynamic Geomatry (That use vertex displacement - like Terrain)
 * If the bool is enabled we will sample the Sampler2D.
 * Once all objects are rendered for a particular light
 *
 *
 */




class Light{
private:
    unsigned int depthMapFBO;
    unsigned int depthMap;

    int SHADOW_WIDTH = 2048;
    int SHADOW_HEIGHT = 2048;




    glm::vec3 target;

    float near_plane = 1.0f;
    float far_plane = 10.0f;

    ShaderProgram *program;

public:
    glm::vec3 position;
    Light(Vector3 position, Vector3 target){
        this->position = glm::vec3(position.x, position.y, position.z);
        this->target = glm::vec3(target.x, target.y, target.z);

        program = new ShaderProgram("Content/Shaders/Lighting/light.frag", "Content/Shaders/Lighting/light.vert");

        glGenFramebuffers(1, &depthMapFBO);
        glGenTextures(1, &depthMap);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            std::cout << "Error: Framebuffer is not complete!" << std::endl;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Start(){
        program->Use();
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);

        ConfigureLightSpaceMatrices();
    }

    void Stop(){
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void ConfigureLightSpaceMatrices(){

        glm::mat4 ProjectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.01f, 50.0f);
        glm::mat4 LightViewMatrix = glm::lookAt(position, target, glm::vec3( 0.0f, 1.0f,  0.0f));

        glm::mat4 lightSpaceViewMatrix = ProjectionMatrix * LightViewMatrix;

        program->setUniformMat4x4("LightSpaceViewMatrix", lightSpaceViewMatrix);
    }

    unsigned int GetDepthMap(){
        return depthMap;
    }

    ShaderProgram* getShaderProgram(){
        return program;
    }

    void Use(ShaderProgram *p){
        glm::vec3 test = glm::vec3(position.x, position.y, position.z);
        p->setUniformVec3("lightPos", position);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        program->setUniformInt("depthMap", 1);
    }






};

#endif //OPENGLPROJECT_LIGHT_HPP

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
public:

    ShaderProgram* Program;
    GLuint FramebufferName;
    GLuint depthTexture;

    glm::vec3 position;

    Light(){
        position = glm::vec3(0.0);

        Program = new ShaderProgram("Content/Shaders/Lighting/light.frag", "Content/Shaders/Lighting/light.vert");

        FramebufferName = 0;
        glGenFramebuffers(1, &FramebufferName);
        glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

        // Depth texture. Slower than a depth buffer, but you can sample it later in your shader
        glGenTextures(1, &depthTexture);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 1024 * 10, 1024 * 10, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

        glDrawBuffer(GL_NONE); // No color buffer is drawn to.

        // Always check that our framebuffer is ok
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            cout << "Error: Could Not Create FrameBuffer. " << endl;
    }

    void SetUpMVP(){
        glm::vec3 lightInvDir = glm::vec3(0.5f, 2.0f , 2.0f);

        // Compute the MVP matrix from the light's point of view
        glm::mat4 depthProjectionMatrix = glm::ortho<float>(-20, 20,-20, 20, -25, 50);
        glm::mat4 depthViewMatrix = glm::lookAt(position, glm::vec3(0,0,0), glm::vec3(0,1,0));
//        glm::mat4 depthModelMatrix = glm::mat4(1.0);
//        glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

        Program->setUniformMat4x4("depthProj", depthProjectionMatrix);
        Program->setUniformMat4x4("depthView", depthViewMatrix);

    }


    void Start(){
        glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
        glViewport(0, 0, 1024 * 10, 1024 * 10);
        glClear(GL_DEPTH_BUFFER_BIT);

        Program->Use();
        SetUpMVP();
    }

    void Stop(){
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Use(ShaderProgram* p){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        p->setUniformSampler2D("shadowMap", 0);




        // Compute the MVP matrix from the light's point of view
        glm::mat4 depthProjectionMatrix = glm::ortho<float>(-20, 20, -20, 20,-25, 50);
        glm::mat4 depthViewMatrix = glm::lookAt(position, glm::vec3(0,0,0), glm::vec3(0,1,0));
        glm::mat4 depthModelMatrix = glm::mat4(1.0);
        glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;







        p->setUniformMat4x4("LightSpaceViewMatrix", depthMVP);
        p->setUniformVec3("lightPos", position);


    }

};

#endif //OPENGLPROJECT_LIGHT_HPP

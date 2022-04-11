#include "scenebasic_uniform.h"

#include <cstdio>
#include <cstdlib>

#include <string>
using std::string;

#include <iostream>
using std::cerr;
using std::endl;

#include "helper/glutils.h"
#include <glm/gtc/matrix_transform.hpp>

using glm::vec3;
using glm::mat4;

SceneBasic_Uniform::SceneBasic_Uniform() : torus(0.7f, 0.3f, 50,50) {}

void SceneBasic_Uniform::initScene()
{
    compile();
    glEnable(GL_DEPTH_TEST);

    /*Initialise the model matrix using:*/
    model = mat4(1.0f);

    model = glm::rotate(model, glm::radians(-35.0f), vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(15.0f), vec3(0.0f, 1.0f, 0.0f));
    view = glm::lookAt(vec3(0.0f, 0.0f, 2.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
        

    projection = mat4(1.0f);

    prog.setUniform("Material.Kd", 0.9f, 0.7f, 0.8f);
    prog.setUniform("Light.Ld", 1.0f, 1.0f, 1.0f);

    prog.setUniform("LightPosition", view * glm::vec4(5.0f, 5.0f, 2.0f, 1.0f));  
        

//    std::cout << std::endl;
//
//    prog.printActiveUniforms();
//
//    /////////////////// Create the VBO ////////////////////
//    float positionData[] = {
//        -0.8f, -0.8f, 0.0f,
//         0.8f, -0.8f, 0.0f,
//         0.0f,  0.8f, 0.0f };
//    float colorData[] = {
//        1.0f, 0.0f, 0.0f,
//        0.0f, 1.0f, 0.0f,
//        0.0f, 0.0f, 1.0f };
//
//    // Create and populate the buffer objects
//    GLuint vboHandles[2];
//    glGenBuffers(2, vboHandles);
//    GLuint positionBufferHandle = vboHandles[0];
//    GLuint colorBufferHandle = vboHandles[1];
//
//    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
//    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positionData, GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
//    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colorData, GL_STATIC_DRAW);
//
//    // Create and set-up the vertex array object
//   /* glGenVertexArrays(1, &vaoHandle);
//    glBindVertexArray(vaoHandle);*/
//
//    glEnableVertexAttribArray(0);  // Vertex position
//    glEnableVertexAttribArray(1);  // Vertex color
//
//#ifdef __APPLE__
//    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
//
//    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
//#else
//    glBindVertexBuffer(0, positionBufferHandle, 0, sizeof(GLfloat) * 3);
//    glBindVertexBuffer(1, colorBufferHandle, 0, sizeof(GLfloat) * 3);
//
//    glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
//    glVertexAttribBinding(0, 0);
//    glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
//    glVertexAttribBinding(1, 1);
//#endif
//    glBindVertexArray(0);


}

void SceneBasic_Uniform::compile()
{
    try {
        prog.compileShader("shader/basic_uniform.vert");
        prog.compileShader("shader/basic_uniform.frag");
        prog.link();
        prog.use();
    }
    catch (GLSLProgramException& e) {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}

void SceneBasic_Uniform::update(float t)
{
    /*update your angle here*/
    /*if (m_animate) {
        angle += 0.1f;
        if (angle >= 360.0f)
            angle -= 360.0f;
    }*/


}


void SceneBasic_Uniform::render()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    setMatrices();

    torus.render();
#


    //rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, vec3(0.0f, 0.0f, 1.0f));
    //
    //GLuint programHandle = prog.getHandle();
    //GLuint location = glGetUniformLocation(programHandle, "RotationMatrix");

    //glUniformMatrix4fv(location, 1, GL_FALSE, &rotationMatrix[0][0]);


    ////create the rotation matrix here and update the uniform in the shader 

    //glBindVertexArray(vaoHandle);
    //glDrawArrays(GL_TRIANGLES, 0, 3);

    //glBindVertexArray(0);
}

void SceneBasic_Uniform::setMatrices()
{
    mat4 mv = view * model; //create model view matrix

    prog.setUniform("ModelViewMatrix", mv); //set the uniform “ModelViewMatrix” and pass mv matrix
    prog.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2]))); // set the uniform for “NormalMatrix”
    prog.setUniform("MVP", projection * mv); //set the uniform for model view projection matrix called “MVP” and pass in projection matrix * model view matrix
        
}

void SceneBasic_Uniform::resize(int w, int h)
{
    width = w;
    height = h;
    glViewport(0, 0, w, h);
    projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 100.0f);
        
}

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

const float screenWidth = 100.0f;
const float screenHeight = 100.0f;

struct camera2D {
    glm::vec2 position = glm::vec2(0.0f, 0.0f);
    float zoom = 1.0f;
    float rotation = 0.0f;

    glm::mat4 getViewMatrix() const {
        glm::mat4 view = glm::mat4(1.0f);


        view = glm::translate(view, glm::vec3(-position, 0.0f));

        view = glm::scale(view, glm::vec3(zoom, zoom, 1.0f));

        return view;
    }
};
camera2D camera;
glm::mat4 projection = glm::ortho(0.0f, screenWidth, 0.0f, screenHeight, -1.0f, 1.0f);

glm::mat4 vpMatrix = projection * camera.getViewMatrix();

void updateCamera(camera2D& camera, float dt){
    const float cameraSpeed = 10.0f;

    //colocar coisa de atualizar camera
}

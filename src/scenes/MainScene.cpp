#include "MainScene.h"

#include "../cbs/components/MeshRenderer/MeshRenderer.h"
#include "../cbs/components/AstronomicalObject.h"
#include "../cbs/components/PointLight.h"
#include "../cbs/components/FirstPersonController.h"
#include "../cbs/components/ThirdPersonController.h"
#include "../cbs/components/Camera.h"
#include "../cbs/components/Manager.h"
#include "../cbs/components/Tail.h"

#define PI 3.14159265358979323846f
#define DOUBLE_PI (PI * 2.0f)

// angular velocity w = 2pi / T
// where T := time in seconds for planet to make full cycle
#define EARTH_RADIUS 0.5f
#define EARTH_ROTATION_SPEED (360.f / 5.0f) // full rotation takes 5 second
#define EARTH_ORBIT_RADIUS (150.0f / 4.0f) // all distances are divided by 4
#define EARTH_ORBIT_ANGULAR_VELOCITY (DOUBLE_PI / (360.0f * 5.0f)) // full orbit takes 5 minutes

void MainScene::CreateScene() {
    FrameRate(60);
    
    DrawManager().Skybox("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/data/skybox/right.jpg",
                         "/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/data/skybox/left.jpg",
                         "/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/data/skybox/top.jpg",
                         "/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/data/skybox/bottom.jpg",
                         "/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/data/skybox/back.jpg",
                         "/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/data/skybox/front.jpg");
    
    
    glm::vec3 model_scale(1.0f / (976.032f * 2.0f), 1.0f / (976.032f * 2.0f), 1.0f / (986.312f * 2.0f));
    glm::quat model_rotation(glm::vec3(glm::radians(-90.0f), 0.0f, 0.0f));
    
    
    auto sun = CreateObject("Sun");
    sun->Transform().Scale(109.0f * EARTH_RADIUS * model_scale);
    sun->Transform().Rotation(model_rotation);
    sun->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/data/models/sun/13902_Earth_v1_l3.obj",
                                       ShaderProgram::Type::TEXTURE_PURE);
    sun->CreateComponent<AstronomicalObject>(EARTH_ROTATION_SPEED / 1.04f);
    sun->CreateComponent<PointLight>(glm::vec3(0.1f),
                                     glm::vec3(0.8f),
                                     glm::vec3(0.5f),
                                     1.0f,
                                     0.0014f,
                                     0.000007f);
    
    
    auto merkury = CreateObject("Merkury");
    merkury->Transform().Scale(0.38f * EARTH_RADIUS * model_scale);
    merkury->Transform().Rotation(model_rotation);
    merkury->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/data/models/merkury/13902_Earth_v1_l3.obj",
                                           ShaderProgram::Type::TEXTURE_LIGHT_RECEIVER);
    AstronomicalObject* merkury_ao = merkury->CreateComponent<AstronomicalObject>(EARTH_ROTATION_SPEED / 58.0f);
    merkury_ao->Orbit(Orbit(&sun->Transform().Position(),
                            0.39f * EARTH_ORBIT_RADIUS,
                            -EARTH_ORBIT_ANGULAR_VELOCITY / 0.24f));
    merkury->CreateComponent<Tail>(3.0f, glm::vec3(1.0f));
    
    auto wenus = CreateObject("Wenus");
    wenus->Transform().Scale(0.94f * EARTH_RADIUS * model_scale);
    wenus->Transform().Rotation(model_rotation);
    wenus->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/data/models/wenus/13902_Earth_v1_l3.obj",
                                         ShaderProgram::Type::TEXTURE_LIGHT_RECEIVER);
    auto wenus_ao = wenus->CreateComponent<AstronomicalObject>(merkury_ao);
    wenus_ao->Orbit(Orbit(&sun->Transform().Position(),
                          0.72f * EARTH_ORBIT_RADIUS,
                          -EARTH_ORBIT_ANGULAR_VELOCITY / 0.61f));
    wenus->CreateComponent<Tail>(3.0f, glm::vec3(1.0f));
    
    
    auto earth = CreateObject("Earth");
    earth->Transform().Scale(EARTH_RADIUS * model_scale);
    earth->Transform().Rotation(model_rotation);
    earth->Transform().Rotate(glm::quat(glm::vec3(glm::radians(23.0f), 0.0f, 0.0f)));
    earth->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/data/models/earth/13902_Earth_v1_l3.obj",
                                         ShaderProgram::Type::TEXTURE_LIGHT_RECEIVER);
    auto earth_ao = earth->CreateComponent<AstronomicalObject>(EARTH_ROTATION_SPEED);
    earth_ao->Orbit(Orbit(&sun->Transform().Position(),
                          EARTH_ORBIT_RADIUS,
                          -EARTH_ORBIT_ANGULAR_VELOCITY));
    earth->CreateComponent<Tail>(3.0f, glm::vec3(1.0f));
    
    
    auto mars = CreateObject("Mars");
    mars->Transform().Scale(0.53f * EARTH_RADIUS * model_scale);
    mars->Transform().Rotation(model_rotation);
    mars->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/data/models/mars/13902_Earth_v1_l3.obj",
                                        ShaderProgram::Type::TEXTURE_LIGHT_RECEIVER);
    auto mars_ao = mars->CreateComponent<AstronomicalObject>(EARTH_ROTATION_SPEED);
    mars_ao->Orbit(Orbit(&sun->Transform().Position(),
                         1.52f * EARTH_ORBIT_RADIUS,
                         -EARTH_ORBIT_ANGULAR_VELOCITY / 1.88f));
    mars->CreateComponent<Tail>(3.0f, glm::vec3(1.0f));
    
    
    auto jupiter = CreateObject("Jupiter");
    jupiter->Transform().Scale(11.2f * EARTH_RADIUS * model_scale);
    jupiter->Transform().Rotation(model_rotation);
    jupiter->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/data/models/jupiter/13902_Earth_v1_l3.obj",
                                           ShaderProgram::Type::TEXTURE_LIGHT_RECEIVER);
    auto jupiter_ao = jupiter->CreateComponent<AstronomicalObject>(0.37f * EARTH_ROTATION_SPEED);
    jupiter_ao->Orbit(Orbit(&sun->Transform().Position(),
                            5.2f * EARTH_ORBIT_RADIUS,
                            -EARTH_ORBIT_ANGULAR_VELOCITY / 11.86f));
    jupiter->CreateComponent<Tail>(3.0f, glm::vec3(1.0f));
    
    
    auto saturn = CreateObject("Saturn");
    saturn->Transform().Scale(9.45f * EARTH_RADIUS * model_scale);
    saturn->Transform().Rotation(model_rotation);
    saturn->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/data/models/saturn/13902_Earth_v1_l3.obj",
                                          ShaderProgram::Type::TEXTURE_LIGHT_RECEIVER);
    auto saturn_ao = saturn->CreateComponent<AstronomicalObject>(0.42f * EARTH_ROTATION_SPEED);
    saturn_ao->Orbit(Orbit(&sun->Transform().Position(),
                           9.54f * EARTH_ORBIT_RADIUS,
                           -EARTH_ORBIT_ANGULAR_VELOCITY / 29.44f));
    saturn->CreateComponent<Tail>(3.0f, glm::vec3(1.0f));
    
    
    auto uranus = CreateObject("Uranus");
    uranus->Transform().Scale(4.0f * EARTH_RADIUS * model_scale);
    uranus->Transform().Rotation(model_rotation);
    uranus->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/data/models/uranus/13902_Earth_v1_l3.obj",
                                          ShaderProgram::Type::TEXTURE_LIGHT_RECEIVER);
    auto uranus_ao = uranus->CreateComponent<AstronomicalObject>(0.7f * EARTH_ROTATION_SPEED);
    uranus_ao->Orbit(Orbit(&sun->Transform().Position(),
                           19.19f * EARTH_ORBIT_RADIUS,
                           -EARTH_ORBIT_ANGULAR_VELOCITY / 84.07f));
    uranus->CreateComponent<Tail>(3.0f, glm::vec3(1.0f));
    
    
    auto neptun = CreateObject("Neptun");
    neptun->Transform().Scale(3.88f * EARTH_RADIUS * model_scale);
    neptun->Transform().Rotation(model_rotation);
    neptun->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/data/models/neptun/13902_Earth_v1_l3.obj",
                                          ShaderProgram::Type::TEXTURE_LIGHT_RECEIVER);
    auto neptun_ao = neptun->CreateComponent<AstronomicalObject>(0.67f * EARTH_ROTATION_SPEED);
    neptun_ao->Orbit(Orbit(&sun->Transform().Position(),
                           30.06f * EARTH_ORBIT_RADIUS,
                           -EARTH_ORBIT_ANGULAR_VELOCITY / 164.88f));
    neptun->CreateComponent<Tail>(3.0f, glm::vec3(1.0f));
    
    
    auto camera = CreateObject("Camera");
    camera->Transform().Position(glm::vec3(0.0f, 0.0f, 80.0f));
    camera->Transform().Rotate(glm::vec3(0.0f, glm::radians(90.0f), 0.0f));
    camera->CreateComponent<Camera>(glm::perspective(glm::radians(45.0f), 2880.0f / 1800.0f, 0.1f, 3000.0f));
    auto camera_tpc = camera->CreateComponent<ThirdPersonController>();
    auto camera_fpc = camera->CreateComponent<FirstPersonController>();
    
    camera->CreateComponent<Manager>(std::array<class Object*, 9>({sun, merkury, wenus, earth, mars, jupiter, saturn, uranus, neptun}),
                                     camera_fpc,
                                     camera_tpc);
}

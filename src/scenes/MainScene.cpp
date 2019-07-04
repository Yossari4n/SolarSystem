#include "MainScene.h"

#include "../cbs/components/MeshRenderer/MeshRenderer.h"
#include "../cbs/components/AstronomicalObject.h"
#include "../cbs/components/PointLight.h"
#include "../cbs/components/FirstPersonController.h"
#include "../cbs/components/ThirdPersonController.h"
#include "../cbs/components/Camera.h"
#include "../cbs/components/Manager.h"
#include "../cbs/components/Tail.h"

/**
 * TODO
 * Unit scaling 
 * 
 * Planets' radius
 * Planets' rotation speed
 * Planets' orbit length (see AstronomicalObject.h ASTRONOMICAL_UNIT)
 */

constexpr float EARTH_RADIUS = 0.5f;

void MainScene::CreateScene() {
    FrameRate(60);
    Skybox("data/skybox/right.jpg",
           "data/skybox/left.jpg",
           "data/skybox/top.jpg",
           "data/skybox/bottom.jpg",
           "data/skybox/back.jpg",
           "data/skybox/front.jpg");
    
    
    glm::vec3 model_scale(1.0f / (976.032f * 2.0f), 1.0f / (976.032f * 2.0f), 1.0f / (986.312f * 2.0f));
    glm::quat model_rotation(glm::vec3(glm::radians(-90.0f), 0.0f, 0.0f));
    
    
    auto sun = CreateObject("Sun");
    sun->Transform().Scale(109.0f * EARTH_RADIUS * model_scale);
    sun->Transform().Rotation(model_rotation);
    sun->CreateComponent<MeshRenderer>("data/models/sun/13902_Earth_v1_l3.obj",
                                       ShaderProgram::Type::PURE_TEXTURE);
    sun->CreateComponent<AstronomicalObject>(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    sun->CreateComponent<PointLight>(glm::vec3(0.1f),
                                     glm::vec3(0.8f),
                                     glm::vec3(0.5f),
                                     1.0f,
                                     0.0014f,
                                     0.000007f);
    
    
    auto mercury = CreateObject("Mercury");
    mercury->Transform().Scale(0.38f * EARTH_RADIUS * model_scale);
    mercury->Transform().Rotation(model_rotation);
    mercury->CreateComponent<MeshRenderer>("data/models/merkury/13902_Earth_v1_l3.obj",
                                           ShaderProgram::Type::PHONG);
    mercury->CreateComponent<AstronomicalObject>(48.3313f, 3.24587E-5f, 7.0047f, 5.0E-8f, 29.1241f, 1.01444E-5f, 0.387098f, 0.0f, 0.205635f, 5.59E-10f, 168.6562f, 4.0923344368f);
    mercury->CreateComponent<Tail>(3.0f, glm::vec3(0.5f));
    
    
    auto venus = CreateObject("Venus");
    venus->Transform().Scale(0.94f * EARTH_RADIUS * model_scale);
    venus->Transform().Rotation(model_rotation);
    venus->CreateComponent<MeshRenderer>("data/models/wenus/13902_Earth_v1_l3.obj",
                                         ShaderProgram::Type::PHONG);
    venus->CreateComponent<AstronomicalObject>(76.6799f, 2.46590E-5f, 3.3946f, 2.75E-8f, 54.8910f, 1.38374E-5f, 0.723330f, 0.0f, 0.006773f, 1.302E-9f, 48.0052f, 1.6021302244f);
    venus->CreateComponent<Tail>(3.0f, glm::vec3(245.0f/ 255.0f, 245.0f / 255.0f, 235.0f / 255.0f));
    
    
    auto earth = CreateObject("Earth");
    earth->Transform().Scale(EARTH_RADIUS * model_scale);
    earth->Transform().Rotation(model_rotation);
    earth->Transform().Rotate(glm::quat(glm::vec3(glm::radians(23.0f), 0.0f, 0.0f)));
    earth->CreateComponent<MeshRenderer>("data/models/earth/13902_Earth_v1_l3.obj",
                                         ShaderProgram::Type::PHONG);
    earth->CreateComponent<AstronomicalObject>(0.0f, 0.0f, 0.0f, 0.0f, 282.9404f, 4.70935E-5f, 1.0f, 0.0f, 0.016709f, 1.151E-9f, 356.0470f, 0.9856002585f);
    earth->CreateComponent<Tail>(3.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    
    
    auto mars = CreateObject("Mars");
    mars->Transform().Scale(0.53f * EARTH_RADIUS * model_scale);
    mars->Transform().Rotation(model_rotation);
    mars->CreateComponent<MeshRenderer>("data/models/mars/13902_Earth_v1_l3.obj",
                                        ShaderProgram::Type::PHONG);
    mars->CreateComponent<AstronomicalObject>(49.5574, 2.11081E-5f, 1.8497f, 1.78E-8f, 286.5016f, 2.92961E-5f, 1.523688f, 0.0f, 0.093405f, 2.516E-9f, 18.6021f, 0.5240207766f);
    mars->CreateComponent<Tail>(3.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    
    
    auto jupiter = CreateObject("Jupiter");
    jupiter->Transform().Scale(11.2f * EARTH_RADIUS * model_scale);
    jupiter->Transform().Rotation(model_rotation);
    jupiter->CreateComponent<MeshRenderer>("data/models/jupiter/13902_Earth_v1_l3.obj",
                                           ShaderProgram::Type::PHONG);
    jupiter->CreateComponent<AstronomicalObject>(100.4542f, 2.76854E-5f, 1.3030f, 1.557E-7f, 273.8777f, 1.64505E-5f, 5.20256f, 0.0f, 0.048498f, 4.469E-9f, 19.8950f, 0.0830853001f);
    jupiter->CreateComponent<Tail>(3.0f, glm::vec3(137.0f / 255.0f, 105.0f / 255.0f, 70.0f / 255.0f));
    
    
    auto saturn = CreateObject("Saturn");
    saturn->Transform().Scale(9.45f * EARTH_RADIUS * model_scale);
    saturn->Transform().Rotation(model_rotation);
    saturn->CreateComponent<MeshRenderer>("data/models/saturn/13902_Earth_v1_l3.obj",
                                          ShaderProgram::Type::PHONG);
    auto saturn_ao = saturn->CreateComponent<AstronomicalObject>(113.6634f, 2.38980E-5f, 2.4886f, 1.081E-7f, 339.3939f, 2.97661E-5f, 9.55475f, 0.0f, 0.055546f, 9.499E-9f, 316.9670f, 0.0334442282f);
    saturn->CreateComponent<Tail>(3.0f, glm::vec3(185.0f / 255.0f, 175.0f / 255.0f, 135.0f / 255.0f));
    
    
    auto uranus = CreateObject("Uranus");
    uranus->Transform().Scale(4.0f * EARTH_RADIUS * model_scale);
    uranus->Transform().Rotation(model_rotation);
    uranus->CreateComponent<MeshRenderer>("data/models/uranus/13902_Earth_v1_l3.obj",
                                          ShaderProgram::Type::PHONG);
    auto uranus_ao = uranus->CreateComponent<AstronomicalObject>(74.0005f, 1.3978E-5f, 0.7733f, 1.9E-8f, 96.6612f, 3.0565E-5f, 19.18171f, 1.55E-8f, 0.047318f, 7.45E-9f, 142.5905f, 0.011725806f);
    uranus->CreateComponent<Tail>(3.0f, glm::vec3(195.0f / 255.0f, 215.0f / 255.0f, 240.0f / 255.0f));
    
    
    auto neptune = CreateObject("Neptune");
    neptune->Transform().Scale(3.88f * EARTH_RADIUS * model_scale);
    neptune->Transform().Rotation(model_rotation);
    neptune->CreateComponent<MeshRenderer>("data/models/neptun/13902_Earth_v1_l3.obj",
                                          ShaderProgram::Type::PHONG);
    neptune->CreateComponent<AstronomicalObject>(131.7806f, 3.0173E-5f, 1.7700f, 2.55E-7f, 272.8461f, 6.027E-6f, 30.05826f, 3.313E-8f, 0.008606f, 2.15E-9f, 260.2471f, 0.005995147f);
    neptune->CreateComponent<Tail>(3.0f, glm::vec3(110.0f / 255.0f, 120.0f / 255.0f, 140.0f / 255.0f));
    
    
    auto camera = CreateObject("Camera");
    camera->Transform().Position(glm::vec3(0.0f, 0.0f, 80.0f));
    camera->Transform().Rotate(glm::vec3(0.0f, glm::radians(90.0f), 0.0f));
    camera->CreateComponent<Camera>(glm::perspective(glm::radians(45.0f), 2880.0f / 1800.0f, 0.1f, 3000.0f));
    auto camera_tpc = camera->CreateComponent<ThirdPersonController>();
    auto camera_fpc = camera->CreateComponent<FirstPersonController>();
    camera->CreateComponent<Manager>(std::array<class Object*, 9>({sun, mercury, venus, earth, mars, jupiter, saturn, uranus, neptune}),
                                     camera_fpc,
                                     camera_tpc);
}

#include "MainScene.h"

#include "../components/MeshRenderer/MeshRenderer.h"
#include "../components/AstronomicalObject.h"
#include "../components/PointLight.h"
#include "../components/FirstPersonController.h"

#define PI 3.14159265358979323846f
#define DOUBLE_PI (PI * 2.0f)

// angular velocity w = 2pi / T
// where T := time in seconds for planet to make full cycle
#define EARTH_RADIUS 1.0f
#define EARTH_ROTATION_SPEED (360.f / 5.0f) // full rotation takes 5 second
#define EARTH_ORBIT_RADIUS (150.0f / 2.0f) // all distances are divided by two
#define EARTH_ORBIT_ANGULAR_VELOCITY (DOUBLE_PI / (360.0f * 5.0f)) // full orbit takes 5 minutes

void MainScene::CreateScene() {
    glm::vec3 model_scale(1.0f / (976.032f * 2.0f), 1.0f / (976.032f * 2.0f), 1.0f / (986.312f * 2.0f));
    glm::vec3 model_rotation(-90.0f, 0.0f, 0.0f);
    
    auto camera = CreateObject("Camera");
    /*camera->CreateComponent<Camera>(glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 3000.0f),
                                    glm::vec3(-5.0f, 20.0f, 5.0f),
                                    glm::vec3(0.0f, 1.0f, 0.0f),
                                    -30.0f,
                                    -30.0f);
    camera->CreateComponent<FirstPersonComponent>();*/
    
    // SUN
    auto sun = CreateObject("Sun");
    sun->Scale(109.0f * EARTH_RADIUS * model_scale);
    sun->Rotation(model_rotation);
    auto sun_mr = sun->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/sun/13902_Earth_v1_l3.obj", IDrawable::ShaderTypes::LIGHT_SOURCE);
    sun->CreateComponent<AstronomicalObject>(EARTH_ROTATION_SPEED / 1.04f);
    sun->CreateComponent<PointLight>(glm::vec3(0.2f), glm::vec3(0.8f), glm::vec3(0.5f), 1.0f, 0.0014f, 0.000007f);
    
    // MERKURY
    auto merkury = CreateObject("Merkury");
    merkury->Scale(0.38f * EARTH_RADIUS * model_scale);
    merkury->Rotation(model_rotation);
    auto merkury_mr = merkury->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/merkury/13902_Earth_v1_l3.obj", IDrawable::ShaderTypes::LIGHT_RECEIVER);
    auto merkury_ao = merkury->CreateComponent<AstronomicalObject>(EARTH_ROTATION_SPEED / 58.0f);
    merkury_ao->Orbit(Orbit(&sun->Position(), 0.39f * EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY / 0.24f));
    
    // WENUS
    auto wenus = CreateObject("Wenus");
    wenus->Scale(0.94f * EARTH_RADIUS * model_scale);
    wenus->Rotation(model_rotation);
    auto wenus_mr = wenus->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/wenus/13902_Earth_v1_l3.obj", IDrawable::ShaderTypes::LIGHT_RECEIVER);
    auto wenus_ao = wenus->CreateComponent<AstronomicalObject>(EARTH_ROTATION_SPEED / 243.0f);
    wenus_ao->Orbit(Orbit(&sun->Position(), 0.72f * EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY / 0.61f));
    
    // EARTH
    auto earth = CreateObject("Earth");
    earth->Scale(EARTH_RADIUS * model_scale);
    earth->Rotation(model_rotation);
    earth->Rotate(glm::vec3(30.0f, 0.0f, 0.0f));
    auto earth_mr = earth->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/earth/13902_Earth_v1_l3.obj", IDrawable::ShaderTypes::LIGHT_RECEIVER);
    auto earth_ao = earth->CreateComponent<AstronomicalObject>(EARTH_ROTATION_SPEED);
    earth_ao->Orbit(Orbit(&sun->Position(), EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY));
    
    // MARS
    auto mars = CreateObject("Mars");
    mars->Scale(0.53f * EARTH_RADIUS * model_scale);
    mars->Rotation(model_rotation);
    auto mars_mr = mars->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/mars/13902_Earth_v1_l3.obj", IDrawable::ShaderTypes::LIGHT_RECEIVER);
    auto mars_ao = mars->CreateComponent<AstronomicalObject>(EARTH_ROTATION_SPEED);
    mars_ao->Orbit(Orbit(&sun->Position(), 1.52f * EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY / 1.88f));
    
    // JUPITER
    auto jupiter = CreateObject("Jupiter");
    jupiter->Scale(11.2f * EARTH_RADIUS * model_scale);
    jupiter->Rotation(model_rotation);
    auto jupiter_mr = jupiter->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/jupiter/13902_Earth_v1_l3.obj", IDrawable::ShaderTypes::LIGHT_RECEIVER);
    auto jupiter_ao = jupiter->CreateComponent<AstronomicalObject>(0.37f * EARTH_ROTATION_SPEED);
    jupiter_ao->Orbit(Orbit(&sun->Position(), 5.2f * EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY / 11.86f));
    
    // SATURN
    auto saturn = CreateObject("Saturn");
    saturn->Scale(9.45f * EARTH_RADIUS * model_scale);
    saturn->Rotation(model_rotation);
    auto saturn_mr = saturn->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/saturn/13902_Earth_v1_l3.obj", IDrawable::ShaderTypes::LIGHT_RECEIVER);
    auto saturn_ao = saturn->CreateComponent<AstronomicalObject>(0.42f * EARTH_ROTATION_SPEED);
    saturn_ao->Orbit(Orbit(&sun->Position(), 9.54f * EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY / 29.44f));
    
    // URANUS
    auto uranus = CreateObject("Uranus");
    uranus->Scale(4.0f * EARTH_RADIUS * model_scale);
    uranus->Rotation(model_rotation);
    auto uranus_mr = uranus->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/uranus/13902_Earth_v1_l3.obj", IDrawable::ShaderTypes::LIGHT_RECEIVER);
    auto uranus_ao = uranus->CreateComponent<AstronomicalObject>(0.7f * EARTH_ROTATION_SPEED);
    uranus_ao->Orbit(Orbit(&sun->Position(), 19.19f * EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY / 84.07f));
    
    // NEPTUN
    auto neptun = CreateObject("Neptun");
    neptun->Scale(3.88f * EARTH_RADIUS * model_scale);
    neptun->Rotation(model_rotation);
    auto neptun_mr = neptun->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/neptun/13902_Earth_v1_l3.obj", IDrawable::ShaderTypes::LIGHT_RECEIVER);
    auto neptun_ao = neptun->CreateComponent<AstronomicalObject>(0.67f * EARTH_ROTATION_SPEED);
    neptun_ao->Orbit(Orbit(&sun->Position(), 30.06f * EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY / 164.88f));
}

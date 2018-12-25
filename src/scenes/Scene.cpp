#include "Scene.h"
#include "../components/MeshRenderer/MeshRenderer.h"
#include "../components/AstronomicalObject.h"
#include "../components/test.h"

#define PI 3.14159265358979323846f
#define DOUBLE_PI (PI * 2.0f)

// angular velocity w = 2pi / T
// where T := time in seconds for planet to make full cycle
#define EARTH_RADIUS (1.21f / PI)
#define EARTH_ROTATION_SPEED (360.f / 5.0f) // full rotation takes 5 second
#define EARTH_ORBIT_RADIUS (150.0f / 3.0f)
#define EARTH_ORBIT_ANGULAR_VELOCITY (DOUBLE_PI / (360.0f * 5.0f)) // full orbit takes 5 minutes

void Scene::Initialize() {
    m_DrawManager.Initialize();
    
    glm::vec3 model_scale(1.0f / (976.032f * 2.0f), 1.0f / (976.032f * 2.0f), 1.0f / (986.312f * 2.0f));
    
    // SUN
    Object *sun = new Object("Sun");
    sun->Scale(109.0f * EARTH_RADIUS * model_scale);
    auto sun_mr = sun->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/sun/13902_Earth_v1_l3.obj", IDrawable::ShaderType::LIGHT_SOURCE);
    sun->CreateComponent<AstronomicalObject>(EARTH_ROTATION_SPEED / 1.04f);
    m_ObjectManager.RegisterObject(sun);
    m_DrawManager.RegsiterDrawCall(sun_mr.get());
    
    // MERKURY
    Object *merkury = new Object("Merkury");
    merkury->Scale(0.38f * EARTH_RADIUS * model_scale);
    auto merkury_mr = merkury->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/merkury/13902_Earth_v1_l3.obj", IDrawable::ShaderType::LIGHT_RECEIVER);
    auto merkury_ao = merkury->CreateComponent<AstronomicalObject>(EARTH_ROTATION_SPEED / 58.0f);
    merkury_ao->Orbit(Orbit(&sun->Position(), 0.39f * EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY / 0.24f));
    m_ObjectManager.RegisterObject(merkury);
    m_DrawManager.RegsiterDrawCall(merkury_mr.get());
    
    // WENUS
    Object *wenus = new Object("Wenus");
    wenus->Scale(0.94f * EARTH_RADIUS * model_scale);
    auto wenus_mr = wenus->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/wenus/13902_Earth_v1_l3.obj", IDrawable::ShaderType::LIGHT_RECEIVER);
    auto wenus_ao = wenus->CreateComponent<AstronomicalObject>(EARTH_ROTATION_SPEED / 243.0f);
    wenus_ao->Orbit(Orbit(&sun->Position(), 0.72f * EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY / 0.61f));
    m_ObjectManager.RegisterObject(wenus);
    m_DrawManager.RegsiterDrawCall(wenus_mr.get());
    
    // EARTH
    Object *earth = new Object("Earth");
    earth->Scale(EARTH_RADIUS * model_scale);
    auto earth_mr = earth->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/earth/13902_Earth_v1_l3.obj", IDrawable::ShaderType::LIGHT_RECEIVER);
    auto earth_ao = earth->CreateComponent<AstronomicalObject>(EARTH_ROTATION_SPEED);
    earth_ao->Orbit(Orbit(&sun->Position(), EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY));
    m_ObjectManager.RegisterObject(earth);
    m_DrawManager.RegsiterDrawCall(earth_mr.get());
    
    // MARS
    Object *mars = new Object("Mars");
    mars->Scale(0.53f * EARTH_RADIUS * model_scale);
    auto mars_mr = mars->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/mars/13902_Earth_v1_l3.obj", IDrawable::ShaderType::LIGHT_RECEIVER);
    auto mars_ao = mars->CreateComponent<AstronomicalObject>(EARTH_ROTATION_SPEED);
    mars_ao->Orbit(Orbit(&sun->Position(), 1.52f * EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY / 1.88f));
    m_ObjectManager.RegisterObject(mars);
    m_DrawManager.RegsiterDrawCall(mars_mr.get());
    
    // JUPITER
    Object *jupiter = new Object("Jupiter");
    jupiter->Scale(11.2f * EARTH_RADIUS * model_scale);
    auto jupiter_mr = jupiter->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/jupiter/13902_Earth_v1_l3.obj", IDrawable::ShaderType::LIGHT_RECEIVER);
    auto jupiter_ao = jupiter->CreateComponent<AstronomicalObject>(0.37f * EARTH_ROTATION_SPEED);
    jupiter_ao->Orbit(Orbit(&sun->Position(), 5.2f * EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY / 11.86f));
    m_ObjectManager.RegisterObject(jupiter);
    m_DrawManager.RegsiterDrawCall(jupiter_mr.get());
    
    // SATURN
    Object *saturn = new Object("Saturn");
    saturn->Scale(9.45f * EARTH_RADIUS * model_scale);
    auto saturn_mr = saturn->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/saturn/13902_Earth_v1_l3.obj", IDrawable::ShaderType::LIGHT_RECEIVER);
    auto saturn_ao = saturn->CreateComponent<AstronomicalObject>(0.42f * EARTH_ROTATION_SPEED);
    saturn_ao->Orbit(Orbit(&sun->Position(), 9.54f * EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY / 29.44f));
    m_ObjectManager.RegisterObject(saturn);
    m_DrawManager.RegsiterDrawCall(saturn_mr.get());
    
    // URANUS
    Object *uranus = new Object("Uranus");
    uranus->Scale(4.0f * EARTH_RADIUS * model_scale);
    auto uranus_mr = uranus->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/uranus/13902_Earth_v1_l3.obj", IDrawable::ShaderType::LIGHT_RECEIVER);
    auto uranus_ao = uranus->CreateComponent<AstronomicalObject>(0.7f * EARTH_ROTATION_SPEED);
    uranus_ao->Orbit(Orbit(&sun->Position(), 19.19f * EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY / 84.07f));
    m_ObjectManager.RegisterObject(uranus);
    m_DrawManager.RegsiterDrawCall(uranus_mr.get());
    
    // NEPTUN
    Object *neptun = new Object("Neptun");
    neptun->Scale(3.88f * EARTH_RADIUS * model_scale);
    auto neptun_mr = neptun->CreateComponent<MeshRenderer>("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/neptun/13902_Earth_v1_l3.obj", IDrawable::ShaderType::LIGHT_RECEIVER);
    auto neptun_ao = neptun->CreateComponent<AstronomicalObject>(0.67f * EARTH_ROTATION_SPEED);
    neptun_ao->Orbit(Orbit(&sun->Position(), 30.06f * EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY / 164.88f));
    m_ObjectManager.RegisterObject(neptun);
    m_DrawManager.RegsiterDrawCall(neptun_mr.get());
}

void Scene::Run() {
    m_ObjectManager.UpdateObjects();
    m_DrawManager.CallDraws();
}

void Scene::PostRun() {
    m_ObjectManager.DestroyObjects();
}

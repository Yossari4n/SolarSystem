#include "Scene.h"
#include "../components/MeshRenderer/MeshRenderer.h"
#include "../components/AstronomicalObject.h"

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
    MeshRenderer *sunMeshRenderer = new MeshRenderer("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/sun/13902_Earth_v1_l3.obj", IDrawable::ShaderType::LIGHT_SOURCE);
    AstronomicalObject *sunAstronomicalObject = new AstronomicalObject(EARTH_ROTATION_SPEED / 1.04f);
    sun->AddComponent(sunMeshRenderer);
    sun->AddComponent(sunAstronomicalObject);
    m_ObjectManager.RegisterObject(sun);
    m_DrawManager.RegsiterDrawCall(sunMeshRenderer);
    
    // MERKURY
    Object *merkury = new Object("Merkury");
    merkury->Scale(0.38f * EARTH_RADIUS * model_scale);
    MeshRenderer *merkuryMeshRenderer = new MeshRenderer("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/merkury/13902_Earth_v1_l3.obj", IDrawable::ShaderType::LIGHT_RECEIVER);
    AstronomicalObject *merkuryAstronomicalObject = new AstronomicalObject(EARTH_ROTATION_SPEED / 58.0f);
    Orbit *merkuryOrbit = new Orbit(&sun->Position(), 0.39f * EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY / 0.24f);
    merkuryAstronomicalObject->Orbit(*merkuryOrbit);
    merkury->AddComponent(merkuryMeshRenderer);
    merkury->AddComponent(merkuryAstronomicalObject);
    m_ObjectManager.RegisterObject(merkury);
    m_DrawManager.RegsiterDrawCall(merkuryMeshRenderer);
    
    // WENUS
    Object *wenus = new Object("Wenus");
    wenus->Scale(0.94f * EARTH_RADIUS * model_scale);
    MeshRenderer *wenusMeshRenderer = new MeshRenderer("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/wenus/13902_Earth_v1_l3.obj", IDrawable::ShaderType::LIGHT_RECEIVER);
    AstronomicalObject *wenusAstronomicalObject = new AstronomicalObject(EARTH_ROTATION_SPEED / 243.0f);
    Orbit *wenusOrbit = new Orbit(&sun->Position(), 0.72f * EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY / 0.61f);
    wenusAstronomicalObject->Orbit(*wenusOrbit);
    wenus->AddComponent(wenusMeshRenderer);
    wenus->AddComponent(wenusAstronomicalObject);
    m_ObjectManager.RegisterObject(wenus);
    m_DrawManager.RegsiterDrawCall(wenusMeshRenderer);
    
    // EARTH
    Object *earth = new Object("Earth");
    earth->Scale(EARTH_RADIUS * model_scale);
    MeshRenderer *earthMeshRenderer = new MeshRenderer("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/earth/13902_Earth_v1_l3.obj", IDrawable::ShaderType::LIGHT_RECEIVER);
    AstronomicalObject *eartAstronomicalObject = new AstronomicalObject(EARTH_ROTATION_SPEED);
    Orbit *earthOrbit = new Orbit(&sun->Position(), EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY);
    eartAstronomicalObject->Orbit(*earthOrbit);
    earth->AddComponent(earthMeshRenderer);
    earth->AddComponent(eartAstronomicalObject);
    m_ObjectManager.RegisterObject(earth);
    m_DrawManager.RegsiterDrawCall(earthMeshRenderer);
    
    // MARS
    Object *mars = new Object("Mars");
    mars->Scale(0.53f * EARTH_RADIUS * model_scale);
    MeshRenderer *marsMeshRenderer = new MeshRenderer("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/mars/13902_Earth_v1_l3.obj", IDrawable::ShaderType::LIGHT_RECEIVER);
    AstronomicalObject *marsAstronomicalObject = new AstronomicalObject(EARTH_ROTATION_SPEED);
    Orbit *marsOrbit = new Orbit(&sun->Position(), 1.52f * EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY / 1.88f);
    marsAstronomicalObject->Orbit(*marsOrbit);
    mars->AddComponent(marsMeshRenderer);
    mars->AddComponent(marsAstronomicalObject);
    m_ObjectManager.RegisterObject(mars);
    m_DrawManager.RegsiterDrawCall(marsMeshRenderer);
    
    // JUPITER
    Object *jupiter = new Object("Jupiter");
    jupiter->Scale(11.2f * EARTH_RADIUS * model_scale);
    MeshRenderer *jupiterMeshRenderer = new MeshRenderer("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/jupiter/13902_Earth_v1_l3.obj", IDrawable::ShaderType::LIGHT_RECEIVER);
    AstronomicalObject *jupiterAstronomicalObject = new AstronomicalObject(0.37f * EARTH_ROTATION_SPEED);
    Orbit *jupiterOrbit = new Orbit(&sun->Position(), 5.2f * EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY / 11.86f);
    jupiterAstronomicalObject->Orbit(*jupiterOrbit);
    jupiter->AddComponent(jupiterMeshRenderer);
    jupiter->AddComponent(jupiterAstronomicalObject);
    m_ObjectManager.RegisterObject(jupiter);
    m_DrawManager.RegsiterDrawCall(jupiterMeshRenderer);
    
    // SATURN
    Object *saturn = new Object("Saturn");
    saturn->Scale(9.45f * EARTH_RADIUS * model_scale);
    MeshRenderer *saturnMeshRenderer = new MeshRenderer("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/saturn/13902_Earth_v1_l3.obj", IDrawable::ShaderType::LIGHT_RECEIVER);
    AstronomicalObject *saturnAstronomicalObject = new AstronomicalObject(0.42f * EARTH_ROTATION_SPEED);
    Orbit *saturnOrbit = new Orbit(&sun->Position(), 9.54f * EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY / 29.44f);
    saturnAstronomicalObject->Orbit(*saturnOrbit);
    saturn->AddComponent(saturnMeshRenderer);
    saturn->AddComponent(saturnAstronomicalObject);
    m_ObjectManager.RegisterObject(saturn);
    m_DrawManager.RegsiterDrawCall(saturnMeshRenderer);
    
    // URANUS
    Object *uranus = new Object("Uranus");
    uranus->Scale(4.0f * EARTH_RADIUS * model_scale);
    MeshRenderer *uranusMeshRenderer = new MeshRenderer("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/uranus/13902_Earth_v1_l3.obj", IDrawable::ShaderType::LIGHT_RECEIVER);
    AstronomicalObject *uranusAstronomicalObject = new AstronomicalObject(0.7f * EARTH_ROTATION_SPEED);
    Orbit *uranusOrbit = new Orbit(&sun->Position(), 19.19f * EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY / 84.07f);
    uranusAstronomicalObject->Orbit(*uranusOrbit);
    uranus->AddComponent(uranusMeshRenderer);
    uranus->AddComponent(uranusAstronomicalObject);
    m_ObjectManager.RegisterObject(uranus);
    m_DrawManager.RegsiterDrawCall(uranusMeshRenderer);
    
    // NEPTUN
    Object *neptun = new Object("Neptun");
    neptun->Scale(3.88f * EARTH_RADIUS * model_scale);
    MeshRenderer *neptunMeshRenderer = new MeshRenderer("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/models/neptun/13902_Earth_v1_l3.obj", IDrawable::ShaderType::LIGHT_RECEIVER);
    AstronomicalObject *neptunAstronomicalObject = new AstronomicalObject(0.67f * EARTH_ROTATION_SPEED);
    Orbit *neptunOrbit = new Orbit(&sun->Position(), 30.06f * EARTH_ORBIT_RADIUS, -EARTH_ORBIT_ANGULAR_VELOCITY / 164.88f);
    neptunAstronomicalObject->Orbit(*neptunOrbit);
    neptun->AddComponent(neptunMeshRenderer);
    neptun->AddComponent(neptunAstronomicalObject);
    m_ObjectManager.RegisterObject(neptun);
    m_DrawManager.RegsiterDrawCall(neptunMeshRenderer);
}

void Scene::Run() {
    m_ObjectManager.UpdateObjects();
    m_DrawManager.CallDraws();
}

void Scene::PostRun() {
    m_ObjectManager.DestroyObjects();
}

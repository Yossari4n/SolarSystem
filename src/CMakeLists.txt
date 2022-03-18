set(SOURCES
	main.cpp

	cbs/Object.cpp
	cbs/ObjectManager.cpp
	cbs/Transform.cpp
	cbs/components/AstronomicalObject.cpp
	cbs/components/Camera.cpp
	cbs/components/FirstPersonController.cpp
	cbs/components/Manager.cpp
	cbs/components/PointLight.cpp
	cbs/components/Tail.cpp
	cbs/components/ThirdPersonController.cpp
	cbs/components/MeshRenderer/Mesh.cpp
	cbs/components/MeshRenderer/MeshRenderer.cpp

	rendering/Cubemap.cpp
	rendering/DrawManager.cpp
	rendering/IDrawable.cpp
	rendering/Line.cpp
	rendering/ShaderProgram.cpp

	scenes/IScene.cpp
	scenes/MainScene.cpp

	utilities/Input.cpp
	utilities/Time.cpp
	utilities/Window.cpp
)

set(HEADERS
	cbs/Object.h
	cbs/ObjectManager.h
	cbs/Transform.h
	cbs/components/AstronomicalObject.h
	cbs/components/Camera.h
	cbs/components/FirstPersonController.h
	cbs/components/IComponent.h
	cbs/components/Manager.h
	cbs/components/PointLight.h
	cbs/components/Tail.h
	cbs/components/ThirdPersonController.h
	cbs/components/MeshRenderer/Mesh.h
	cbs/components/MeshRenderer/MeshRenderer.h

	rendering/Cubemap.h
	rendering/DrawManager.h
	rendering/IDrawable.h
	rendering/ILightSource.h
	rendering/Line.h
	rendering/ShaderProgram.h

	scenes/IScene.h
	scenes/MainScene.h

	utilities/Input.h
	utilities/Time.h
	utilities/Window.h
)

add_executable(SolarSystem ${SOURCES} ${HEADERS})
target_link_libraries(SolarSystem ${CONAN_LIBS})
target_include_directories(SolarSystem PUBLIC ${PROJECT_SOURCE_DIR}/src)
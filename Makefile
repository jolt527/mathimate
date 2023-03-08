EXECUTABLE = mathimate

IMGUI_DIRECTORY = imgui
IMGUI_SOURCE_FILES = \
	${IMGUI_DIRECTORY}/imgui_demo.cpp \
	${IMGUI_DIRECTORY}/imgui_draw.cpp \
	${IMGUI_DIRECTORY}/imgui_tables.cpp \
	${IMGUI_DIRECTORY}/imgui_widgets.cpp \
	${IMGUI_DIRECTORY}/imgui.cpp \
	${IMGUI_DIRECTORY}/imgui_impl_opengl3.cpp \
	${IMGUI_DIRECTORY}/imgui_impl_glfw.cpp

INCLUDE_PATHS = \
	-I/opt/homebrew/opt/glfw/include \
	-I/opt/homebrew/opt/glew/include \
	-I/opt/homebrew/opt/ffmpeg/include \
	-I${IMGUI_DIRECTORY}

LIBRARY_PATHS = \
	-L/opt/homebrew/opt/glfw/lib \
	-L/opt/homebrew/opt/glew/lib \
	-L/opt/homebrew/opt/ffmpeg/lib

LIBRARIES = -framework OpenGL -lglfw -lglew -lavcodec -lavutil

SOURCE_FILES = \
	main.cpp \
	ShaderProgram.cpp \
	Triangle.cpp \
	PropertyIntervalManager.cpp

all:
	g++ -o ${EXECUTABLE} -std=c++11 ${IMGUI_SOURCE_FILES} ${SOURCE_FILES} ${INCLUDE_PATHS} ${LIBRARY_PATHS} ${LIBRARIES}

clean:
	rm -rf ${EXECUTABLE}

glfw_include = C:\Libraries\GLFW\include
glfw_lib = C:\Libraries\GLFW\lib

glad_include = C:\Libraries\GLAD\include
glad_src =  C:\Libraries\GLAD\src\glad.c

stb_include = C:\Libraries\STB\include
stb_src = C:\Libraries\STB\src\stb.cpp

glm_include = C:\Libraries\GLM\include

json_include = C:\Libraries\JSON\include

local_include = ./Header
local_src = 



################################################################################################################################################################################################################################


CXX = g++
CPP = ./Source/main.cpp
TARGET = ./Bin/main


OBJECTS = $(CPP) $(glad_src) $(stb_src) $(local_src)
INCLUDES = -I$(glfw_include) -I$(glad_include) -I$(stb_include) -I$(glm_include) -I$(json_include) -I$(local_include) 
LIBRARIES = -L$(glfw_lib)


C_FLAGS = $(INCLUDES)
LD_FLAGS = $(LIBRARIES) -lglfw3 -lopengl32 -lglu32 -lgdi32


$(TARGET): $(CPP) # Final Output
	$(CXX) $(OBJECTS) $(C_FLAGS) $(LD_FLAGS) -o$(TARGET)
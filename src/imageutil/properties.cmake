set(MODULE_NAME imageutil)
set(MODULE_PATH ${SRC}/imageutil)

set(MODULE_SOURCES
	pixel.cpp
	image.cpp
	spectral_image.cpp
	spectre.cpp
)

set(MODULE_LIBS
	glm stb
)
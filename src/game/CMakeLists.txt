add_definitions(-DGAME_LIBRARY)

file(GLOB MARSHMALLOW_GAME_SRCS *.cpp)

set(MARSHMALLOW_GAME_LIBS
	marshmallow_core
	marshmallow_event
	marshmallow_graphics
	marshmallow_math)

# BOX2D
if (MARSHMALLOW_WITH_BOX2D)
	include(Box2D)
	file(GLOB MARSHMALLOW_GAME_BOX2D_SRCS box2d/*.cpp)
endif()

# TINYXML
include_directories(${TINYXML_INCLUDE_DIR})
set(MARSHMALLOW_GAME_LIBS ${MARSHMALLOW_GAME_LIBS} ${TINYXML_LIBRARIES})

include(EASTL)

add_library(marshmallow_game
	${MARSHMALLOW_GAME_SRCS}
	${MARSHMALLOW_GAME_BOX2D_SRCS}
)

target_link_libraries(marshmallow_game ${MARSHMALLOW_GAME_LIBS})

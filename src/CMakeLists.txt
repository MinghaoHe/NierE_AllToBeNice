PROJECT(NierE_AllToBeNice)

INCLUDE_DIRECTORIES(
    ${PROJECT_ROOT_DIR}
    ${SOURCE_ROOT_DIR}
    ${THIRD_PARTY_DIR}
    ${THIRD_PARTY_DIR}/freetype/include
    ${THIRD_PARTY_DIR}/glm
    ${THIRD_PARTY_DIR}/json/include
    ${THIRD_PARTY_DIR}/SDL/include
    ${THIRD_PARTY_DIR}/SDL_mixer/include)

SET(LIBS freetype SDL3::SDL3 SDL3_mixer::SDL3_mixer tinyobjloader)

LINK_LIBRARIES(${LIBS})

SET(PROJECT_SOURCE_FILES
    # project
    main.cc

    # engine
    atn/engine.h
    atn/engine.cc

    atn/define.h

    # audio
    atn/engine/audio/component.h
    atn/engine/audio/component.cc
    atn/engine/audio/system.h
    atn/engine/audio/system.cc

    # canvas
    atn/engine/canvas/sdl_canvas.h
    atn/engine/canvas/sdl_canvas.cc

    atn/engine/canvas/define.h

    # ecs
    atn/engine/ecs/entity.h
    atn/engine/ecs/entity.cc
    atn/engine/ecs/component.h
    atn/engine/ecs/component.cc
    atn/engine/ecs/system.h
    atn/engine/ecs/system.cc

    atn/engine/ecs/define.h

    # logic
    atn/engine/logic/component.h
    atn/engine/logic/component.cc
    atn/engine/logic/system.h
    atn/engine/logic/system.cc

    # physics
    atn/engine/physics/component.h
    atn/engine/physics/component.cc
    atn/engine/physics/system.h
    atn/engine/physics/system.cc

    atn/engine/physics/define.h

    # world
    atn/engine/world/prime_player.cc
    atn/engine/world/prime_player.h
    atn/engine/world/scene.h
    atn/engine/world/scene.cc
    atn/engine/world/world.h
    atn/engine/world/world.cc

    # render
    atn/engine/render/component.h
    atn/engine/render/component.cc
    atn/engine/render/system.h
    atn/engine/render/system.cc

    atn/engine/render/canvas_frame.h
    atn/engine/render/canvas_frame.cc
    atn/engine/render/define.h
    atn/engine/render/framebuffer.h
    atn/engine/render/framebuffer.cc
    atn/engine/render/object.h
    atn/engine/render/object.cc
    atn/engine/render/shader.h
    atn/engine/render/shader.cc
    atn/engine/render/pass.h
    atn/engine/render/pass.cc
    atn/engine/render/text.h
    atn/engine/render/text.cc

    # game
    atn/game/game.h

    # games202
    atn/game/games202/games202.h

    # shadow
    atn/game/games202/shadow/shadow.h
    atn/game/games202/shadow/tag.h

    atn/game/games202/shadow/marry.h
    atn/game/games202/shadow/marry.cc
    atn/game/games202/shadow/marry/logic.h
    atn/game/games202/shadow/marry/logic.cc
    atn/game/games202/shadow/marry/render.h
    atn/game/games202/shadow/marry/render.cc

    # utils
    atn/utils/id_generator.h
    atn/utils/id_generator.cc
    atn/utils/random.h
    atn/utils/random.cc

    # 3rdparty
    ${THIRD_PARTY_DIR}/glad/glad.c)

SET(PROJECT_SHADER_FILES
    atn/engine/render/shader/canvas.vert
    atn/engine/render/shader/canvas.frag
    atn/engine/render/shader/canvas_mixer.vert
    atn/engine/render/shader/canvas_mixer.frag
    atn/engine/render/shader/mesh.vert
    atn/engine/render/shader/mesh.frag)

ADD_EXECUTABLE(NierE_AllToBeNice ${PROJECT_SOURCE_FILES} ${PROJECT_SHADER_FILES})
SOURCE_GROUP(TREE ${PROJECT_ROOT_DIR} FILES ${PROJECT_SOURCE_FILES} ${PROJECT_SHADER_FILES})

IF(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    ADD_CUSTOM_COMMAND(
            TARGET NierE_AllToBeNice
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_ROOT_DIR}/atn/engine/render/shader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res/shader)
    ADD_CUSTOM_COMMAND(
            TARGET NierE_AllToBeNice
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_ROOT_DIR}/res ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res)
ELSE()
    ADD_CUSTOM_COMMAND(
            TARGET NierE_AllToBeNice
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_ROOT_DIR}/atn/engine/render/shader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res/shader)
    ADD_CUSTOM_COMMAND(
            TARGET NierE_AllToBeNice
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_ROOT_DIR}/res ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res)
ENDIF()

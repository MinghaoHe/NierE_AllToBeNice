PROJECT(NierE_AllToBeNice)

IF(${CMAKE_BUILD_NIER_E_AIRPLANE})
ADD_DEFINITIONS(
  -DNIER_E_AIRPLANE
)
ENDIF()

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

SET(PROJECT_ENGINE_SOURCE_FILES
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
    atn/engine/render/pass.h
    atn/engine/render/pass.cc
    atn/engine/render/pass/bloom.h
    atn/engine/render/pass/bloom.cc
    atn/engine/render/pass/fade.h
    atn/engine/render/pass/fade.cc
    atn/engine/render/pass/normal.h
    atn/engine/render/pass/normal.cc
    atn/engine/render/pass/particles.h
    atn/engine/render/pass/particles.cc
    atn/engine/render/pass/text.h
    atn/engine/render/pass/text.cc
    atn/engine/render/shader.h
    atn/engine/render/shader.cc
    atn/engine/render/text.h
    atn/engine/render/text.cc

    # utils
    atn/utils/id_generator.h
    atn/utils/id_generator.cc
    atn/utils/random.h
    atn/utils/random.cc

    # 3rdparty
    ${THIRD_PARTY_DIR}/glad/glad.c)

IF(${CMAKE_BUILD_NIER_E_AIRPLANE})
SET(PROJECT_GAME_SOURCE_FILES
    # game
    atn/game/game.h
    atn/game/define.h

    # nier_e_airplane
    atn/game/nier_e_airplane/nier_e_airplane.h
    atn/game/nier_e_airplane/nier_e_airplane.cc
    atn/game/nier_e_airplane/game_control.h
    atn/game/nier_e_airplane/game_control.cc
    atn/game/nier_e_airplane/define.h
    atn/game/nier_e_airplane/enemy.h
    atn/game/nier_e_airplane/enemy.cc
    atn/game/nier_e_airplane/enemy/audio.h
    atn/game/nier_e_airplane/enemy/audio.cc
    atn/game/nier_e_airplane/enemy/data.h
    atn/game/nier_e_airplane/enemy/logic.h
    atn/game/nier_e_airplane/enemy/logic.cc
    atn/game/nier_e_airplane/enemy/logic/shoot.h
    atn/game/nier_e_airplane/enemy/logic/shoot.cc
    atn/game/nier_e_airplane/enemy/logic/track.h
    atn/game/nier_e_airplane/enemy/logic/track.cc
    atn/game/nier_e_airplane/enemy/render.h
    atn/game/nier_e_airplane/enemy/render.cc

    atn/game/nier_e_airplane/enemy_bullet.h
    atn/game/nier_e_airplane/enemy_bullet.cc
    atn/game/nier_e_airplane/enemy_bullet/data.h
    atn/game/nier_e_airplane/enemy_bullet/logic.h
    atn/game/nier_e_airplane/enemy_bullet/logic.cc
    atn/game/nier_e_airplane/enemy_bullet/render.h
    atn/game/nier_e_airplane/enemy_bullet/render.cc

    atn/game/nier_e_airplane/enemy_hit.h
    atn/game/nier_e_airplane/enemy_hit.cc
    atn/game/nier_e_airplane/enemy_hit/data.h
    atn/game/nier_e_airplane/enemy_hit/logic.h
    atn/game/nier_e_airplane/enemy_hit/logic.cc
    atn/game/nier_e_airplane/enemy_hit/render.h
    atn/game/nier_e_airplane/enemy_hit/render.cc

    atn/game/nier_e_airplane/explosion.h
    atn/game/nier_e_airplane/explosion.cc
    atn/game/nier_e_airplane/explosion/data.h
    atn/game/nier_e_airplane/explosion/logic.h
    atn/game/nier_e_airplane/explosion/logic.cc
    atn/game/nier_e_airplane/explosion/render.h
    atn/game/nier_e_airplane/explosion/render.cc

    atn/game/nier_e_airplane/pod.h
    atn/game/nier_e_airplane/pod.cc
    atn/game/nier_e_airplane/pod/audio.h
    atn/game/nier_e_airplane/pod/audio.cc
    atn/game/nier_e_airplane/pod/data.h
    atn/game/nier_e_airplane/pod/logic.h
    atn/game/nier_e_airplane/pod/logic.cc
    atn/game/nier_e_airplane/pod/render.h
    atn/game/nier_e_airplane/pod/render.cc

    atn/game/nier_e_airplane/pod_bullet.h
    atn/game/nier_e_airplane/pod_bullet.cc
    atn/game/nier_e_airplane/pod_bullet/data.h
    atn/game/nier_e_airplane/pod_bullet/logic.h
    atn/game/nier_e_airplane/pod_bullet/logic.cc
    atn/game/nier_e_airplane/pod_bullet/render.h
    atn/game/nier_e_airplane/pod_bullet/render.cc

    atn/game/nier_e_airplane/pod_trail.h
    atn/game/nier_e_airplane/pod_trail.cc
    atn/game/nier_e_airplane/pod_trail/data.h
    atn/game/nier_e_airplane/pod_trail/logic.h
    atn/game/nier_e_airplane/pod_trail/logic.cc
    atn/game/nier_e_airplane/pod_trail/render.h
    atn/game/nier_e_airplane/pod_trail/render.cc
)
ENDIF()

SET(PROJECT_SHADER_FILES
    atn/engine/render/shader/bloom_pass.vert
    atn/engine/render/shader/bloom_pass.frag
    atn/engine/render/shader/canvas.vert
    atn/engine/render/shader/canvas.frag
    atn/engine/render/shader/canvas_mixer.vert
    atn/engine/render/shader/canvas_mixer.frag
    atn/engine/render/shader/fade_pass.vert
    atn/engine/render/shader/fade_pass.frag
    atn/engine/render/shader/normal_pass.vert
    atn/engine/render/shader/normal_pass.frag
    atn/engine/render/shader/particles_pass.vert
    atn/engine/render/shader/particles_pass.frag
    atn/engine/render/shader/text_pass.vert
    atn/engine/render/shader/text_pass.frag)

ADD_EXECUTABLE(NierE_AllToBeNice ${PROJECT_ENGINE_SOURCE_FILES} ${PROJECT_GAME_SOURCE_FILES} ${PROJECT_SHADER_FILES})
SOURCE_GROUP(TREE ${PROJECT_ROOT_DIR} FILES ${PROJECT_ENGINE_SOURCE_FILES} ${PROJECT_GAME_SOURCE_FILES} ${PROJECT_SHADER_FILES})

IF(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    ADD_CUSTOM_COMMAND(
            TARGET NierE_AllToBeNice
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_ROOT_DIR}/atn/engine/render/shader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res/shader)
    ADD_CUSTOM_COMMAND(
            TARGET NierE_AllToBeNice
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_ROOT_DIR}/res ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res)
    IF(${CMAKE_BUILD_NIER_E_AIRPLANE})
        ADD_CUSTOM_COMMAND(
                TARGET NierE_AllToBeNice
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_ROOT_DIR}/atn/game/nier_e_airplane/conf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/conf)
    ENDIF()
ELSE()
    ADD_CUSTOM_COMMAND(
            TARGET NierE_AllToBeNice
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_ROOT_DIR}/atn/engine/render/shader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res/shader)
    ADD_CUSTOM_COMMAND(
            TARGET NierE_AllToBeNice
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_ROOT_DIR}/res ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res)
    IF(${CMAKE_BUILD_NIER_E_AIRPLANE})
        ADD_CUSTOM_COMMAND(
                TARGET NierE_AllToBeNice
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_ROOT_DIR}/atn/game/nier_e_airplane/conf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/conf)
    ENDIF()
ENDIF()

SET (LIBRARY_NAME basic)

PROJECT (${LIBRARY_NAME} CXX)

SET (SOURCES
    aabb
    camera
    color
    hittable
    material
    onb
    pdf
    perlin
    ray
    texture
    utils
    vec
)

ADD_LIBRARY (${LIBRARY_NAME} STATIC
    ${SOURCES}
)

TARGET_INCLUDE_DIRECTORIES (${LIBRARY_NAME} PRIVATE
    ../../include/${LIBRARY_NAME}
)

TARGET_INCLUDE_DIRECTORIES (${LIBRARY_NAME} PUBLIC
    ../../include/${LIBRARY_NAME}
)

TARGET_COMPILE_FEATURES (${LIBRARY_NAME} PUBLIC
    cxx_std_11
)
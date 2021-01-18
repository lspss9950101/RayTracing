SET (LIBRARY_NAME material)

PROJECT (${LIBRARY_NAME} CXX)

SET (SOURCES
    dielectric
    diffuse_light
    isotropic
    lambertian
    metal
)

ADD_LIBRARY (${LIBRARY_NAME} STATIC
    ${SOURCES}
)

TARGET_LINK_LIBRARIES (${LIBRARY_NAME} PUBLIC
    basic
    texture
)

TARGET_INCLUDE_DIRECTORIES (${LIBRARY_NAME} PRIVATE
    ../../include/${LIBRARY_NAME}
)

TARGET_INCLUDE_DIRECTORIES (${LIBRARY_NAME} PUBLIC
    ../../include
)

TARGET_COMPILE_FEATURES (${LIBRARY_NAME} PUBLIC
    cxx_std_11
)
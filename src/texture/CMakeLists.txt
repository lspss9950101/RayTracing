SET (LIBRARY_NAME texture)

PROJECT (${LIBRARY_NAME} CXX)

SET (SOURCES
    checker_texture
    noise_texture
    solid_color
)

ADD_LIBRARY (${LIBRARY_NAME} STATIC
    ${SOURCES}
)

TARGET_LINK_LIBRARIES (${LIBRARY_NAME} PUBLIC
    basic
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
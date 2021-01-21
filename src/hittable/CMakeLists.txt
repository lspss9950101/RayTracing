SET (LIBRARY_NAME hittable)

PROJECT (${LIBRARY_NAME} CXX)

SET (SOURCES
    box
    bvh
    constant_medium
    flip_face
    hittable_list
    hollow_sphere
    moving_sphere
    rect
    rotation
    sphere
    translation
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
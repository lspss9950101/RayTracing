SET (LIBRARIES 
    basic
    hittable
    material
    texture
    thread_pool
)

FOREACH (LIB ${LIBRARIES})
    ADD_SUBDIRECTORY (${LIB})
ENDFOREACH (LIB)
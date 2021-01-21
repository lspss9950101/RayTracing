SET (LIBRARIES 
    basic
    hittable
    material
    pdf
    texture
    thread_pool
)

FOREACH (LIB ${LIBRARIES})
    ADD_SUBDIRECTORY (${LIB})
ENDFOREACH (LIB)
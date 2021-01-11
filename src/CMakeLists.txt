SET (LIBRARIES 
    basic
    hittable
    material
    thread_pool
)

FOREACH (LIB ${LIBRARIES})
    ADD_SUBDIRECTORY (${LIB})
ENDFOREACH (LIB)
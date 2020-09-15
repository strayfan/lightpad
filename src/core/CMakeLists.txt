set(core_PUB
    api.h
    global.h
    itextdocument.h
    itextstream.h
    rbtree.h
    )

generate_public_header(core
    ${core_PUB}
    )

add_library(core SHARED
    ${core_PUB}
    api.cpp
    textdocument.cpp
    textdocument.h
    textstream.cpp
    textstream.h
    textbuffer.h
    piecetable.cpp
    piecetable.h
    rbtree.h
    )

set(core_PUB
    global.h
    itextdocument.h
    itextstream.h
    rbtree.h
    )

generate_public_header(core
    ${core_PUB}
    )

add_library(core STATIC
    ${core_PUB}
    textdocument.cpp
    textdocument.h
    textstream.cpp
    textstream.h
    textbuffer.h
    piecetable.cpp
    piecetable.h
    rbtree.h
    )

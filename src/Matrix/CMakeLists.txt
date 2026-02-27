add_library(Matrix)

target_sources(Matrix
    PRIVATE
        matrix.cpp
    
    PUBLIC
        FILE_SET HEADERS
        FILES
            matrix.hpp
)

add_library(DiagThree)

target_sources(DiagThree
    PRIVATE
        diagthree.cpp
    
    PUBLIC
        FILE_SET HEADERS
        FILES
            diagthree.hpp
)

cmake_minimum_required(VERSION 4.2.3)

project(kfsoleq)

# Options
option(DIAGTHREE_BUILD "Build DiagThree" ON)
option(DIAGTHREE_TESTS_BUILD "Build DiagThree tests" ON)


# Applying options
if (DIAGTHREE_BUILD)
    message("Adding DiagThree Source files...")
    add_subdirectory(src/DiagThree)
    message("Adding DiagThree Source files DONE!")
    
    if (DIAGTHREE_TESTS_BUILD)
        message("Adding DiagThree Test files...")
        add_subdirectory(tests/DiagThreeTests)
        message("Adding DiagThree Test files DONE!")
        message("[31;1mTHE MAIN TEST IS 6th ONE, YOU CAN TRY TO SOLVE YOUR OWN TRIDIAGONAL SYSTEM OF LINEAR EQUATIONS WITH IT[0m")
    endif()
endif()

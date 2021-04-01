find_package(GTest)
include(CodeCoverage)

if (GTest_FOUND)

    # gather all *.cc files
    file(GLOB TEST_SRC *.cc)

    # if you need to copy from source to build folder do it here
    # configure_file(SRC DST COPYONLY)

    # Dont create a unit_test if not tests given
    ADD_EXECUTABLE(UNIT_TEST ${TEST_SRC})

    target_compile_features(UNIT_TEST PRIVATE
        cxx_std_17
    )
    TARGET_COMPILE_OPTIONS(UNIT_TEST PRIVATE
        "-fprofile-arcs"
        "-ftest-coverage"
        "-fPIC"
    )

    TARGET_LINK_LIBRARIES(
        UNIT_TEST
        SOURCE_LIB
        GTest::GTest
        gcov
    )


    setup_target_for_coverage_gcovr_html(
        NAME coverage
        EXECUTABLE UNIT_TEST
        EXCLUDE test/*
        DEPENDENCIES UNIT_TEST
    )


    add_test(
        NAME test_unitaire
        COMMAND UNIT_TEST
    )
    add_custom_target(check
        COMMAND ${CMAKE_CTEST_COMMAND}
        DEPENDS UNIT_TEST
    )
endif()

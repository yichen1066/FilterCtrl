set(SRCS
    app.cpp
    app.h
    main_frame.h
    main_frame.cpp
    filter_ctrl.cpp
    filter_ctrl.h
    resource_id.h
    )

set(TARGET_NAME FilterCtrl)

add_executable(${TARGET_NAME} WIN32 MACOSX_BUNDLE ${SRCS})
if(WIN32)
    target_link_libraries(${TARGET_NAME} gdiplus)
endif()
target_link_libraries(${TARGET_NAME} ${wxWidgets_LIBRARIES})
set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_NAME FilterCtrl)

# Unit test.
if(JIL_ENABLE_TEST)
    set(UT_SRCS
        )
    set(UT_TARGET_NAME app_unittest)
    add_executable(${UT_TARGET_NAME} ${UT_SRCS})
    target_link_libraries(${UT_TARGET_NAME} ${wxWidgets_LIBRARIES} ${GTEST_BOTH_LIBRARIES})
endif()

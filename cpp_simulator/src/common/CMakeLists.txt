SET(COMMON_SRC
        ffModule/convertible.cpp
        ffModule/loadSettings.cpp
        json/jsoncpp.cpp
)

ADD_LIBRARY(common STATIC ${COMMON_SRC})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/common)

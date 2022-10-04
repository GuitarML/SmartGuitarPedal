cmake_minimum_required(VERSION 3.15)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.12" CACHE STRING "Minimum OS X deployment target")
project(SmartPedal VERSION 1.5.0)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(modules)
include_directories(modules)

#juce_set_aax_sdk_path(C:/SDKs/AAX_SDK/)

set(JUCE_FORMATS AU VST3)

# Build LV2 only on Linux
if(UNIX AND NOT APPLE)
    message(STATUS "Building LV2 plugin format")
    list(APPEND JUCE_FORMATS LV2)
endif()

# Build AAX if SDK target exists
if(TARGET juce_aax_sdk)
    message(STATUS "Building AAX plugin format")
    list(APPEND JUCE_FORMATS AAX)
endif()

juce_add_plugin(SmartPedal
    COMPANY_NAME GuitarML
    PLUGIN_MANUFACTURER_CODE GtML
    PLUGIN_CODE Sgp3 
    FORMATS ${JUCE_FORMATS}
    ProductName "SmartPedal"
    LV2_URI https://github.com/GuitarML/SmartPedal
    ICON_BIG resources/logo.png
    MICROPHONE_PERMISSION_ENABLED TRUE
)

# create JUCE header
juce_generate_juce_header(SmartPedal)

# add sources
add_subdirectory(src)
include_directories(src)
add_subdirectory(resources)

target_compile_definitions(SmartPedal
    PUBLIC
    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_REPORT_APP_USAGE=0
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_MODAL_LOOPS_PERMITTED=1
)

target_link_libraries(SmartPedal PUBLIC
    juce_plugin_modules
)


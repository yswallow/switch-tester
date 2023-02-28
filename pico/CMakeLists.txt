cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(switch_tester)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(switch_tester)

target_sources(switch_tester PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/main.c
        ${CMAKE_CURRENT_LIST_DIR}/usb_descriptors.c
        )

# Make sure TinyUSB can find tusb_config.h
target_include_directories(switch_tester PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

# In addition to pico_stdlib required for common PicoSDK functionality, add dependency on tinyusb_device
# for TinyUSB device support and tinyusb_board for the additional board support library used by the example
target_link_libraries(switch_tester PUBLIC pico_stdlib tinyusb_device)

pico_add_extra_outputs(switch_tester)

# add url via pico_set_program_url
#example_auto_set_url(switch_tester)

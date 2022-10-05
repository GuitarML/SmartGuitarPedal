juce_add_binary_data(BinaryData SOURCES
    footswitch_down.png
    footswitch_up.png
    knob_hex.png
    background_on.jpg
    background_on_blue.jpg
    background_off.jpg

)

# Need to build BinaryData with -fPIC flag on Linux
set_target_properties(BinaryData PROPERTIES
    POSITION_INDEPENDENT_CODE TRUE)

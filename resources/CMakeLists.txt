juce_add_binary_data(BinaryData SOURCES
    footswitch_down.png
    footswitch_up.png
    knob2.png
    knob_hex.png
    led_blue_off.png
    led_blue_on.png
    led_red_off.png
    led_red_on.png
    smart_pedal.jpg

)

# Need to build BinaryData with -fPIC flag on Linux
set_target_properties(BinaryData PROPERTIES
    POSITION_INDEPENDENT_CODE TRUE)

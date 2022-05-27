APPL_CXXOBJS += device_io.o etrc_info.o utils.o driving.o test_runner.o game_play.o state_manager.o

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile
endif

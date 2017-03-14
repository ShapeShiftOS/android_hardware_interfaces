
LOCAL_SRC_FILES += SurfaceFlingerConfigs.cpp

ifneq ($(VSYNC_EVENT_PHASE_OFFSET_NS),)
    LOCAL_CFLAGS += -DVSYNC_EVENT_PHASE_OFFSET_NS=$(VSYNC_EVENT_PHASE_OFFSET_NS)
endif

ifneq ($(SF_VSYNC_EVENT_PHASE_OFFSET_NS),)
    LOCAL_CFLAGS += -DSF_VSYNC_EVENT_PHASE_OFFSET_NS=$(SF_VSYNC_EVENT_PHASE_OFFSET_NS)
endif

ifeq ($(NUM_FRAMEBUFFER_SURFACE_BUFFERS),3)
    LOCAL_CFLAGS += -DUSE_TRIPLE_FRAMEBUFFER
endif

ifeq ($(TARGET_BOARD_PLATFORM),omap4)
    LOCAL_CFLAGS += -DUSE_CONTEXT_PRIORITY=1
endif

ifeq ($(TARGET_BOARD_PLATFORM),s5pc110)
    LOCAL_CFLAGS += -DUSE_CONTEXT_PRIORITY=1
endif

$(FIG_DONE): package.fig
        fig --log-level warn -m -c build
        touch $@

$(GCC_HOME_FILE): $(FIG_DONE)
        fig -c default -g GCC_HOME > $(GCC_HOME_FILE)

gcc: $(GCC_HOME_FILE)
        $(eval GCC_HOME := $(shell cat $(GCC_HOME_FILE)))
        @test "x$(GCC_HOME)" != "x" || (echo "Fig failed"; false)

$(VERSION_CPP): $(LAST_VERSION)
        @echo Updating version number to $(APP_VERSION).
        @echo '// this file is auto-generated!' > $@
        @echo '#include "version.h"' >> $@
        @echo 'const char COMMON_VERSION[] = "$(APP_VERSION)";' >> $@

$(DBG_MAIN_O):out/dbg/main/%.o: $(MAIN_DIR)/%.cpp $(FIG_DONE) | gcc
        @mkdir -p $(dir $@)
        $(CXX) -c -o $@ $(CFLAGS) $(DBG_CFLAGS) -MD -MP -MF"$(@:%.o=%.d)" -MT "$@" -MT"$(@:%.o=%.d)" $<


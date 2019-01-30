# make targets

.PHONY: all clean distclean

all: $(TARGET)

install: all | $(INSTALLPATH) ALLDATAPATHS
	@echo Installing $(PROG) into $(INSTALLPATH)
	$(COPY) $(BUILDPATH)$(DIRSEP)$(TARGET) $(INSTALLPATH)
	@echo Installing data into $(DATAPATH)
	$(MKDIR) $(ALLDATAPATHS)
	$(COPY) $(GRAPHICSFILES) $(DATAPATH)$(DIRSEP)$(GRAPHICSPATH)

uninstall:
	@echo Removing $(PROG) from $(INSTALLPATH) and $(PROG) data from $(DATAPATH)
	$(REMOVE) $(INSTALLPATH)$(DIRSEP)$(TARGET)
	$(REMOVE) $(DATAPATH)

clean:
	$(REMOVE) $(BUILDPATH)

distclean: clean
	$(REMOVE) $(TRASHFILES)
	$(REMOVE) $(TRASHDIRS)

ALLDATAPATHS: $(ALLDATAPATHS)
	$(MKDIR) $<

$(INSTALLPATH):
	$(MKDIR) $@

$(BUILDPATH):
	$(MKDIR) $@

$(OBJECTS): | $(BUILDPATH)

# c sources
$(OBJECTS): %.o: %.cpp
	@$(CPPBUILD)
	@echo compiling $<


# output executable
$(TARGET): $(OBJECTS)
	$(LDBUILD)

-include $(DEPENDS)
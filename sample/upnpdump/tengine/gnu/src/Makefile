#
#	Makefile for CyberLink
#
#	Copyright (C) Satoshi Konno 2005
#

DEPS = Dependencies
DEPENDENCIES_OUTPUT := $(DEPS)

# for C++
USE_CPP = 1
REL_TYP=q

include $(BD)/bappl/etc/makerules
include $(CLINKROOT)/lib/tengine/gnu/Makefile.inc

TARGET = clinktestunit

S = ../../../
VPATH = $S

CLINKTESTCASESRC = \
	../../../clinktestunit.cpp \
	../../../UPnPTestCase.cpp

CPPUNITSRC = \
	$(CPPUNITROOT)/src/cppunit/AdditionalMessage.cpp \
	$(CPPUNITROOT)/src/cppunit/Asserter.cpp \
	$(CPPUNITROOT)/src/cppunit/BeOsDynamicLibraryManager.cpp \
	$(CPPUNITROOT)/src/cppunit/BriefTestProgressListener.cpp \
	$(CPPUNITROOT)/src/cppunit/CompilerOutputter.cpp \
	$(CPPUNITROOT)/src/cppunit/DefaultProtector.cpp \
	$(CPPUNITROOT)/src/cppunit/Exception.cpp \
	$(CPPUNITROOT)/src/cppunit/Message.cpp \
	$(CPPUNITROOT)/src/cppunit/Protector.cpp \
	$(CPPUNITROOT)/src/cppunit/ProtectorChain.cpp \
	$(CPPUNITROOT)/src/cppunit/RepeatedTest.cpp \
	$(CPPUNITROOT)/src/cppunit/ShlDynamicLibraryManager.cpp \
	$(CPPUNITROOT)/src/cppunit/SourceLine.cpp \
	$(CPPUNITROOT)/src/cppunit/StringTools.cpp \
	$(CPPUNITROOT)/src/cppunit/SynchronizedObject.cpp \
	$(CPPUNITROOT)/src/cppunit/Test.cpp \
	$(CPPUNITROOT)/src/cppunit/TestAssert.cpp \
	$(CPPUNITROOT)/src/cppunit/TestCase.cpp \
	$(CPPUNITROOT)/src/cppunit/TestCaseDecorator.cpp \
	$(CPPUNITROOT)/src/cppunit/TestComposite.cpp \
	$(CPPUNITROOT)/src/cppunit/TestDecorator.cpp \
	$(CPPUNITROOT)/src/cppunit/TestFactoryRegistry.cpp \
	$(CPPUNITROOT)/src/cppunit/TestFailure.cpp \
	$(CPPUNITROOT)/src/cppunit/TestLeaf.cpp \
	$(CPPUNITROOT)/src/cppunit/TestNamer.cpp \
	$(CPPUNITROOT)/src/cppunit/TestPath.cpp \
	$(CPPUNITROOT)/src/cppunit/TestPlugInDefaultImpl.cpp \
	$(CPPUNITROOT)/src/cppunit/TestResult.cpp \
	$(CPPUNITROOT)/src/cppunit/TestResultCollector.cpp \
	$(CPPUNITROOT)/src/cppunit/TestRunner.cpp \
	$(CPPUNITROOT)/src/cppunit/TestSetUp.cpp \
	$(CPPUNITROOT)/src/cppunit/TestSuccessListener.cpp \
	$(CPPUNITROOT)/src/cppunit/TestSuite.cpp \
	$(CPPUNITROOT)/src/cppunit/TestSuiteBuilderContext.cpp \
	$(CPPUNITROOT)/src/cppunit/TextOutputter.cpp \
	$(CPPUNITROOT)/src/cppunit/TextTestProgressListener.cpp \
	$(CPPUNITROOT)/src/cppunit/TextTestResult.cpp \
	$(CPPUNITROOT)/src/cppunit/TextTestRunner.cpp \
	$(CPPUNITROOT)/src/cppunit/TypeInfoHelper.cpp \
	$(CPPUNITROOT)/src/cppunit/XmlDocument.cpp \
	$(CPPUNITROOT)/src/cppunit/XmlElement.cpp \
	$(CPPUNITROOT)/src/cppunit/XmlOutputter.cpp \
	$(CPPUNITROOT)/src/cppunit/XmlOutputterHook.cpp

CPPUNITSRC_NOUSE = \
	$(CPPUNITROOT)/src/cppunit/DllMain.cpp \
	$(CPPUNITROOT)/src/cppunit/DynamicLibraryManager.cpp \
	$(CPPUNITROOT)/src/cppunit/DynamicLibraryManagerException.cpp \
	$(CPPUNITROOT)/src/cppunit/PlugInManager.cpp \
	$(CPPUNITROOT)/src/cppunit/PlugInParameters.cpp \
	$(CPPUNITROOT)/src/cppunit/UnixDynamicLibraryManager.cpp \
	$(CPPUNITROOT)/src/cppunit/Win32DynamicLibraryManager.cpp

EXPATSRC = \
	$(EXPATROOT)/lib/xmlparse.c \
	$(EXPATROOT)/lib/xmlrole.c \
	$(EXPATROOT)/lib/xmltok.c
#	$(EXPATROOT)/lib/xmltok_ns.c
#	$(EXPATROOT)/lib/xmltok_impl.c \
			
unexport SRC =
SRC = $(CLINKTESTCASESRC) $(CLINKSRC) $(CPPUNITSRC) $(EXPATSRC)

OBJ = $(addsuffix .o, $(basename $(SRC)))

CFLAGS += $(CFLAGS_WARNING)

CFLAGS += -DPROCESS_BASE
ifeq ($(mode), debug)
  LDLIBS += -ltm
endif

CFLAGS += -I$(CLINKHEADERROOT)
CFLAGS += -I$(CPPUNITROOT)/include
CFLAGS += -I$(EXPATROOT)/lib
CFLAGS += -DTENGINE
CFLAGS += -DTENGINE_NET_KASAGO
#CFLAGS += -DTENGINE_NET_PMC
CFLAGS += -DUSE_XMLPARSER_EXPAT

# for C++
CPPFLAGS += -D__USE_THREADS
CPPFLAGS += -D__USE_IOSTREAMS
LOADLIBES += -lstlport

# for Expat
CFLAGS += -DHAVE_MEMMOVE

# for KASAGO
ifeq ($(MACHINE), m32104)
  START_ADR = -Wl,-Ttext,0x049B0000,-Tdata,0x049B8000
  CFLAGS += -DTM_BIG_ENDIAN
  CFLAGS += -O0
endif
ifeq ($(MACHINE), sh7727)
  CFLAGS += -DTM_LITTLE_ENDIAN
endif
LOADLIBES += -lsvc_ka

# ----------------------------------------------------------------------------

.PHONY: all install clean

ifeq ($(mode), debug)
  NOINST = $(TARGET).trg
endif
INST = $(TARGET) $(TARGET:%=%.map)
ALL = $(INST) $(NOINST)

all: $(ALL)

#$(TARGET): $(OBJ)
$(TARGET): $(addsuffix .o, $(basename $(SRC)))

$(OBJ):

$(TARGET).trg: $(TARGET)
	cp $< $@
	$(STRIP) $@

clean:
	$(RM) $(OBJ) $(ALL) $(DEPS)

prenv:
	set

install: $(addprefix $(EXE_INSTALLDIR)/, $(INST))

$(TARGET:%=$(EXE_INSTALLDIR)/%): $(EXE_INSTALLDIR)/%: %
	$(EXE_INSTALL_STRIP)

ifdef DEPENDENCIES_OUTPUT
  $(DEPS): ; touch $(DEPS)
else
  $(DEPS): $(SRC) ; $(MAKEDEPS) $@ $?
endif
include $(DEPS)


CLD_LIB_DIR = /usr/local/lib/cld
CLD_INCLUDE_DIR = /usr/local/include/cld

BASEDIR=../../../
CLASSDIR=../../../target/classes
OUTPUTDIR=../../../target/native

default: $(OUTPUTDIR)/libcld.jnilib

test: $(CLASSDIR)/com/mzsanford/cld/CompactLanguageDetector.class $(OUTPUTDIR)/libcld.jnilib
	java -cp $(CLASSDIR) com.mzsanford.cld.CompactLanguageDetector "Was gibt neues?"

$(OUTPUTDIR)/com_mzsanford_cld_CompactLanguageDetector.o: $(OUTPUTDIR) com_mzsanford_cld_CompactLanguageDetector.cpp com_mzsanford_cld_CompactLanguageDetector.h
	$(CC) -c -I/System/Library/Frameworks/JavaVM.framework/Headers -I$(CLD_INCLUDE_DIR) -DCLD_WINDOWS -o $(OUTPUTDIR)/com_mzsanford_cld_CompactLanguageDetector.o com_mzsanford_cld_CompactLanguageDetector.cpp

$(OUTPUTDIR)/libcld.jnilib: $(OUTPUTDIR) $(OUTPUTDIR)/com_mzsanford_cld_CompactLanguageDetector.o
	$(CC) -dynamiclib -o $(OUTPUTDIR)/libcld.jnilib $(OUTPUTDIR)/com_mzsanford_cld_CompactLanguageDetector.o -framework JavaVM -lcld -L$(CLD_LIB_DIR)

$(OUTPUTDIR)/com_mzsanford_cld_CompactLanguageDetector.h: $(OUTPUTDIR) ../java/com/mzsanford/cld/CompactLanguageDetector.java
	javah -classpath $(CLASSDIR) com.mzsanford.cld.CompactLanguageDetector

$(OUTPUTDIR):
	mkdir -p $(OUTPUTDIR)

clean:
	rm $(OUTPUTDIR)/com_mzsanford_cld_CompactLanguageDetector.o $(OUTPUTDIR)/libcld.jnilib


CLD_LIB_DIR = /usr/local/lib/cld
CLD_INCLUDE_DIR = /usr/local/include/cld

default: libcld.jnilib

test: ../../../target/classes/com/mzsanford/cld/CompactLanguageDetector.class libcld.jnilib
	java com.mzsanford.cld.CompactLanguageDetector "Was gibt neues?"

com_mzsanford_cld_CompactLanguageDetector.o: com_mzsanford_cld_CompactLanguageDetector.cpp com_mzsanford_cld_CompactLanguageDetector.h
	$(CC) -c -I/System/Library/Frameworks/JavaVM.framework/Headers -I$(CLD_INCLUDE_DIR) -DCLD_WINDOWS com_mzsanford_cld_CompactLanguageDetector.cpp

libcld.jnilib: com_mzsanford_cld_CompactLanguageDetector.o
	$(CC) -dynamiclib -o libcld.jnilib com_mzsanford_cld_CompactLanguageDetector.o -framework JavaVM -lcld -L$(CLD_LIB_DIR)

com_mzsanford_cld_CompactLanguageDetector.h: ../java/com/mzsanford/cld/CompactLanguageDetector.java
	javah -classpath ../../../target/classes com.mzsanford.cld.CompactLanguageDetector

clean:
	rm com_mzsanford_cld_CompactLanguageDetector.o libcld.jnilib


package com.mzsanford.cld;

public class CompactLanguageDetector {
    static {
        System.loadLibrary("cld");
    }

    public String detect(String text) {
        // Call native code.
        return detectLanguage(text);
    }

    /* PRIVATE NATIVE CODE */
    private native String detectLanguage(String text);

    public static void main(String [] args) {
	  CompactLanguageDetector cld = new CompactLanguageDetector();
	  System.out.println("DETECTED: " + cld.detect(args[0]));
    }
}

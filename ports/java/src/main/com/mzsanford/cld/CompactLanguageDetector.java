
package com.mzsanford.cld;

import java.util.Locale;

public class CompactLanguageDetector {
    static {
        System.loadLibrary("cld");
    }

    public Locale detect(String text) {
	    Locale detected = null;
        // Call native code.
        String nativeLanguageCode = detectLanguage(text);
		if (nativeLanguageCode != null) {
			detected = new Locale(nativeLanguageCode);
		}
		return detected;
    }

    /* PRIVATE NATIVE CODE */
    private native String detectLanguage(String text);

    private native LanguageDetectionResult detectLanguageDetails( String text,
                                                                  boolean is_plain_text,
                                                                  boolean do_allow_extended_languages,
                                                                  boolean skip_summary_language,
                                                                  boolean keep_weak_matches,
                                                                  String tld_hint);
    /* END NATIVE CODE */

    /* Interactive test entry point */
    public static void main(String [] args) {
	  CompactLanguageDetector cld = new CompactLanguageDetector();
	  Locale detected = cld.detect(args[0]);
	  if (detected != null) {
		System.out.println("DETECTED: " + detected.getDisplayName());
	  } else {
		System.out.println("Language detection failed");
	  }
    }

    public static class LanguageDetectionResult {
    }
}

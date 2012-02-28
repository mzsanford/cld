
package com.mzsanford.cld;

import java.util.Collections;
import java.util.Locale;


public class CompactLanguageDetector {
    static {
        // Bring on the hotness.
        System.loadLibrary("cld");
    }

    /**
     * 
     * @param text to identify the language of
     * @return result object with identification details
     */
    public LanguageDetectionResult detect(String text) {
    	LanguageDetectionResult result = null;
        // Call native code.
        String nativeLanguageCode = detectLanguage(text);
		if (nativeLanguageCode != null) {
		    // TODO: Native code should fill in this object
		    result = new LanguageDetectionResult(new Locale(nativeLanguageCode),
		                                         false,
		                                         Collections.<LanguageDetectionCandidate>emptyList());
		}
		return result;
    }
    
    public LanguageDetectionResult detectDetailed(String text) {
        // Native call.
        LanguageDetectionResult result = detectLanguageDetails(text, true, true, true, true, null);
        return result;
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
	  LanguageDetectionResult detected = cld.detectDetailed(args[0]);
      System.out.println("Here we go.");
	  if (detected != null && detected.probableLocale != null) {
		System.out.println("DETECTED: " + detected.toString());
	  } else {
		System.out.println("Language detection failed: " + detected.isReliable());
	  }
    }
}

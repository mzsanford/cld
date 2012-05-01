
package com.mzsanford.cld;

/**
 * Class providing an interface for detecting the language of a given string of text using
 * the Compact Language Detector.
 * 
 * @author Matt Sanford <matt@mzsanford.com>
 */
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
        // Native call.
        LanguageDetectionResult result = detectLanguageDetails(text, true, true, false, true, null);
        return result;
    }
    

    /* PRIVATE NATIVE CODE */

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
	  LanguageDetectionResult detected = cld.detect(args[0]);
	  if (detected != null && detected.probableLocale != null) {
		System.out.println("DETECTED: " + detected.toString());
	  } else {
		System.out.println("Language detection failed: " + detected.isReliable());
	  }
    }
}

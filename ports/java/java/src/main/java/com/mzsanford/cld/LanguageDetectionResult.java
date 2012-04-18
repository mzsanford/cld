package com.mzsanford.cld;

import java.util.Collections;
import java.util.List;
import java.util.Locale;

/**
 * Results of a language detection attempt
 * 
 * @author matt
 */
public class LanguageDetectionResult {
	Locale probableLocale;
	private boolean reliable;
	private List<LanguageDetectionCandidate> candidates;
	
	/**
	 * Package scoped constructor used by the CompactLanguageDetector class
	 * 
	 * @param probableLocale most likely locale
	 * @param reliable expected reliability of probableLocale
	 * @param candidates List of candidates with scores
	 */
	LanguageDetectionResult(Locale probableLocale, boolean reliable,
            List<LanguageDetectionCandidate> candidates) {
        super();
        this.probableLocale = probableLocale;
        this.reliable = reliable;
        this.candidates = candidates;
    }

    /**
     * @return the probableLocale
     */
    public Locale getProbableLocale() {
        return probableLocale;
    }

    /**
     * @return the reliability of the probableLocale
     */
    public boolean isReliable() {
        return reliable;
    }

    /**
     * @return copy of the candidates (up to three)
     */
    public List<LanguageDetectionCandidate> getCandidates() {
        // Take the hit for a copy to prevent changes.
        return Collections.unmodifiableList(candidates);
    }

    /**
     * @see java.lang.Object#toString()
     */
    @Override
    public String toString() {
        return new StringBuilder("LanguageDetectionResult [probableLocale=").append(probableLocale)
                   .append(", reliable=").append(reliable)
                   .append(", candidates=").append(candidates).append("]")
                   .toString();
    }
}
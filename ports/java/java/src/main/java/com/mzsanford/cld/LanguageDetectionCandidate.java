package com.mzsanford.cld;

import java.util.Locale;

/**
 * A single possible result
 * 
 * @author Matt Sanford <matt@mzsanford.com>
 */
public class LanguageDetectionCandidate {
    /** Locale object representing the candidate language */
	private Locale locale;
	/** Raw probability score */
	private double score;
	/** Normalized probability score */
	private double normalizedScore;
	
	/**
	 * Package scoped constructor used by the underlying library for creation
	 * 
	 * @param locale of the candidate
	 * @param score raw probability score
	 * @param normalizedScore normalized probability score
	 */
	LanguageDetectionCandidate(Locale locale, double score, double normalizedScore) {
		super();
		this.locale = locale;
		this.score = score;
		this.normalizedScore = normalizedScore;		
	}
	
	/**
	 * @return the locale
	 */
	public Locale getLocale() {
		return locale;
	}
	
	/**
	 * @return the score
	 */
	public double getScore() {
		return score;
	}
	
	/**
	 * @return the normalizedScore
	 */
	public double getNormalizedScore() {
		return normalizedScore;
	}

    /**
     * @see java.lang.Object#toString()
     */
    @Override
    public String toString() {
        return new StringBuilder("LanguageDetectionCandidate [locale=").append(locale)
                                 .append(", score=").append(score)
                                 .append(", normalizedScore=").append(normalizedScore).append("]")
                                 .toString();
    }
}

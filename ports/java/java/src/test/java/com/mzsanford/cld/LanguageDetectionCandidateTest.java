package com.mzsanford.cld;

import static org.junit.Assert.*;

import java.util.Locale;

import org.junit.Test;

public class LanguageDetectionCandidateTest {
    private LanguageDetectionCandidate result = null;
    private Locale locale = new Locale("en");

    @Test
    public void testGetLocale() {
        result = new LanguageDetectionCandidate(locale, 0.0, 0.0);
        assertEquals(locale, result.getLocale());
    }

    @Test
    public void testGetScore() {
        result = new LanguageDetectionCandidate(locale, 1.0, 2.0);
        assertEquals(1.0, result.getScore(), 0.001);
    }

    @Test
    public void testGetNormalizedScore() {
        result = new LanguageDetectionCandidate(locale, 1.0, 2.0);
        assertEquals(2.0, result.getNormalizedScore(), 0.001);
    }

    @Test
    public void testToString() {
        result = new LanguageDetectionCandidate(locale, 1.0, 2.0);
        assertTrue(result.toString().indexOf("locale=en") > 0);
        assertTrue(result.toString().indexOf("score=1.0") > 0);
        assertTrue(result.toString().indexOf("normalizedScore=2.0") > 0);
    }

}

package com.mzsanford.cld;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.fail;

import java.util.Locale;

import org.junit.Test;

public class LanguageDetectionResultTest {
    private LanguageDetectionResult result = null;
    private Locale locale = new Locale("en");

    @Test
    public void testGetProbableLocale() {
        result = new LanguageDetectionResult(locale, false, null);
        assertEquals(locale, result.getProbableLocale());
    }

    @Test
    public void testIsReliable() {
        result = new LanguageDetectionResult(locale, true, null);
        assertEquals(true, result.isReliable());
        
        result = new LanguageDetectionResult(locale, false, null);
        assertEquals(false, result.isReliable());
    }

    @Test
    public void testGetCandidates() {
        fail("Not yet implemented");
    }

    @Test
    public void testToString() {
        fail("Not yet implemented");
    }

}

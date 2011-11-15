
#include "com_mzsanford_cld_CompactLanguageDetector.h"

#include <string.h>

// Include the CLD headers
#include "cld/compact_lang_det.h"
#include "cld/encodings/compact_lang_det/ext_lang_enc.h"
#include "cld/encodings/compact_lang_det/unittest_data.h"
#include "cld/encodings/proto/encodings.pb.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     com_mzsanford_cld_CompactLanguageDetector
 * Method:    detectLanguage
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_mzsanford_cld_CompactLanguageDetector_detectLanguage
  (JNIEnv *env, jobject obj, jstring text) {

    bool is_plain_text = true;
    bool do_allow_extended_languages = true;
    bool do_pick_summary_language = false;
    bool do_remove_weak_matches = false;
    bool is_reliable;
    Language plus_one = (Language)UNKNOWN_LANGUAGE;
    const char* tld_hint = NULL;
    int encoding_hint = UNKNOWN_ENCODING;
    Language language_hint = UNKNOWN_LANGUAGE;

    double normalized_score3[3];
    Language language3[3];
    int percent3[3];
    int text_bytes;

    jboolean iscopy;
    const char *src = env->GetStringUTFChars(text, &iscopy);

    Language lang;
    lang = CompactLangDet::DetectLanguage(0,
                                          src, strlen(src),
                                          is_plain_text,
                                          do_allow_extended_languages,
                                          do_pick_summary_language,
                                          do_remove_weak_matches,
                                          tld_hint,
                                          encoding_hint,
                                          language_hint,
                                          language3,
                                          percent3,
                                          normalized_score3,
                                          &text_bytes,
                                          &is_reliable);

    return( env->NewStringUTF(LanguageCode(lang)) );
}

JNIEXPORT jobject JNICALL Java_com_mzsanford_cld_CompactLanguageDetector_detectLanguageDetails
  (JNIEnv *env, jobject obj, jstring text, jboolean plain_text, jboolean allow_extended,
   jboolean skip_summary, jboolean keep_weak_match, jstring tld_hint_arg) {
	jboolean iscopy;

	bool is_plain_text = plain_text;
    bool do_allow_extended_languages = allow_extended;
    bool do_pick_summary_language = !skip_summary;
    bool do_remove_weak_matches = !keep_weak_match;
    bool is_reliable;
    Language plus_one = (Language)UNKNOWN_LANGUAGE;
    const char* tld_hint = env->GetStringUTFChars(tld_hint_arg, &iscopy);

    int encoding_hint = UNKNOWN_ENCODING;
    Language language_hint = UNKNOWN_LANGUAGE;

    double normalized_score3[3];
    Language language3[3];
    int percent3[3];
    int text_bytes;

    const char *src = env->GetStringUTFChars(text, &iscopy);

    Language lang;
    lang = CompactLangDet::DetectLanguage(0,
                                          src, strlen(src),
                                          is_plain_text,
                                          do_allow_extended_languages,
                                          do_pick_summary_language,
                                          do_remove_weak_matches,
                                          tld_hint,
                                          encoding_hint,
                                          language_hint,
                                          language3,
                                          percent3,
                                          normalized_score3,
                                          &text_bytes,
                                          &is_reliable);

    // TODO: build and return the correct result class
    return( env->NewStringUTF(LanguageCode(lang)) );
}

#ifdef __cplusplus
}
#endif

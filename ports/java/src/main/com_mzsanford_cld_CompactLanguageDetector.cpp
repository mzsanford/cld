
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
    jclass classResult = env->FindClass("com/mzsanford/cld/LanguageDetectionResult");
    jclass classCandidate = env->FindClass("com/mzsanford/cld/LanguageDetectionCandidate");

    return( env->NewStringUTF(LanguageCode(lang)) );
}

/********* Helper Methods *******/

void mzs_throw_by_name(JNIEnv *env, const char *name, const char *msg) {
     jclass cls = env->FindClass(name);
     /* if cls is NULL, an exception has already been thrown */
     if (cls != NULL) {
         env->ThrowNew(cls, msg);
     }
     /* free the local ref */
     env->DeleteLocalRef(cls);
}

jobject mzs_new_language_detection_result(JNIEnv *env) {
    jobject resultObject;
   
    jclass classResult = env->FindClass("com/mzsanford/cld/LanguageDetectionResult");
    if (classResult == 0) {
        mzs_throw_by_name(env, "java/lang/IllegalArgumentException", "Can't find com.mzsanford.cld.LanguageDetectionResult class");
        return (jobject) 0;
    }
    
    /* TODO: (II)V needs to have the correct args. Those need to be passed into here */
    jmethodID ctorMethodId = env->GetMethodID(classResult, "<init>", "(II)V");
	if (ctorMethodId == 0) {
	  mzs_throw_by_name(env, "java/lang/IllegalArgumentException", "Can't find com.mzsanford.cld.LanguageDetectionResult constructor");
	  return (jobject) 0;
	}
 
	resultObject = env->NewObject(classResult, ctorMethodId);
	if (resultObject == 0) {
	  mzs_throw_by_name(env, "java/lang/IllegalArgumentException", "Can't create com.mzsanford.cld.LanguageDetectionResult object");
	  return (jobject) 0;
	}
	
	return resultObject;
}

#ifdef __cplusplus
}
#endif

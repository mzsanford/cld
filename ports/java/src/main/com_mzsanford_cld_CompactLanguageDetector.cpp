
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

jobject mzs_new_locale(JNIEnv *env, const char *str) {
  if (strcmp("un", str) == 0) {
    return NULL;
  }

  jobject localeObject;
  jclass classLocale = env->FindClass("java/util/Locale");
    if (classLocale == 0) {
        mzs_throw_by_name(env, "java/lang/IllegalArgumentException", "Can't find java.util.Locale class");
        return (jobject) 0;
    }

    jmethodID ctorMethodId = env->GetMethodID(classLocale, "<init>", "(Ljava/lang/String;)V");
	if (ctorMethodId == 0) {
	  mzs_throw_by_name(env, "java/lang/IllegalArgumentException", "Can't find java.util.Locale constructor");
	  return (jobject) 0;
	}

	localeObject = env->NewObject(classLocale, ctorMethodId, env->NewStringUTF(str));
	if (localeObject == 0) {
	  mzs_throw_by_name(env, "java/lang/IllegalArgumentException", "Can't create java.util.Locale object");
	  return (jobject) 0;
	}

	return localeObject;
}

jobject mzs_new_language_detection_candidates(JNIEnv *env,
                                              Language language3[3],
                                              double normalized_score3[3],
                                              int percent3[3]) {
    jobject resultObject;

    /* Shortcut for 0 candidate languages */
    if (IS_LANGUAGE_UNKNOWN(language3[0])) {
      return NULL;
    }
        
    /** New List for the candidates **/
    jclass classList = env->FindClass("java/util/LinkedList");
    if (classList == 0) {
        mzs_throw_by_name(env, "java/lang/IllegalArgumentException", "Can't find java.util.LinkedList class");
        return (jobject) 0;
    }
    jmethodID ctorMethodIdList = env->GetMethodID(classList, "<init>", "()V");
	if (ctorMethodIdList == 0) {
	  mzs_throw_by_name(env, "java/lang/IllegalArgumentException", "Can't find java.util.LinkedList constructor");
	  return (jobject) 0;
	}
	resultObject = env->NewObject(classList, ctorMethodIdList);
	if (resultObject == 0) {
	  mzs_throw_by_name(env, "java/lang/IllegalArgumentException", "Can't create java.util.LinkedList object");
	  return (jobject) 0;
	}
	/* Add method for building the List */
	jmethodID addMethodIdList = env->GetMethodID(classList, "add", "(Ljava/lang/Object;)Z");
	if (addMethodIdList == 0) {
	  mzs_throw_by_name(env, "java/lang/IllegalArgumentException", "Can't find java.util.LinkedList method 'add(Object)'");
	  return (jobject) 0;
	}
	
	/** Prep for candidate members **/
	jclass classCandidate = env->FindClass("com/mzsanford/cld/LanguageDetectionCandidate");
    if (classCandidate == 0) {
        mzs_throw_by_name(env, "java/lang/IllegalArgumentException", "Can't find com.mzsanford.cld.LanguageDetectionCandidate class");
        return (jobject) 0;
    }
    jmethodID ctorMethodIdCandidate = env->GetMethodID(classCandidate, "<init>", "(Ljava/util/Locale;DD)V");
    if (ctorMethodIdCandidate == 0) {
	  mzs_throw_by_name(env, "java/lang/IllegalArgumentException", "Can't find com.mzsanford.cld.LanguageDetectionCandidate constructor");
	  return (jobject) 0;
	}
    
    /** Fill in the list of candidates **/
    for (int i=0; i<3; i++) {
      if (!IS_LANGUAGE_UNKNOWN(language3[i])) {        
        env->CallBooleanMethod(resultObject,
                               addMethodIdList,
                               env->NewObject(classCandidate, ctorMethodIdCandidate,
                                              mzs_new_locale(env, LanguageCode(language3[i])),
                                              (double)percent3[i], normalized_score3[i])
                              );
       
      }
    }
                                         
    return resultObject;
}

jobject mzs_new_language_detection_result(JNIEnv *env,
                                          Language probableLanguage,
                                          bool probableIsReliable,
                                          Language language3[3],
                                          double normalized_score3[3],
                                          int percent3[3]) {
    jobject resultObject;
    jobject probableLocale = mzs_new_locale(env, LanguageCode(probableLanguage));
    jboolean reliable = probableIsReliable;
    jobject detectionCandidates = mzs_new_language_detection_candidates(env, language3, normalized_score3, percent3);

    jclass classResult = env->FindClass("com/mzsanford/cld/LanguageDetectionResult");
    if (classResult == 0) {
        mzs_throw_by_name(env, "java/lang/IllegalArgumentException", "Can't find com.mzsanford.cld.LanguageDetectionResult class");
        return (jobject) 0;
    }

    jmethodID ctorMethodId = env->GetMethodID(classResult, "<init>", "(Ljava/util/Locale;ZLjava/util/List;)V");
	if (ctorMethodId == 0) {
	  mzs_throw_by_name(env, "java/lang/IllegalArgumentException", "Can't find com.mzsanford.cld.LanguageDetectionResult constructor");
	  return (jobject) 0;
	}

	resultObject = env->NewObject(classResult, ctorMethodId, probableLocale, reliable, detectionCandidates);
	if (resultObject == 0) {
	  mzs_throw_by_name(env, "java/lang/IllegalArgumentException", "Can't create com.mzsanford.cld.LanguageDetectionResult object");
	  return (jobject) 0;
	}

	return resultObject;
}


/******* Begin JNI methods *******/

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
    const char* tld_hint = NULL;
    if (tld_hint_arg != NULL) {
      tld_hint = env->GetStringUTFChars(tld_hint_arg, &iscopy);;
    } 

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

    return mzs_new_language_detection_result(env, lang, is_reliable, language3, normalized_score3, percent3);
}

#ifdef __cplusplus
}
#endif

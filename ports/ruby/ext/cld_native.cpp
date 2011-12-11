
// Include the Ruby headers and goodies
#include "ruby.h"

// Include the CLD headers
#include "cld/compact_lang_det.h"
#include "cld/encodings/compact_lang_det/ext_lang_enc.h"
#include "cld/encodings/compact_lang_det/unittest_data.h"
#include "cld/encodings/proto/encodings.pb.h"

#define SYMBOL_NAMED(x)   ID2SYM( rb_intern(x) )

static VALUE t_init(VALUE self)
{
  return self;
}

static VALUE t_build_detection_result(Language lang, bool is_reliable, 
                                      Language language3[3], double normalized_score3[3],
                                      int percent3[3])
{
	VALUE argv[0];
	// Modules and classes
	VALUE cld_module = rb_define_module("CLD");
	VALUE result_class = rb_const_get(cld_module, rb_intern("LanguageResult"));
	VALUE possible_class = rb_const_get(cld_module, rb_intern("PossibleLanguage"));
	VALUE lang_class = rb_const_get(cld_module, rb_intern("Language"));

	VALUE detection_result = rb_class_new_instance(0, argv, result_class);
	
	VALUE probable_lang_obj = rb_class_new_instance(0, argv, lang_class);
	rb_ivar_set(probable_lang_obj, rb_intern("@name"), rb_str_new2(LanguageName(lang)) );
	rb_ivar_set(probable_lang_obj, rb_intern("@code"), rb_str_new2(LanguageCode(lang)) );

	rb_ivar_set(detection_result, rb_intern("@probable_language"), probable_lang_obj);
	rb_ivar_set(detection_result, rb_intern("@reliable"), is_reliable);

	VALUE array = rb_ary_new();
	for (int i=0; i < 3; i++) {
		if ( !IS_LANGUAGE_UNKNOWN(language3[i]) ) {
			VALUE lang_obj = rb_class_new_instance(0, argv, lang_class);
			rb_ivar_set(lang_obj, rb_intern("@name"), rb_str_new2(LanguageName(language3[i])) );
			rb_ivar_set(lang_obj, rb_intern("@code"), rb_str_new2(LanguageCode(language3[i])) );
			
			VALUE result = rb_class_new_instance(0, argv, possible_class);
			rb_ivar_set(result, rb_intern("@language"), lang_obj );
			rb_ivar_set(result, rb_intern("@score"), rb_float_new(normalized_score3[i]) );
			rb_ivar_set(result, rb_intern("@raw_score"), rb_float_new(percent3[i]) );
			rb_ary_push(array, result);
		}
	}
	rb_ivar_set(detection_result, rb_intern("@possible_languages"), array);

	return detection_result;
}

static VALUE t_detect_language(VALUE self, VALUE text, VALUE options)
{
	
	bool is_plain_text = !rb_hash_aref(options, SYMBOL_NAMED("html"));
    bool do_allow_extended_languages = rb_hash_aref(options, SYMBOL_NAMED("all_languages"));
    bool do_remove_weak_matches = !rb_hash_aref(options, SYMBOL_NAMED("weak_matches"));
    // TODO: Add hints via options hash
    int encoding_hint = UNKNOWN_ENCODING;
    Language language_hint = UNKNOWN_LANGUAGE;
    const char* tld_hint = NULL;
    bool do_pick_summary_language = false;

    bool is_reliable;
    Language plus_one = (Language)UNKNOWN_LANGUAGE;
    double normalized_score3[3];
    Language language3[3];
    int percent3[3];
    int text_bytes;
    char *src = StringValueCStr(text);

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

   return t_build_detection_result(lang, is_reliable, language3, normalized_score3, percent3);
}

extern "C" {

	static VALUE cCLD;

	void Init_cld_native() {
	  cCLD = rb_define_class("CLDNative", rb_cObject);
	  rb_define_method(cCLD, "initialize", RUBY_METHOD_FUNC(t_init), 0);
	  rb_define_method(cCLD, "detect_language", RUBY_METHOD_FUNC(t_detect_language), 2);
	}

} // extern C


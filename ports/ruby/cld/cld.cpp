
// Include the Ruby headers and goodies
#include "ruby.h"

// Include the CLD headers
#include "cld/compact_lang_det.h"
#include "cld/encodings/compact_lang_det/ext_lang_enc.h"
#include "cld/encodings/compact_lang_det/unittest_data.h"
#include "cld/encodings/proto/encodings.pb.h"

static VALUE t_init(VALUE self)
{
  return self;
}

static VALUE t_detect_language(VALUE self, VALUE text)
{
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
	char* src = STR2CSTR(text);

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
   return rb_str_new2(LanguageName(lang));
}

extern "C" {



	static VALUE cCLD;

	void Init_cld() {
	  cCLD = rb_define_class("CLD", rb_cObject);
	  rb_define_method(cCLD, "initialize", RUBY_METHOD_FUNC(t_init), 0);
	  rb_define_method(cCLD, "detect_language", RUBY_METHOD_FUNC(t_detect_language), 1);
	}

} // extern C


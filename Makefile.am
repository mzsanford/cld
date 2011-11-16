AUTOMAKE_OPTIONS          = gnu
AM_CPPFLAGS               = -I. -Ibase -DCLD_WINDOWS

pkglib_LTLIBRARIES        = libcld.la 
pkginclude_HEADERS        = encodings/compact_lang_det/*.h

langincludedir            = $(includedir)/cld/languages/public
langinclude_HEADERS       = languages/public/*.h

langprotoincludedir       = $(includedir)/cld/languages/proto
langprotoinclude_HEADERS  = languages/proto/*.h

encincludedir             = $(includedir)/cld/encodings/compact_lang_det
encinclude_HEADERS        = encodings/compact_lang_det/*.h

encwinincludedir          = $(includedir)/cld/encodings/compact_lang_det/win
encwininclude_HEADERS     = encodings/compact_lang_det/win/*.h

encprotoincludedir        = $(includedir)/cld/encodings/proto
encprotoinclude_HEADERS   = encodings/proto/*.h

baseincludedir            = $(includedir)/cld/base
baseinclude_HEADERS       = base/*.h


noinst_HEADERS            = 
libcld_la_SOURCES         = encodings/compact_lang_det/cldutil.cc encodings/compact_lang_det/cldutil_dbg_empty.cc encodings/compact_lang_det/compact_lang_det.cc encodings/compact_lang_det/compact_lang_det_impl.cc encodings/compact_lang_det/ext_lang_enc.cc encodings/compact_lang_det/getonescriptspan.cc encodings/compact_lang_det/letterscript_enum.cc encodings/compact_lang_det/tote.cc encodings/compact_lang_det/generated/cld_generated_score_quadchrome_0406.cc encodings/compact_lang_det/generated/compact_lang_det_generated_cjkbis_0.cc encodings/compact_lang_det/generated/compact_lang_det_generated_ctjkvz.cc encodings/compact_lang_det/generated/compact_lang_det_generated_deltaoctachrome.cc encodings/compact_lang_det/generated/compact_lang_det_generated_quadschrome.cc encodings/compact_lang_det/win/cld_htmlutils_windows.cc encodings/compact_lang_det/win/cld_unilib_windows.cc encodings/compact_lang_det/win/cld_utf8statetable.cc encodings/compact_lang_det/win/cld_utf8utils_windows.cc encodings/internal/encodings.cc languages/internal/languages.cc
libcld_la_LDFLAGS         = -version 0:1:0 

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = cld.pc
        
  
%Dictionary.cc %Dictionary.h:$(pkginclude_HEADERS) %LinkDef.hh
	@ROOTCINT@ -f $*.cc -c $(AM_CPPLFAGS) $(INCLUDES) $^ 

// Copyright (c) 2011 Michael McCandless. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <Python.h>

#define CLD_WINDOWS

#include "encodings/compact_lang_det/compact_lang_det.h"
#include "encodings/compact_lang_det/ext_lang_enc.h"
#include "base/string_util.h"
#include "cld_encodings.h"

#if PY_MAJOR_VERSION >= 3
#define PYSTR(s) PyUnicode_FromString(s)
#else
#define PYSTR(s) PyString_FromString(s)
#endif

static PyObject *CLDError;

static bool EncodingFromName(const char *name, Encoding *answer) {
  for (int encIDX=0;encIDX<NUM_ENCODINGS;encIDX++) {
    if (!base::strcasecmp(name, cld_encoding_info[encIDX].name)) {
      *answer = cld_encoding_info[encIDX].encoding;
      return true;
    }
  }
  *answer = UNKNOWN_ENCODING;

  return false;
}

static PyObject *
detect(PyObject *self, PyObject *args, PyObject *kwArgs) {
  char *bytes;
  int numBytes;

  int isPlainText = 0;
  int pickSummaryLanguage = 0;
  int removeWeakMatches = 1;
  int includeExtendedLanguages = 1;

  // "id" boosts Indonesian;
  const char* hintTopLevelDomain = NULL;

  // ITALIAN boosts it
  const char* hintLanguageCode = NULL;

  // SJS boosts Japanese
  const char* hintEncoding = NULL;

  static const char *kwList[] = {"utf8Bytes",
                                 "isPlainText",
                                 "includeExtendedLanguages",
                                 "hintTopLevelDomain",
                                 "hintLanguageCode",
                                 "hintEncoding",
                                 "pickSummaryLanguage",
                                 "removeWeakMatches",
                                 NULL};

  if (!PyArg_ParseTupleAndKeywords(args, kwArgs, "s#|iizzzii",
                                   (char **) kwList,
                                   &bytes, &numBytes,
                                   &isPlainText,
                                   &includeExtendedLanguages,
                                   &hintTopLevelDomain,
                                   &hintLanguageCode,
                                   &hintEncoding,
                                   &pickSummaryLanguage,
                                   &removeWeakMatches)) {
    return NULL;
  }

  Language hintLanguageEnum;
  if (hintLanguageCode == NULL) {
    // no hint
    hintLanguageEnum = UNKNOWN_LANGUAGE;
  } else if (!LanguageFromCode(hintLanguageCode, &hintLanguageEnum)) {
    // TODO: maybe LookupError?
    PyErr_Format(CLDError, "Unrecognized language hint code (got '%s'); see cld.LANGUAGES for recognized language codes (note that currently external languages cannot be hinted)", hintLanguageCode);
    return NULL;
  }

  Encoding hintEncodingEnum;
  if (hintEncoding == NULL) {
    // no hint
    hintEncodingEnum = UNKNOWN_ENCODING;
  } else if (!EncodingFromName(hintEncoding, &hintEncodingEnum)) {
    PyErr_Format(CLDError, "Unrecognized encoding hint code (got '%s'); see cld.ENCODINGS for recognized encodings", hintEncoding);
    return NULL;
  }
    
  bool isReliable;
  Language language3[3];
  int percent3[3];
  double normalized_score3[3];
  int textBytesFound;
  Language sumLang;
  Py_BEGIN_ALLOW_THREADS
  sumLang = CompactLangDet::DetectLanguage(0,
                                           bytes, numBytes,
                                           isPlainText != 0,
                                           includeExtendedLanguages != 0,
                                           pickSummaryLanguage != 0,
                                           removeWeakMatches != 0,
                                           hintTopLevelDomain,
                                           hintEncodingEnum,
                                           hintLanguageEnum,
                                           language3,
                                           percent3,
                                           normalized_score3,
                                           &textBytesFound,
                                           &isReliable);
  Py_END_ALLOW_THREADS

  PyObject *details = PyList_New(0);
  for(int idx=0;idx<3;idx++) {
    Language lang = language3[idx];
    if (lang == UNKNOWN_LANGUAGE) {
      break;
    }

    PyObject *oneDetail = Py_BuildValue("(ssif)",
                                        ExtLanguageName(lang),
                                        ExtLanguageCode(lang),
                                        percent3[idx],
                                        normalized_score3[idx]);
    PyList_Append(details, oneDetail);
    Py_DECREF(oneDetail);
  }

  PyObject *result = Py_BuildValue("(ssOiO)",
                                   ExtLanguageName(sumLang),
                                   ExtLanguageCode(sumLang),
                                   isReliable ? Py_True : Py_False,
                                   textBytesFound,
                                   details);
  Py_DECREF(details);
  return result;
}

static PyMethodDef CLDMethods[] = {
  {"detect",  (PyCFunction) detect, METH_VARARGS | METH_KEYWORDS,
   "Detect language from a UTF8 string."},
  {NULL, NULL, 0, NULL}        /* Sentinel */
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "cld",
        NULL,
        NULL,
        CLDMethods,
        NULL,
        NULL,
        NULL,
        NULL
};
#endif

#if PY_MAJOR_VERSION >= 3
PyMODINIT_FUNC
PyInit_cld(void) {
#else
PyMODINIT_FUNC
initcld() {
#endif

#if PY_MAJOR_VERSION >= 3
  PyObject *m = PyModule_Create(&moduledef);
  if (m == NULL) {
    return NULL;
  }
#else
  PyObject *m = Py_InitModule("cld", CLDMethods);
  if (m == NULL) {
    return;
  }
#endif


  // Set module-global ENCODINGS tuple:
  PyObject* pyEncs = PyTuple_New(NUM_ENCODINGS);
  for(int encIDX=0;encIDX<NUM_ENCODINGS;encIDX++) {
    PyTuple_SET_ITEM(pyEncs, encIDX, PYSTR(cld_encoding_info[encIDX].name));
  }
  // Steals ref:
  PyModule_AddObject(m, "ENCODINGS", pyEncs);

  // Set module-global LANGUAGES tuple:
  PyObject* pyLangs = PyTuple_New(NUM_LANGUAGES);
  for(int langIDX=0;langIDX<NUM_LANGUAGES;langIDX++) {
    PyObject* pyLang = Py_BuildValue("(zz)",
                                     LanguageName((Language) langIDX),
                                     LanguageCode((Language) langIDX));
    PyTuple_SET_ITEM(pyLangs, langIDX, pyLang);
  }
  // Steals ref:
  PyModule_AddObject(m, "LANGUAGES", pyLangs);

  // Set module-global EXTERNAL_LANGUAGES tuple:
  const int numExtLangs = EXT_NUM_LANGUAGES - EXT_LANGUAGE_BASE; // see ext_lang_enc.h
  PyObject* pyExtLangs = PyTuple_New(numExtLangs);
  for(int langIDX=EXT_LANGUAGE_BASE;langIDX<EXT_NUM_LANGUAGES;langIDX++) {
    PyObject* pyLang = Py_BuildValue("(zz)",
                                     ExtLanguageName((Language) langIDX),
                                     ExtLanguageCode((Language) langIDX));
    PyTuple_SET_ITEM(pyExtLangs, langIDX - EXT_LANGUAGE_BASE, pyLang);
  }
  // Steals ref:
  PyModule_AddObject(m, "EXTERNAL_LANGUAGES", pyExtLangs);

  // Set module-global DETECTED_LANGUAGES tuple:
  // MKM: NOTE I reverse engineered this list from the unit
  // test!!  It has all languages ever detected by the test

  PyObject* pyDetLangs = PyTuple_New(75);
  PyTuple_SET_ITEM(pyDetLangs, 0, PYSTR("AFRIKAANS"));
  PyTuple_SET_ITEM(pyDetLangs, 1, PYSTR("ALBANIAN"));
  PyTuple_SET_ITEM(pyDetLangs, 2, PYSTR("AMHARIC"));
  PyTuple_SET_ITEM(pyDetLangs, 3, PYSTR("ARABIC"));
  PyTuple_SET_ITEM(pyDetLangs, 4, PYSTR("ARMENIAN"));
  PyTuple_SET_ITEM(pyDetLangs, 5, PYSTR("AZERBAIJANI"));
  PyTuple_SET_ITEM(pyDetLangs, 6, PYSTR("BASQUE"));
  PyTuple_SET_ITEM(pyDetLangs, 7, PYSTR("BELARUSIAN"));
  PyTuple_SET_ITEM(pyDetLangs, 8, PYSTR("BENGALI"));
  PyTuple_SET_ITEM(pyDetLangs, 9, PYSTR("BULGARIAN"));
  PyTuple_SET_ITEM(pyDetLangs, 10, PYSTR("BURMESE"));
  PyTuple_SET_ITEM(pyDetLangs, 11, PYSTR("CATALAN"));
  PyTuple_SET_ITEM(pyDetLangs, 12, PYSTR("CHEROKEE"));
  PyTuple_SET_ITEM(pyDetLangs, 13, PYSTR("CROATIAN"));
  PyTuple_SET_ITEM(pyDetLangs, 14, PYSTR("CZECH"));
  PyTuple_SET_ITEM(pyDetLangs, 15, PYSTR("Chinese"));
  PyTuple_SET_ITEM(pyDetLangs, 16, PYSTR("ChineseT"));
  PyTuple_SET_ITEM(pyDetLangs, 17, PYSTR("DANISH"));
  PyTuple_SET_ITEM(pyDetLangs, 18, PYSTR("DHIVEHI"));
  PyTuple_SET_ITEM(pyDetLangs, 19, PYSTR("DUTCH"));
  PyTuple_SET_ITEM(pyDetLangs, 20, PYSTR("ENGLISH"));
  PyTuple_SET_ITEM(pyDetLangs, 21, PYSTR("ESTONIAN"));
  PyTuple_SET_ITEM(pyDetLangs, 22, PYSTR("FINNISH"));
  PyTuple_SET_ITEM(pyDetLangs, 23, PYSTR("FRENCH"));
  PyTuple_SET_ITEM(pyDetLangs, 23, PYSTR("GALICIAN"));
  PyTuple_SET_ITEM(pyDetLangs, 24, PYSTR("GEORGIAN"));
  PyTuple_SET_ITEM(pyDetLangs, 25, PYSTR("GERMAN"));
  PyTuple_SET_ITEM(pyDetLangs, 26, PYSTR("GREEK"));
  PyTuple_SET_ITEM(pyDetLangs, 27, PYSTR("GUJARATI"));
  PyTuple_SET_ITEM(pyDetLangs, 28, PYSTR("HAITIAN_CREOLE"));
  PyTuple_SET_ITEM(pyDetLangs, 29, PYSTR("HEBREW"));
  PyTuple_SET_ITEM(pyDetLangs, 30, PYSTR("HINDI"));
  PyTuple_SET_ITEM(pyDetLangs, 31, PYSTR("HUNGARIAN"));
  PyTuple_SET_ITEM(pyDetLangs, 32, PYSTR("ICELANDIC"));
  PyTuple_SET_ITEM(pyDetLangs, 33, PYSTR("INDONESIAN"));
  PyTuple_SET_ITEM(pyDetLangs, 34, PYSTR("INUKTITUT"));
  PyTuple_SET_ITEM(pyDetLangs, 35, PYSTR("IRISH"));
  PyTuple_SET_ITEM(pyDetLangs, 36, PYSTR("ITALIAN"));
  PyTuple_SET_ITEM(pyDetLangs, 37, PYSTR("Japanese"));
  PyTuple_SET_ITEM(pyDetLangs, 38, PYSTR("KANNADA"));
  PyTuple_SET_ITEM(pyDetLangs, 39, PYSTR("KHMER"));
  PyTuple_SET_ITEM(pyDetLangs, 40, PYSTR("Korean"));
  PyTuple_SET_ITEM(pyDetLangs, 41, PYSTR("LAOTHIAN"));
  PyTuple_SET_ITEM(pyDetLangs, 42, PYSTR("LATVIAN"));
  PyTuple_SET_ITEM(pyDetLangs, 43, PYSTR("LITHUANIAN"));
  PyTuple_SET_ITEM(pyDetLangs, 44, PYSTR("MACEDONIAN"));
  PyTuple_SET_ITEM(pyDetLangs, 45, PYSTR("MALAY"));
  PyTuple_SET_ITEM(pyDetLangs, 46, PYSTR("MALAYALAM"));
  PyTuple_SET_ITEM(pyDetLangs, 47, PYSTR("MALTESE"));
  PyTuple_SET_ITEM(pyDetLangs, 48, PYSTR("NORWEGIAN"));
  PyTuple_SET_ITEM(pyDetLangs, 49, PYSTR("ORIYA"));
  PyTuple_SET_ITEM(pyDetLangs, 50, PYSTR("PERSIAN"));
  PyTuple_SET_ITEM(pyDetLangs, 51, PYSTR("POLISH"));
  PyTuple_SET_ITEM(pyDetLangs, 52, PYSTR("PORTUGUESE"));
  PyTuple_SET_ITEM(pyDetLangs, 53, PYSTR("PUNJABI"));
  PyTuple_SET_ITEM(pyDetLangs, 54, PYSTR("ROMANIAN"));
  PyTuple_SET_ITEM(pyDetLangs, 55, PYSTR("RUSSIAN"));
  PyTuple_SET_ITEM(pyDetLangs, 56, PYSTR("SERBIAN"));
  PyTuple_SET_ITEM(pyDetLangs, 57, PYSTR("SINHALESE"));
  PyTuple_SET_ITEM(pyDetLangs, 58, PYSTR("SLOVAK"));
  PyTuple_SET_ITEM(pyDetLangs, 59, PYSTR("SLOVENIAN"));
  PyTuple_SET_ITEM(pyDetLangs, 60, PYSTR("SPANISH"));
  PyTuple_SET_ITEM(pyDetLangs, 61, PYSTR("SWAHILI"));
  PyTuple_SET_ITEM(pyDetLangs, 62, PYSTR("SWEDISH"));
  PyTuple_SET_ITEM(pyDetLangs, 63, PYSTR("SYRIAC"));
  PyTuple_SET_ITEM(pyDetLangs, 64, PYSTR("TAGALOG"));
  PyTuple_SET_ITEM(pyDetLangs, 65, PYSTR("TAMIL"));
  PyTuple_SET_ITEM(pyDetLangs, 66, PYSTR("TELUGU"));
  PyTuple_SET_ITEM(pyDetLangs, 67, PYSTR("THAI"));
  PyTuple_SET_ITEM(pyDetLangs, 68, PYSTR("TIBETAN"));
  PyTuple_SET_ITEM(pyDetLangs, 69, PYSTR("TURKISH"));
  PyTuple_SET_ITEM(pyDetLangs, 70, PYSTR("UKRAINIAN"));
  PyTuple_SET_ITEM(pyDetLangs, 71, PYSTR("URDU"));
  PyTuple_SET_ITEM(pyDetLangs, 72, PYSTR("VIETNAMESE"));
  PyTuple_SET_ITEM(pyDetLangs, 73, PYSTR("WELSH"));
  PyTuple_SET_ITEM(pyDetLangs, 74, PYSTR("YIDDISH"));

  // Steals ref:
  PyModule_AddObject(m, "DETECTED_LANGUAGES", pyDetLangs);
  
  CLDError = PyErr_NewException((char *) "cld.error", NULL, NULL);
  // Steals ref:
  PyModule_AddObject(m, "error", CLDError);

#if PY_MAJOR_VERSION >= 3
  return m;
#endif
}

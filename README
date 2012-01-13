# CLD - Compact Language Detector

This package contains the CLD (Compact Language Detection) library, extracted from the source code for Google's Chromium library at [http://src.chromium.org/svn/trunk/src/third_party/cld](http://src.chromium.org/viewvc/chrome/trunk/src/third_party/cld), specifically revision 105735. The original extraction was done by [Mike McCandless](http://code.google.com/p/chromium-compact-language-detector) and was altered to improve the build and packaging as well as add new bindings for various languages.

The LICENSE is the same as Chromium's LICENSE and is included in the LICENSE file for reference.

# Installing the C++ library

## Prerequisites

Building the C++ library requires a C++ compiler (duh) as well as `pkg-config` so future programs can locate the needed dependancies.

## Building

The shared C++ library can be built from source using the following commands:

    $ git clone git://github.com/mzsanford/cld.git
    $ cd cld
    $ ./configure
    $ make
    $ make check # optional. Runs the tests

## Installing

Once built from source:

    $ make install

Or, once my Homebrew branch merges, Mac OSX users of Homebrew can build and install via:

    $ brew install libcld

# Ports

None of the ports are 100% completed yet but the preliminary APIs are introduced below

## Ruby

### Installing

    # Coming Soon!
    $ gem install cld

### Example

    detector = CLD::Detector.new
    result = detector.detect_language("I'm a little teapot.")
    puts result.probable_language.code
    #=> 'en'

### Documentation

Full RDoc documentation is at [http://mzsanford.github.com/cld/ports/ruby/rdoc/index.html](http://mzsanford.github.com/cld/ports/ruby/rdoc/index.html) and
includes even more examples.

## Node

### Installing

    # Coming soon!
    $ npm install cld

### Example

    // TODO: This will change when npm is working correctly.
    var LanguageDetector = require("./build/Release/languagedetector.node").LanguageDetector;
    var detector = new LanguageDetector();

    // simple: result is "en"
    detector.detectSync("This is my sample text")
    
    // complex:
    detector.detect("I am simply English", function(result) {
      // result.languageCode => "en"
    });

### Documentation

## Java

### Installing

### Example

### Documentation

## Python

### Installing

### Example

### Documentation


# Original notes on the Python library (plus Markdown)

## USING THE PYTHON LIBRARY

Once you've compiled & installed the Python bindings detection is easy.

First, you must get your content (plain text or HTML) encoded into UTF8 bytes.  Then, detect like this:

    topLanguageName, topLanguageCode, isReliable, textBytesFound, details = cld.detect(bytes)

The code and name of the top language is returned.  isReliable is True
if the top language is much better than 2nd best language.
textBytesFound tells you how many actual bytes CLD analyzed (after
removing HTML tags, collapsing areas of too-many-spaces, etc.).
details has an entry per top 3 languages that matched, that includes
the percent confidence of the match as well as a separate normalized
score.

The detect method takes optional params:

  * `isPlainText` (default is False): set to True if you know your bytes
    don't have any XML/HTML markup

  * `includeExtendedLanguages` (default is True): set to False to
    exclude "extended" languages added by Google

  * `hintTopLevelDomain` (default is None): set to the last part of the
    domain name that the content came from (for example if the URL was
    http://www.krasnahora.cz, pass the string 'cz').  This gives a
    hint that can bias the detector somewhat.

  * `hintLanguageCode` (default is None): set to the possible language.
    For example, if the web-server declared the language, or the
    content itself embedded an http-equiv meta tag declaring the
    language, pass this (for example, "it" for Italian).  This gives a
    hint that can bias the detector somewhat.

  * `hintEncoding` (default is None): set to the original encoding of
    the content (note you still must pass UTF-8 encoded bytes).  This
    gives a hint that can bias the detector somewhat.  NOTE: this is
    currently not working.

  * `pickSummaryLanguage` (default is False): if False, CLD will always
    return the top matching language as the answer.  If True, it will
    sometimes pick 2nd or 3rd match (for example, if English and X
    match, where X (not UNK) is big enough, assume the English is
    boilerplate and return X).  In simple testing accuracy seems to
    suffer a bit (XX to YY %) when this is True so I've defaulted to
    False.

  * `removeWeakMatches` (default is True): if a match isn't strong
    enough, delete it.  This ensures some amount of confidence when a
    language is returned.


The module exports these global constants:

  * `cld.ENCODINGS`: list of the encoding names CLD recognizes (if you
    provide hintEncoding, it must be one of these names).

  * `cld.LANGUAGES`: list of languages and their codes (if you provide
    hintLanguageCode, it must be one of the codes from these codes).

  * `cld.EXTERNAL_LANGUAGES`: list of external languages and their
    codes.  Note that external languages cannot be hinted, but may be
    matched if you pass includeExtendedLanguages=True (the default).

  * `cld.DETECTED_LANGUAGES`: list of all detectable languages, as best
    I can determine (this was reverse engineered from a unit test, ie
    it contains a language X if that language was tested and passes
    for at least one example text).

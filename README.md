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

Or, Mac OSX users of Homebrew can build and install via:

    $ brew install https://raw.github.com/mzsanford/homebrew/libcld/Library/Formula/libcld.rb

# Ports

None of the ports are 100% completed yet but the preliminary APIs are introduced below

## Ruby

### Prerequisites

The `libcld` C++ library must be installed (see above)

### Installing

    # 'gem install ...' in the near future
    $ git clone http://github.com/mzsanford/cld.git
    $ cd cld/ports/ruby
    $ rake gem
    $ gem install pkg/*gem

### Example

    require 'CLD'
    require 'pp' # just for illustration

    cld = CLD::Detector.new
    res = cld.detect_language('I am the very measure of a modern major general')

    pp res
    #<CLD::LanguageResult:0x007fb7728b6768
     @possible_languages=
      [#<CLD::PossibleLanguage:0x007fb7728b6628
        @language=#<CLD::Language:0x007fb7728b66a0 @code="en", @name="ENGLISH">,
        @raw_score=100.0,
        @score=52.6742301458671>],
     @probable_language=
      #<CLD::Language:0x007fb7728b6740 @code="en", @name="ENGLISH">,
     @reliable=0>

### Documentation

Full RDoc documentation is at [http://mzsanford.github.com/cld/ports/ruby/rdoc/index.html](http://mzsanford.github.com/cld/ports/ruby/rdoc/index.html) and
includes even more examples.

## Node

### Prerequisites

The `libcld` C++ library must be installed (see above)

### Installing

    # 'npm install ...' in the near future
    $ git clone http://github.com/mzsanford/cld.git
    $ cd cld/ports/node
    $ node-waf configure build
    $ npm install

### Example

    var LanguageDetector = require('languagedetector').LanguageDetector;
    var detector = new LanguageDetector();

    // Sync - Returns two letter language code of the most likely candidate language
    var simpleResult = detector.detectSync("This is my sample text");
    // Returns 'en' in this case

    // Async - Returns detailed result structure
    detector.detect("This is my sample text", function(result) {
      // 'result' contains:
      // { languageCode: 'en',
      //  reliable: false,
      //  details:
      //   [ { languageCode: 'en', normalizedScore: 20.25931928687196, percentScore: 64 },
      //     { languageCode: 'fr', normalizedScore: 8.221993833504625, percentScore: 36 },
      //     { languageCode: 'un', normalizedScore: 0, percentScore: 0 } ] }
    });

### Documentation

Both the `detectSync` and `detect` methods take an option second parameter that is a hash of options. The available options (and defaults) are:

  * `tld` (none): The TLD of the domain that the data came from. This is used as a hint for some ambiguous languages, for example the following snippet from there tests:

        var detector = new LanguageDetector();
        var ambig =  "  常用漢字  ";
        detector.detectSync(ambig)                  #=> "zh-TW"
        detector.detectSync(ambig, { tld: "cn" })   #=> "zh"
        detector.detectSync(ambig, { tld: "jp" })   #=> "ja"
                    
  * `html` (`false`):  The string to be processed HTML. If this is the case then markup will be ignored in the calculations.

  * `allowExtendedLanguages` (`true`): Return language from outside of the core set of supported languages (where wuality is not as good)

  * `pickSummaryLanguage` (`false`): If true then the summary language may not be the top match, based on some other factors.

  * `skipWeakMatches` (`false`): Include weak matches in the results


## Java

As a JNI library the Java port may require some environment settings to work correctly. For example on a fresh Ubuntu install I needed to install the Oracle JDK, set `JAVA_HOME` and `LD_LIBRARY_PATH` for linking and compilation to work correctly.

### Prerequisites

The `libcld` C++ library must be installed (see above). See the notes above about compilation and runtime linker environments.

### Installing

    # Maven repository information in the future
    $ git clone http://github.com/mzsanford/cld.git
    $ cd cld/ports/java
    # mvn test (optional)
    $ mvn install

### Example

    CompactLanguageDetector compactLanguageDetector = new CompactLanguageDetector();
    LanguageDetectionResult result = compactLanguageDetector.detect("This is my sample text");
    if (result.isReliable()) {
      // getProbableLocale returns a java.util.Locale
      System.out.println("Pretty sure that's " + result.getProbableLocale().getDisplayName());
    } else {
      for (LanguageDetectionCandidate candidate : result.getCandidates()) {
        System.out.println("Maybe it's " + candidate.getLocale().getDisplayName());
      }
    }

### Documentation

Full Javadocs are at [http://mzsanford.github.com/cld/ports/java/doc/apidocs](http://mzsanford.github.com/cld/ports/java/doc/apidocs).

## Python

### Prerequisites

The `libcld` C++ library must be installed (see above)

### Installing

    $ git clone http://github.com/mzsanford/cld.git
    $ cd cld/ports/python
    $ make install # This will prompt for your password

### Example

    import cld

    detectedLangName, detectedLangCode, isReliable, textBytesFound, details = cld.detect("This is my sample text", pickSummaryLanguage=True, removeWeakMatches=False)
    print '  detected: %s' % detectedLangName
    print '  reliable: %s' % (isReliable != 0)
    print '  textBytes: %s' % textBytesFound
    print '  details: %s' % str(details)

    # The output look lie so:
    #  detected: ENGLISH
    #  reliable: True
    #  textBytes: 25
    #  details: [('ENGLISH', 'en', 64, 20.25931928687196), ('FRENCH', 'fr', 36, 8.221993833504625)]

### Documentation

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

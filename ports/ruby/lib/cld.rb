
require 'cld_native'

# Compact Language Detector module
#
# TODO: I need a full-on README here
module CLD

  # Model class for a single language
  class Language
    # language code (+en+ for English, for example)
    attr_reader :code
    # language name (+ENGLISH+, for example)
    attr_reader :name
  end

  # Model for a possible language with the associated score information
  class PossibleLanguage
    # Language object for a possible language
    attr_reader :language
    # Normalized score for this possibility
    attr_reader :score
    # Raw score for the possibility (percentage)
    attr_reader :raw_score
  end
  
  # Result object from a language detection attempt
  class LanguageResult
    # The most likely Language for the provided tex
    attr_reader :probable_language
    # :nodoc:
    attr_reader :reliable
    # Array of all PossibleLanguage objects
    attr_reader :possible_languages
    
    # Boolean representing if the cld considers +probable_language+ reliable
    def reliable?
      !!reliable
    end
  end

  # Detect the language of a given string of text
  class Detector
    # Initialize and allocate a copy of the native C++ library
    def initialize
      @native = CLDNative.new
    end
  
    # Detect the language of +text+ using the provided +options+ (see below). For example:
    #
    #    detector = CLD::Detector.new
    #    result = detector.detect_language("I'm a little teapot.")
    #    puts result.probable_language.code
    #    #=> 'en'
    #
    # Or, you can pass a block which will be called with the result object:
    #
    #    detector = CLD::Detector.new
    #    detector.detect_language("I'm a little teapot.") do |result|
    #      puts result.probable_language.code
    #      #=> 'en'
    #    end
    #    
    #
    # The +options+ can include:
    # * +:html+           if the +text+ contains HTML that should be ignored
    # * +:all_languages+  test language outside of the core set (quality if not as good)
    # * +:weak_matches+   include weak matches in the results
    def detect_language(text, options = {}, &block)
      return nil if text == nil
      return nil if text =~ /^\s*$/

      if block_given?
        yield @native.detect_language(text, options)
      else
        @native.detect_language(text, options)
      end
    end
  end
end
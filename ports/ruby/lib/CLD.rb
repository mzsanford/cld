
require 'cld_native'

# Compact Language Detector module
module CLD

  # Model class for a single language
  class Language
    attr_reader :code, :name
  end

  # Model for a possible language with the associated score information
  class PossibleLanguage
    attr_reader :language, :score, :raw_score
  end
  
  # Result object from a language detection attempt
  class LanguageResult
    attr_reader :probable_language, :reliable, :possible_languages
  end

  # Detect the language of a given string of text
  class Detector
    # Initialize and allocate a copy of the native C++ library
    def initialize
      @native = CLDNative.new
    end
  
    # Detect the language of +text+. The +options+ can include:
    #
    # :html           if the +text+ contains HTML that should be ignored
    # :all_languages  test language outside of the core set (quality if not as good)
    # :weak_matches   include weak matches in the results
    def detect_language(text, options = {}, &block)
      if block_given?
        yield @native.detect_language(text, options)
      else
        @native.detect_language(text, options)
      end
    end
  end
end
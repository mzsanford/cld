
require 'cld_native'

module CLD
  class Language
    attr_accessor :code, :name
  end

  class PossibleLanguage
    attr_accessor :name, :score
  end
  
  class LanguageResult
    attr_accessor :probable_language, :reliable, :possible_languages
  end

  class Detector
    def initialize
      @native = CLDNative.new
    end
  
    def detect_language(text, options = {})
      @native.detect_language(text, options)
    end
  end
end
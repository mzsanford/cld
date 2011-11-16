
require 'cld'

text = ARGV[0] || "This is a test string in English"

cld = CLD::Detector.new
puts cld.detect_language(text).inspect

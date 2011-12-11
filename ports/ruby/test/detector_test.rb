require File.join(File.dirname(__FILE__), 'test_helper.rb')

class DetectorTest < Test::Unit::TestCase
  ExampleEnglish = "This is English test text"

  def setup
    @detector = CLD::Detector.new
  end
  
  def test_constructor_initalizes_native_component
    assert_not_nil(@detector.instance_variable_get(:@native), "Initialize should create @native member")
  end
  
  def test_detect_no_args
    result = @detector.detect_language(ExampleEnglish)
    assert_equal("en", result.probable_language.code)
  end
  
  def pending_test_detect_no_args_block
  end
end
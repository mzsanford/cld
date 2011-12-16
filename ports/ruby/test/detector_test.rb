require File.join(File.dirname(__FILE__), 'test_helper.rb')

class DetectorTest < Test::Unit::TestCase
  ExampleEnglish = "This is English test text"
  ExampleEnglishHTML = "<div>wow</div>"

  def setup
    @detector = CLD::Detector.new
  end
  
  def test_constructor_initalizes_native_component
    assert_not_nil(@detector.instance_variable_get(:@native), "Initialize should create @native member")
  end
  
  def test_detect_nil
    assert_nil @detector.detect_language(nil)
  end
  
  def test_detect_blank
    assert_nil @detector.detect_language("")
    assert_nil @detector.detect_language(" ")
    assert_nil @detector.detect_language("\t")
  end
  
  def test_detect_no_options
    result = @detector.detect_language(ExampleEnglish)
    assert_equal("en", result.probable_language.code)
  end
  
  def test_detect_no_options_block
    block_executed = false
    @detector.detect_language(ExampleEnglish) do |result|
      assert_equal("en", result.probable_language.code)
      block_executed = true
    end
    assert(block_executed, "Should have executed the block argument")
  end
  
  def test_option_html_true
    ignore_markup = @detector.detect_language(ExampleEnglishHTML, :html => true)
    assert_equal("en", ignore_markup.probable_language.code)
  end
  
  def test_options_html_false
    include_markup = @detector.detect_language(ExampleEnglishHTML, :html => false)    
    assert_nil(include_markup.probable_language, "Nothing probably about markup treated as data")
    assert_equal(1, include_markup.possible_languages.length, "One possibility should remain despite lack of confidence")
  end
  
  def test_option_all_languages
  end
  
  def test_option_weak_matches
  end
end
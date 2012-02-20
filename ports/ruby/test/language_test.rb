require File.join(File.dirname(__FILE__), 'test_helper.rb')

class LanguageTest < Test::Unit::TestCase
  def setup
    @language = CLD::Language.new
    @language.instance_variable_set(:@code, 'en')
    @language.instance_variable_set(:@name, 'ENGLISH')
  end

  def test_code_read_only
    assert_equal('en', @language.code)
    assert_raise(NoMethodError) do
      @language.code = 'ar'
    end
    assert_equal('en', @language.code)
  end
  
  def test_code_name_only
    assert_equal('ENGLISH', @language.name)
    assert_raise(NoMethodError) do
      @language.name = 'ARABIC'
    end
    assert_equal('ENGLISH', @language.name)
  end
end
require File.join(File.dirname(__FILE__), 'test_helper.rb')

class PossibleLanguageTest < Test::Unit::TestCase
  def setup
    @language = CLD::Language.new
    @language.instance_variable_set(:@code, 'en')
    @language.instance_variable_set(:@name, 'ENGLISH')

    @possible_language = CLD::PossibleLanguage.new
    @possible_language.instance_variable_set(:@language, @language)
    @possible_language.instance_variable_set(:@score, 1.1)
    @possible_language.instance_variable_set(:@raw_score, 100)
    # TODO: Setup values via set_ivar(?) for reading
  end

  def test_language_read_only
    assert_equal(@language, @possible_language.language)
    assert_raise(NoMethodError) do
      @possible_language.language = CLD::Language.new
    end
    assert_equal(@language, @possible_language.language)
  end
  
  def test_score_read_only
    assert_equal(1.1, @possible_language.score)
    assert_raise(NoMethodError) do
      @possible_language.score =  2.2
    end
    assert_equal(1.1, @possible_language.score)
  end
  
  def test_raw_score_read_only
    assert_equal(100, @possible_language.raw_score)
    assert_raise(NoMethodError) do
      @possible_language.raw_score = 50
    end
    assert_equal(100, @possible_language.raw_score)
  end
end
require 'test_helper.rb'

class PossibleLanguageTest < Test::Unit::TestCase
  def setup
    @possible_language = CLD::PossibleLanguage.new
    # TODO: Setup values via set_ivar(?) for reading
  end

  def test_language_read_only
    # error
    @possible_language.language = CLD::Language.new
  end
  
  def test_score_read_only
    # error
    @possible_language.score =  100
  end
  
  def test_raw_score_read_only
    # error
    @possible_language.raw_score = 1.0
  end
end
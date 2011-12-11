require 'test_helper.rb'

class LanguageTest < Test::Unit::TestCase
  def setup
    @language = CLD::Language.new
    # TODO: Setup values via set_ivar(?) for reading
  end

  def test_code_read_only
    # error
    @language.code = 'en'
  end
  
  def test_code_name_only
    # error
    @language.name = 'ENGLISH'
  end
end

require 'test_helper.rb'
class TestLanguage < Test::Unit::TestCase
  def setup
    @language = CLD::Language.new
  end

  def test_code_read_only
    @language.code = 'en'
  end
end
Gem::Specification.new do |s|
  s.name = 'cld'
  s.version = '0.2.0'

  s.summary = 'Compact Language Detector for ruby'
  s.description = 'Chromium language detection bindings for Ruby'

  s.homepage = 'https://github.com/mzsanford/cld'
  s.has_rdoc = true

  s.authors = ['Matt Sanford']
  s.email = ['matt@mzsanford.com']

  s.add_development_dependency 'rake-compiler', '0.7.6'
  s.extensions = ['ext/extconf.rb']
  s.require_paths = ['lib']

  s.files = `git ls-files`.split("\n")
end

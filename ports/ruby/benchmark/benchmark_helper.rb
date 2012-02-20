
require File.join(File.dirname(__FILE__), '..', 'lib', 'cld')
require 'cld'
require "benchmark"

class CLD::Benchmark
  
  def get_bench_methods
    self.methods.grep(/^bench_/)
  end
  
  def run_benchmark
    self.get_bench_methods.each do |meth|
      puts "========================"
      puts " Begin Benchmark #{meth.to_s}"
      self.send(meth)
      puts "========================"
    end
  end
end
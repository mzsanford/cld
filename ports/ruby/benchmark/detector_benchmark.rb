
require File.join(File.dirname(__FILE__), 'benchmark_helper.rb')

class DetectorBenchmark < CLD::Benchmark
  
  def bench_short_detection
    iter = 50000
    detector = CLD::Detector.new
    
    Benchmark.bm(7) do |x|
      x.report("en")    { iter.times { detector.detect_language("I am English") } }
      x.report("blank") { iter.times { detector.detect_language("") } }
      x.report("nil")   { iter.times { detector.detect_language(nil) } }
    end
  end
  
  def bench_alloc_versus_reuse
    iter = 100000
    detector = CLD::Detector.new
    
    Benchmark.bm(7) do |x|
      x.report("alloc") { iter.times { CLD::Detector.new.detect_language("I am English") } }
      x.report("reuse") { iter.times { detector.detect_language("I am English") } }
    end
  end
  
  def bench_html_option
    text = IO.read(File.join(File.dirname(__FILE__), 'data', 'eu.html'))
    iter = 10000
    detector = CLD::Detector.new
    
    Benchmark.bm(12) do |x|
      x.report(":html true")  { iter.times { detector.detect_language(text, :html => true) } }
      x.report(":html false") { iter.times { detector.detect_language(text, :html => false) } }
    end
  end
  
  def bench_data_by_size
    text_m = IO.read(File.join(File.dirname(__FILE__), 'data', 'english-m.txt'))
    text_l = IO.read(File.join(File.dirname(__FILE__), 'data', 'english-l.txt'))
    iter = 50000
    detector = CLD::Detector.new
    
    Benchmark.bm(12) do |x|
      x.report("medium")  { iter.times { detector.detect_language(text_m) } }
      x.report("large")   { iter.times { detector.detect_language(text_l) } }
    end
  end

end

## TODO: Make this auto-run
DetectorBenchmark.new.run_benchmark

var Benchmark = require("benchmark");
var suite = new Benchmark.Suite;


var path = require('path');
var LanguageDetector;
if (path.existsSync("./build/Release")) {
  LanguageDetector = require("./build/Release/languagedetector.node").LanguageDetector;
} else {
  LanguageDetector = require("./build/default/languagedetector.node").LanguageDetector;
}
var detector = new LanguageDetector();

// add tests
suite.add('Create#test', function() {
  new LanguageDetector().detectSync("This is my sample text")
})
.add('Reuse#test', function() {
  detector.detectSync("This is my sample text")
})
.add('ReuseAsync#test', function() {
  detector.detect("This is my sample text", function(res) {
    // NO-OP
  });
})
// add listeners
.on('cycle', function(event, bench) {
  console.log(String(bench));
})
.on('complete', function() {
  console.log('Fastest is ' + this.filter('fastest').pluck('name'));
})
// run async
.run({ 'async': true });
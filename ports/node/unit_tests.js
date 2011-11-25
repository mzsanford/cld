

var LanguageDetector = require("./build/Release/languagedetector.node").LanguageDetector;
var detector = new LanguageDetector();

exports['detect sync'] = {
	simple: function(test) {
		test.expect(2);
		test.equal(detector.detectSync("This is my sample text"), "en", "Simple English phrase should be identified as English");
		test.equal(detector.detectSync("Was gibt neues?"), "de", "Simple German phrase should be identified as German");
		test.done();
	},

	htmlOption: function(test) {
		test.expect(2);
		test.equal(detector.detectSync("<span>foo</span>", { html: true }), "en", "Should skip html when html=true");
		test.equal(detector.detectSync("<span>foo</span>", { html: false }), "ut", "Should include html with html=false");
		test.done();
	},

	tldHint: function(test) {
		test.expect(3);
		var ambig =  "  常用漢字  ";
		test.equal(detector.detectSync(ambig), "zh-TW");
		test.equal(detector.detectSync(ambig, { tld: "cn" }), "zh");
		test.equal(detector.detectSync(ambig, { tld: "jp" }), "ja");
		test.done();
	}
}; 

exports['detect async'] = {
	simple: function(test) {
		test.expect(1);
		detector.detect("I am simply English", function(result) {
			test.equal(result.languageCode, "en", "Async detection should correctly identify English without options");
			test.done();
		});
	},

	htmlText: function(test) {
		test.expect(1);
		detector.detect("<span>foo</span>", { html: true }, function(result) {
			test.equal(result.languageCode, "en");
			test.done();
		});
	},

	nonHtml: function(test) {
		test.expect(1);
		detector.detect("<span>foo</span>", { html: false }, function(result) {
			test.equal(result.languageCode, "ut");
			test.done();
		});
	}
};



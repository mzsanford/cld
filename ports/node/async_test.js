var ASYNC = require('async');
var CLD = new (require("./build/Release/cld.node").LanguageDetector)();


//str_repeat('Foo',3) => 'FooFooFoo'
function str_repeat(a,b){ for(var c="";;)if(b&1&&(c+=a),b>>=1)a+=a;else break;return c }


//CLD.detectSync()
function detect_v1(str,cb)
{
  var res = CLD.detectSync(str);

  cb(
    null,
    res && res !== 'un' ? res : false
  );
}

//CLD.detect()
function detect_v2(str,cb)
{
  CLD.detect(str,function(res)
  {
    cb(
      null,
      res && res.languageCode && res.languageCode !== 'un' ? res.languageCode : false
    );
  });
}

console.log('#Chars  | V1  | V2 ');
console.log('------- | --- | ---');
for(var i=1, i_max=100, str; i <= i_max; ++i)
{
  //str = str_repeat('Hans und Gretel gingen in den Wald, dort war es finster und auch so bitterkalt. ',i);
    str = str_repeat('Alle meine Entchen schwimmen auf dem See, den Kopf dann in das Wasser und blub. ',i);

  (function(str)
  {
    ASYNC.parallel(
    {
      v1: function(cb){ detect_v1(str,cb); },
      v2: function(cb){ detect_v2(str,cb); }
    },
    function(err,res)
    {
      console.log(str.length+' | '+res.v1+' | '+res.v2);
    });
  })(str);
}


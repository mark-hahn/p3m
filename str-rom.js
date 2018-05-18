// this compile strings.txt into strings-rom.asm and strings-rom.h

fs   = require('fs');

icons = { s: 2, q: 3,
          e: 4, t: 5, b: 6, a: 7,
          u: 8, d: 9}

eol = 1;

allStrings = {};
   
txt = fs.readFileSync('strings.txt', 'utf8');
lines = txt.split('\n');

hdrTxt  = "#ifndef STRINGS_H\n";
hdrTxt += "#define STRINGS_H\n";
hdrTxt += "\n";
hdrTxt += "enum string_names {\n";
hdrTxt += "";

offsets  = "const uint16 strRomOfs[] = {\n";
        
asm =  "PSECT stringsromsect,class=CODE,local,delta=2\n";
asm += "GLOBAL _stringsrom\n";
asm += "_stringsrom:\n";

var zero = "0".charCodeAt(0);
var romOfs = 0;

for(lineIdx = 0; lineIdx < lines.length; lineIdx++) {
   var line = lines[lineIdx];
   if(line.length === 0 || line[0] === '#') continue;
      
   offsets += "  " + romOfs + ",\n";

   parts = /^(\S*)\s*"(.*)"$/.exec(line);
   name = parts[1];
   str  = parts[2];
   
   if(allStrings[str]) {
     console.log("duplicate string:", str);
     break;
   }
   allStrings[str] = true;

   hdrTxt += "  " + name + ",\n";

   var num = 0;
   var addWord = function() {
      var hex = num.toString(16);
      while(hex.length < 4) hex = "0" + hex;
      asm += "  DW 0x" + hex + "\n"
      romOfs += 1;
      num = 0;
   }
   for(var idx = 0; idx < str.length; idx++) {
      var code = str.charCodeAt(idx);
      if (str[idx] === "\\") {
        code = icons[str[++idx]];
      };
      num = (num << 7) + code;    
      if(num > 127) addWord();
   }
   num = (num << 7) + eol;
   if(num < 127) num <<= 7;
   addWord();
}

hdrTxt += "}\n\n";
hdrTxt += offsets;
hdrTxt += "}\n\n";
hdrTxt += "#endif\n";

fs.writeFileSync('strings.h', hdrTxt );
fs.writeFileSync('strings-rom.asm', asm);

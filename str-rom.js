// this compile strings.txt into strings-rom.asm and strings-rom.h

fs   = require('fs');

txt = fs.readFileSync('strings.txt', 'utf8');
lines = txt.split('\n');

enumTxt  = "#ifndef STRINGSROM_H\n";
enumTxt += "#define STRINGSROM_H\n";
enumTxt += "\n";
enumTxt += "enum string_names {\n";
enumTxt = "";

asm =  "PSECT stringsromsect,class=CODE,local,delta=2\n";
asm += "GLOBAL _stringsrom\n";
asm += "_stringsrom:\n";

for(lineIdx = 0; lineIdx < lines.length; lineIdx++) {
   var line = lines[lineIdx];
   if(line.length === 0 || line[0] === '#') continue;
   
   parts = /^(\S*)\s*"(.*)"$/.exec(line);
   name = parts[1];
   str  = parts[2];
   
   enumTxt += "  " + name + ",\n";
   
   hex = "ffff";
   asm += "  DW 0x" + hex + "\n"
}
enumTxt += "}\n";
enumTxt += "\n";
enumTxt += "#endif\n";

fs.writeFileSync('strings-rom.h', enumTxt);
fs.writeFileSync('strings-rom.asm', asm);

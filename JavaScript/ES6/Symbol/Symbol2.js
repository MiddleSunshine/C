const COLOR_RED = Symbol("red");
const COLOR_YELLOW = Symbol("yellow");
const COLOR_BLUE = Symbol("blue");
 
function ColorException(message) {
   this.message = message;
   this.name = "ColorException";
}
function getConstantName(color) {
    switch (color) {
        case COLOR_RED :
            return "COLOR_RED";
        case COLOR_YELLOW :
            return "COLOR_YELLOW ";
        case COLOR_BLUE:
            return "COLOR_BLUE";
        default:
            throw new ColorException("Can't find this color");
    }
}
 
try {
   // 只能写成这样 var color = "red"; 是不行的
   var color = COLOR_RED;
   var colorName = getConstantName(color);
} catch (e) {
   var colorName = "unknown";
   console.log(e.message, e.name);
} 
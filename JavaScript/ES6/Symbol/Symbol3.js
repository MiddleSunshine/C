let yellow = Symbol("Yellow");
// 
let yellow1 = Symbol.for("Yellow");
let result1=yellow === yellow1;      // false
 
let yellow2 = Symbol.for("Yellow");
let result2=yellow1 === yellow2;     // true

console.log(result1);
console.log(result2);

// https://www.runoob.com/w3cnote/es6-symbol.html
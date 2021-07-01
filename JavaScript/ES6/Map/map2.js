var myMap = new Map();
myMap.set(0, "zero");
myMap.set(1, "one");
 
// 将会显示两个 logs。 一个是 "0 = zero" 另一个是 "1 = one"
myMap.forEach(function(value, key) {
  console.log(key + " = " + value);
}, myMap)
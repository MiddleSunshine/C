let sy=Symbol("key1");

let syObject={};

syObject[sy]="unique key with result";

console.log(syObject);
let sy2=Symbol("key1");
let syObject2={
    // 使用 Symbol 的时候，要用 []
    [sy2]:"object type"
}
// 两个值是不一样的
console.log(sy2==sy?1:2);
// 只有下面两个方法才能拿到这些值
console.log(Object.getOwnPropertySymbols(syObject));
console.log(Reflect.ownKeys(syObject));
var cu = require(__dirname + '/../build/default/binding');

var driverVersion = cu.DriverGetVersion();
console.log("Driver version: " + driverVersion);

var count = cu.DeviceGetCount();
console.log("Device count: " + count);
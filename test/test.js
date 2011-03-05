var cu = require(__dirname + '/../build/default/binding');

var driverVersion = cu.DriverGetVersion(); //cuDriverGetVersion()
console.log("Driver version: " + driverVersion);

var count = cu.DeviceGetCount(); //cuDeviceGetCount
console.log("Device count: " + count);


var device = new cu.CudaDevice();
//var device = new cu.DeviceGet(0); //cuDeviceGet(0)

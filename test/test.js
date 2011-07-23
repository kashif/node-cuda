var cu = require(__dirname + '/../build/default/binding');

//cuDriverGetVersion()
var driverVersion = cu.DriverGetVersion();
console.log("Driver version: " + driverVersion);

//cuDeviceGetCount
var count = cu.DeviceGetCount();
console.log("Device count: " + count);

//cuDeviceGet
var cuDevice = new cu.CudaDevice(0);

//cuDeviceGetName
console.log("Device name: " + cuDevice.GetName());
console.log("Device total mem: " + cuDevice.TotalMem())

//cuDeviceComputeCapability
var compute = cuDevice.ComputeCapability();
console.log("Device compute capability: major=" + compute[0] + " minor=" + compute[1]);

//cuCtxCreate
var cuCtx = new cu.CudaCtx(0, cuDevice);

//cuCtxDestroy
var error = cuCtx.Destroy();
console.log("Context destroyed with error code: " + error);

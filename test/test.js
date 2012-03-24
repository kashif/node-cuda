var cu = require(__dirname + '/../build/Release/cuda');

//cuDriverGetVersion()
var driverVersion = cu.DriverGetVersion();
console.log("Driver version: " + driverVersion);

//cuDeviceGetCount
var count = cu.DeviceGetCount();
console.log("Device count: " + count);

for (var i=0; i<count; i++) {
  //cuDeviceGet
  var cuDevice = new cu.Device(i);

  //cuDeviceGetName
  console.log("Device " + i + ":", cuDevice);
}

//cuCtxCreate
var cuCtx = new cu.Ctx(0, cuDevice);

//cuCtxSynchronize
var error = cuCtx.Synchronize();
console.log("Context synchronize with error code: " + error);

//cuCtxGetApiVersion
console.log("Context API version: " + cuCtx.GetApiVersion());


//cuMemAlloc
var cuMem = new cu.Mem();
error = cuMem.Alloc(100);
console.log("Mem Alloc with error code: " + error);

//cuMemFree
error = cuMem.Free();
console.log("Mem Free with error code: " + error);

//cuMemAllocPitch
var pitch = cuMem.AllocPitch(100, 100, 8);
console.log("Mem pitch of allocation in bytes: " + pitch);
cuMem.Free();

//cuCtxDestroy
error = cuCtx.Destroy();
console.log("Context destroyed with error code: " + error);

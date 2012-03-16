var cu = require(__dirname + '/../build/Release/cuda');

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

//cuCtxSynchronize
var error = cuCtx.Synchronize();
console.log("Context synchronize with error code: " + error);

//cuCtxGetApiVersion
console.log("Context API version: " + cuCtx.GetApiVersion());


//cuMemAlloc
var cuMem = new cu.CudaMem();
error = cuMem.Alloc(100);
console.log("Cuda Mem Alloc with error code: " + error);

//cuMemFree
error = cuMem.Free();
console.log("Cuda Mem Free with error code: " + error);

//cuMemAllocPitch
var pitch = cuMem.AllocPitch(100, 100, 8);
console.log("Cuda Mem pitch of allocation in bytes: " + pitch);
cuMem.Free();

//cuCtxDestroy
error = cuCtx.Destroy();
console.log("Context destroyed with error code: " + error);
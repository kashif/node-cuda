var cu = require(__dirname + '/../build/Release/cuda');

//cuDriverGetVersion
//cuDeviceGetCount
console.log("Node-cuda exports:", cu);

for (var i=0; i<cu.deviceCount; i++) {
  //cuDeviceGet
  var cuDevice = new cu.Device(i);

  //cuDeviceComputeCapability
  //cuDeviceGetName
  //cuDeviceTotalMem
  console.log("Device " + i + ":", cuDevice);
}


//cuCtxCreate
var cuCtx = new cu.Ctx(0, cu.Device(0));

//cuCtxGetApiVersion
console.log("Created context:", cuCtx);

//cuCtxSynchronize
var error = cuCtx.synchronize();
console.log("Context synchronize with error code: " + error);


//cuMemAlloc
var cuMem = cu.memAlloc(100);
console.log("Allocated 100 bytes:", cuMem);

//cuMemFree
error = cuMem.free();
console.log("Mem Free with error code: " + error);

//cuMemAllocPitch
var cuMem = cu.memAllocPitch(100, 100, 8);
console.log("Allocated 100x100 array of doubles:", cuMem);

//cuMemFree
error = cuMem.free();
console.log("Mem Free with error code: " + error);


//cuCtxDestroy
error = cuCtx.destroy();
console.log("Context destroyed with error code: " + error);

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
var error = cuMem.free();
console.log("Mem Free with error code: " + error);

//cuMemAllocPitch
var cuMem = cu.memAllocPitch(100, 100, 8);
console.log("Allocated 100x100 array of doubles:", cuMem);

//cuMemFree
var error = cuMem.free();
console.log("Mem Free with error code: " + error);


//cuModuleLoad
var cuModule = cu.moduleLoad("test/test.cubin");
console.log("Loaded module:", cuModule);

//cuModuleGetFunction
var cuFunction = cuModule.getFunction("helloWorld");
console.log("Got function:", cuFunction);

//cuLaunchKernel
var error = cuFunction.launch([3,1,1],[2,2,2]);
console.log("Launched kernel:", error);

//cuCtxDestroy
error = cuCtx.destroy();
console.log("Context destroyed with error code: " + error);

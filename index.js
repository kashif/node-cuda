module.exports = require(__dirname + '/build/Release/cuda');

// Type names follow the W3C typed array specs, not NodeJS's Buffer library

var typeByteSize = {
  "Uint8": 1,
  "Uint16": 2,
  "Uint32": 4,
  "Int8": 1,
  "Int16": 2,
  "Int32": 4,
  "Float32": 4,
  "Float64": 8,
  "DevicePtr": 8
};

var typeAlignment = {
  "Uint8": 1,
  "Uint16": 2,
  "Uint32": 4,
  "Int8": 1,
  "Int16": 2,
  "Int32": 4,
  "Float32": 4,
  "Float64": 8,
  "DevicePtr": 8
};

var typeBufferFunc = {
  "Uint8": "UInt8",
  "Uint16": "UInt16LE",
  "Uint32": "UInt32LE",
  "Int8": "Int8",
  "Int16": "Int16LE",
  "Int32": "Int32LE",
  "Float32": "FloatLE",
  "Float64": "DoubleLE"
}

function alignUp(offset, alignment) {
  return (((offset) + (alignment) - 1) & ~((alignment) - 1));
}

module.exports.prepareArguments = function (args) {
  var paramBufferSize = 0;
  
  for (var i in args) {
    var type = args[i].type;

    paramBufferSize = alignUp(paramBufferSize, typeAlignment[type]);
    
    if (typeof(typeByteSize[type]) != "number")
      throw "Invalid type given";

    paramBufferSize += typeByteSize[type];
  }

  var paramBuffer = new Buffer(paramBufferSize);

  var offset = 0;
  for (var i in args) {
    var type = args[i].type;
    
    offset = alignUp(offset, typeAlignment[type]);

    if (type == "DevicePtr") {
      args[i].value.copy(paramBuffer, offset);
    } else {
      paramBuffer["write" + typeBufferFunc[type]](args[i].value, offset);
    }

    offset += typeByteSize[type];
  }

  return paramBuffer;
}

module.exports.launch = function () {
  var func = arguments[0];
  var gridDim = arguments[1];
  var blockDim = arguments[2];
  var args = arguments[3];

  args = module.exports.prepareArguments(args);

  return func.launchKernel(gridDim, blockDim, args);
}

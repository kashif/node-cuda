{
  "targets": [
    {
      "target_name": "cuda",
      "sources": [ 
        "src/bindings.cpp",
        "src/ctx.cpp",
        "src/device.cpp",
        "src/function.cpp",
        "src/mem.cpp",
        "src/module.cpp"
        ],
      "libraries": [
        "-L/usr/local/cuda/lib -lcuda"
      ],
      "include_dirs": [
        "/usr/local/cuda/include"
      ],
    }
  ]
}
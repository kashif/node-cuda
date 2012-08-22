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
      'conditions': [
        [ 'OS=="mac"', {
          "link_settings": {
            "libraries": [
              '$(SDKROOT)/System/Library/Frameworks/CUDA.framework',
            ]
          }
        }],
        [ 'OS=="linux"', {
          "link_settings": {
            "libraries": [
              '-lcuda',
            ]
          }
        }]
      ],
      "include_dirs": [
        "/usr/local/cuda-5.0/include",
        "/usr/local/cuda/include"
      ],
    }
  ]
}
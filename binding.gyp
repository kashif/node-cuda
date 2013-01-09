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
        }],
        [ 'OS=="win"', {
          'conditions': [
            ['target_arch=="x64"',
              {
                'variables': { 'arch': 'x64' }
              }, {
                'variables': { 'arch': 'Win32' }
              }
            ],
          ],
          'variables': {
            'cuda_root%': '$(CUDA_PATH)'
          },
          'libraries': [ 
            '-l<(cuda_root)/lib/<(arch)/cuda.lib',
          ],
          "include_dirs": [
            "<(cuda_root)/include",
          ],
        }, {
          "include_dirs": [
            "/usr/local/cuda-5.0/include",
            "/usr/local/cuda/include"
          ],
        }]
      ]
    }
  ]
}
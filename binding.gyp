{
  "targets": [
    {
      "target_name": "cuda",
      "sources": [
        "src/bindings.cpp",
        # "src/ctx.cpp",
        "src/device.cpp",
        # "src/function.cpp",
        # "src/mem.cpp",
        # "src/module.cpp"
        ],
      "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ],
      'conditions': [
        [ 'OS=="mac"', {
          'libraries': ['-framework CUDA'],
          'include_dirs': ['/usr/local/include'],
          'library_dirs': ['/usr/local/lib']
        }],
        [ 'OS=="linux"', {
          'libraries': ['-lcuda'],
          'include_dirs': ['/usr/local/include'],
          'library_dirs': ['/usr/local/lib64','/usr/local/lib']
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
            "/usr/local/cuda/include"
          ],
        }]
      ]
    }
  ]
}

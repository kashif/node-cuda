import Options

srcdir = "."
blddir = "build"
VERSION = "0.1.0"

def set_options(opt):
  opt.tool_options("compiler_cxx")

def configure(conf):
  conf.check_tool("compiler_cxx")
  conf.check_tool("node_addon")

  if not conf.check(lib="cuda",
                    libpath=['/usr/local/cuda/lib', '/usr/lib64/nvidia-graphics-current'],
                    includes=['/usr/local/cuda/include'],
                    uselib_store="CUDA"):
    conf.fatal('Cannot find CUDA library.');

def build(bld):
    obj = bld.new_task_gen('cxx', 'shlib', 'node_addon')
    obj.target = "cuda"
    obj.source = "src/bindings.cpp src/ctx.cpp src/device.cpp src/function.cpp src/mem.cpp src/module.cpp"
    obj.uselib = "CUDA"

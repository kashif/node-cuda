import Options

srcdir = "."
blddir = "build"
VERSION = "0.0.1"

def set_options(opt):
  opt.tool_options("compiler_cxx")

def configure(conf):
  conf.check_tool("compiler_cxx")
  conf.check_tool("node_addon")

  if not conf.check_cfg(package='cuda', uselib_store='CUDA'):
    if not conf.check(lib="cuda",
                      libpath=['/usr/local/cuda/lib'],
                      includes=['/usr/local/cuda/include'],
                      uselib_store="CUDA"):
      conf.fatal('Cannot find CUDA library.');

def build(bld):
    obj = bld.new_task_gen('cxx', 'shlib', 'node_addon')
    obj.target = "binding"
    obj.source = "src/bindings.cpp src/cuda_device.cpp src/cuda_ctx.cpp"
    obj.uselib = "CUDA"
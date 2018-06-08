from distutils.core import setup, Extension
import sys
import subprocess

PY3K = sys.version_info >= (3, 0)

def pkgconfig_win(*packages, **kw):
    return { 'define_macros': [('WIN32',None)],
             'libraries': packages,
             'include_dirs': ['..'] }

def byte2str(input):
    if PY3K:
        return input.decode('utf-8')
    else:
        return str(input)

def pkgconfig(*packages):
    kw = {}
    flag_map = {'-I': 'include_dirs', '-L': 'library_dirs', '-l': 'libraries'}
    cmd = "pkg-config --libs --cflags %s" % ' '.join(packages)
    for token in subprocess.check_output(cmd, shell=True).split():
        k = byte2str(token[:2])
        v = byte2str(token[2:])
        kw[flag_map[k]] = [v]
    return kw

module = Extension(name='cld',
                   sources=['pycldmodule.cc'],
                   extra_compile_args=['-Wno-unused-local-typedef'],
                   **pkgconfig('cld'))

setup(name='cld',
      version='0.031415',
      description='Python bindings around Google Chromium\'s embedded compact language detection library',
      ext_modules = [module])

from distutils.core import setup, Extension
import commands

def pkgconfig(*packages, **kw):
    flag_map = {'-I': 'include_dirs', '-L': 'library_dirs', '-l': 'libraries'}
    for token in commands.getoutput("pkg-config --libs --cflags %s" % ' '.join(packages)).split():
        kw.setdefault(flag_map.get(token[:2]), []).append(token[2:])
    return kw

module = Extension('cld',
                   ['pycldmodule.cc'],
                   **pkgconfig('cld'))

setup(name='cld',
      version='0.031415',
      description='Python bindings around Google Chromium\'s embedded compact language detection library',
      ext_modules = [module])

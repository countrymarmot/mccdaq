#!/usr/bin/env python
"""Build  script for mccdaq.

unzip mccdaq-x.x.zip
>>>> setup.py install

mccdaq-x.x.win32-py2.x.exe
>>>> setup.py bdist_wininst --bitmap mccdaq.bmp
"""

from distutils.core import setup, Extension
import os, re, sys, string

VERSION_MAJOR = 0
VERSION_MINOR = 2
mccdaq_version = str(VERSION_MAJOR) + "." + str(VERSION_MINOR)


ext_modules = Extension('_mccdaq',
                        sources = ['src/win32/_mccdaq.c'],
                        libraries = ['cbw32'],
                        #libraries = ['src/win32/cbw32.lib'],
                        library_dirs = ['src/win32'],
                    )

setup(
    name = "mccdaq",
    version = mccdaq_version,
    description = "USB-DAQ interface MCCDAQ .",
    author = "Philippe Dalet",
    author_email = "philippe.dalet@ac-toulouse.fr",
    url = "http://gpib82357a.sourceforge.net/mccdaq.htm", 
    download_url  = "http://sourceforge.net/projects/gpib82357a/" , 
    long_description =
'''MCCDAQ is an interface USB-DAQ running only on windows (XP pro,W2K,vista)
- Connect MCCDAQ (USB-1208LS) on USB port
- Install driver (see CDROM for MCCDAQ) 8.6
- Install this python package mccdaq.
''',
    
    packages    = ["mccdaq"],
    license="Python",
    platforms="Windows",
    classifiers=[
          'Development Status :: 5 - Production/Stable',
          'Environment :: Console',
          'Intended Audience :: Developers',
          'Intended Audience :: Science/Research',
          'License :: OSI Approved :: Python Software Foundation License',
          'Operating System :: Microsoft :: Windows',
          'Programming Language :: Python',
          'Topic :: Scientific/Engineering :: Interface Engine/Protocol Translator',
          'Topic :: Software Development :: Libraries :: Python Modules',
          ],

    data_files=[
                ('doc/mccdaq',['doc/mccdaq.bmp'],['doc/USB-1208LS_block.pdf'],
                ['doc/USB-1208LS_pins.pdf']
                )
               ],    
    ext_modules = [ext_modules]
    )




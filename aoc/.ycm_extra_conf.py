import os

DIR_OF_THIS_SCRIPT = os.path.abspath(os.path.dirname( __file__ ))

flags = [
    '-x', 'c++', 
    '-Wall',
    '-Wextra',
    '-std=c++20',
    '-isystem', '~/.ycm-extras/fmt-8.0.1/include',
]

def Settings(**kwargs):
    return {
        "flags": flags,
    }

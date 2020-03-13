"""
    otgu --- An OpenTURNS module
    ==================================

    Contents
    --------
      'otgu' is a module for OpenTURNS

"""

import sys
if sys.platform.startswith('win'):
    # this ensures OT dll is loaded
    import openturns

from .otgu import *

__version__ = '0.0'


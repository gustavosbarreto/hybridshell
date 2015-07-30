# Copyright (c) 2015 Piotr Tworek. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

{
  'variables': {
    'rcc_file%': '',
    'resources%': [],
  },
  'inputs': [
    '<@(resources)',
    '<(rcc_file)',
  ],
  'outputs': [
    '<(rcc_output)',
  ],
  'action': [
    'rcc',
    '-o', 'rcc_<(rcc_output)',
    '-name', '<(rcc_name)',
    '<(rcc_file)',
  ],
}


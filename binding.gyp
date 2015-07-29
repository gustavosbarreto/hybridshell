{
  'targets': [
    {
      'target_name': 'qt',
      'sources': [
        'src/qt.cc', 
        'src/QtGui/qapplication.cc',
        'src/QtWebEngine/qwebengineview.cc'
      ],
      'conditions': [
        ['OS=="mac"', {
          'include_dirs': [
            'deps/qt-4.8.0/darwin/x64/include',
            'deps/qt-4.8.0/darwin/x64/include/QtCore',
            'deps/qt-4.8.0/darwin/x64/include/QtGui',
            'deps/qt-4.8.0/darwin/x64/include/QtTest'
          ],
          'libraries': [
            # TODO: fix node-gyp behavior that requires ../
            '../deps/qt-4.8.0/darwin/x64/lib/QtCore.framework/QtCore', 
            '../deps/qt-4.8.0/darwin/x64/lib/QtGui.framework/QtGui', 
            '../deps/qt-4.8.0/darwin/x64/lib/QtTest.framework/QtTest'
          ],
        }],
        ['OS=="linux"', {
          'cflags': [
            '<!@(pkg-config --cflags Qt5Core Qt5Gui Qt5Widgets Qt5WebEngineWidgets)'
          ],
          'ldflags': [
            '<!@(pkg-config --libs-only-L --libs-only-other Qt5Core Qt5Gui Qt5Widgets Qt5WebEngineWidgets)'
          ],
          'libraries': [
            '<!@(pkg-config --libs-only-l Qt5Core Qt5Gui Qt5Widgets Qt5WebEngineWidgets)'
          ]
        }],
        ['OS=="win"', {
          'include_dirs': [
              'deps/qt-4.8.0/win32/ia32/include',
              'deps/qt-4.8.0/win32/ia32/include/QtCore',
              'deps/qt-4.8.0/win32/ia32/include/QtGui',
              'deps/qt-4.8.0/win32/ia32/include/QtTest',
          ],
          'libraries': [
              # TODO: fix node-gyp behavior that requires ../
              '../deps/qt-4.8.0/win32/ia32/lib/QtCore4.lib',
              '../deps/qt-4.8.0/win32/ia32/lib/QtGui4.lib',
              '../deps/qt-4.8.0/win32/ia32/lib/QtTest4.lib'
          ]
        }]        
      ]
    }
  ]
}

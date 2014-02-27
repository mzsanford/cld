{
  "targets": [
    {
      "target_name": "languagedetector",
      "sources": [ "languagedetector.cc" ],
      "defines": [
        "_FILE_OFFSET_BITS=64",
        "_LARGEFILE_SOURCE",
        "CLD_WINDOWS"
      ],
      'include_dirs': [
        '<!@(pkg-config cld --cflags-only-I | sed s/-I//g)'
      ],
      'libraries': [
        '<!@(pkg-config cld --libs)'
      ]
    }
  ]
}

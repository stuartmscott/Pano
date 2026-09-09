#!/bin/bash

set -e 

header_dir=include/PanoNotoSans
mkdir -p ${header_dir}

for font in "NotoSans-Regular" "NotoSans-Bold" "NotoSans-Italic" "NotoSans-BoldItalic" "NotoSansMath-Regular"
do
    echo "${font}"
    underscore="$(echo "${font}" | tr '-' '_')"
    uppercase=$(echo "${underscore}" | tr '[:lower:]' '[:upper:]')
    guard="FONT_NOTO_INCLUDE_PANONOTOSANS_${uppercase}_H_"
    lowercase=$(echo "${underscore}" | tr '[:upper:]' '[:lower:]')
    filename="${header_dir}/${lowercase}.h"
    echo "#ifndef ${guard}" > "${filename}"
    echo "#define ${guard}" >> "${filename}"
    xxd -n "${lowercase}" -i "data/${font}.ttf" >> "${filename}"
    echo "#endif  // ${guard}" >> "${filename}"
done

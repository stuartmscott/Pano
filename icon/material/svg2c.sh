#!/bin/bash

set -e 

header_dir=include/PanoMaterialIcon
mkdir -p ${header_dir}

icons=(
    "arrow_drop_down"
    "check_box_checked"
    "check_box_unchecked"
    "pano"
    "radio_button_selected"
    "radio_button_unselected"
)

for icon in "${icons[@]}"
do
    echo "${icon}"
    uppercase=$(echo "${icon}" | tr '[:lower:]' '[:upper:]')
    guard="ICON_MATERIAL_INCLUDE_PANOMATERIALICON_${uppercase}_H_"
    filename="${header_dir}/${icon}.h"
    echo "#ifndef ${guard}" > "${filename}"
    echo "#define ${guard}" >> "${filename}"
    xxd -n "${icon}" -i "data/${icon}.svg" >> "${filename}"
    echo "#endif  // ${guard}" >> "${filename}"
done

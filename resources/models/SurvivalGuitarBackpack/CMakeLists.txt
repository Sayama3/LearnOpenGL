cmake_minimum_required(VERSION 3.24)

configure_file(scene.bin scene.bin COPYONLY)
configure_file(scene.gltf scene.gltf COPYONLY)
add_subdirectory(textures)
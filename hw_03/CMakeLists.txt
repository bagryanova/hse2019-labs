cmake_minimum_required(VERSION 3.8)

project(hw_03)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include_directories("include/")

add_executable(hw_03
    include/ByteWriter.hpp
    include/CLI.hpp
    include/Statistics.hpp
    include/Trie.hpp
    include/Huffman.hpp
    include/HuffmanArchiver.hpp
    include/ByteReader.hpp
    src/main.cpp
    src/ByteWriter.cpp
    src/CLI.cpp
    src/Statistics.cpp
    src/Trie.cpp
    src/Huffman.cpp
    src/HuffmanArchiver.cpp
    src/ByteReader.cpp
)

set_target_properties(hw_03 PROPERTIES COMPILE_FLAGS "-O2")

add_executable(test_hw_03
    include/ByteWriter.hpp
    include/CLI.hpp
    include/Statistics.hpp
    include/Trie.hpp
    include/Huffman.hpp
    include/HuffmanArchiver.hpp
    include/ByteReader.hpp
    src/ByteWriter.cpp
    src/CLI.cpp
    src/Statistics.cpp
    src/Trie.cpp
    src/Huffman.cpp
    src/HuffmanArchiver.cpp
    src/ByteReader.cpp
    test/TestMain.cpp
    test/TestCLI.cpp
    test/TestByteWriter.cpp
    test/TestByteReader.cpp
    test/TestHuffman.cpp
    test/TestTrie.cpp
    test/TestHuffmanArchiver.cpp
)
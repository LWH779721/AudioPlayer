cmake_minimum_required(VERSION 2.8) 

PROJECT(AudioPlayerTest)

INCLUDE_DIRECTORIES(../smartaudioplayer/include) 

link_directories(${PROJECT_SOURCE_DIR}/../smartaudioplayer/)

ADD_EXECUTABLE(player_test player_test.cpp)  
TARGET_LINK_LIBRARIES(player_test smartaudioplayer)

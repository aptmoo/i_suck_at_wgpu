workspace "LearningApp"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "App"

group "Dependencies"
    include "Dependencies/BuildGLFW.lua"
group ""

include "App/BuildApp.lua"
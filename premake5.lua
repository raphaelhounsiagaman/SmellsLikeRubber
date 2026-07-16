workspace "SmellsLikeRubber"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }
    startproject "SmellsLikeRubber"

include "vendor/SlateEngine/Slate/Build-SlateEngine.lua"

include "SmellsLikeRubber/Build-SmellsLikeRubber.lua"


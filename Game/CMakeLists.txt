project(Game)

# D�finir les fichiers sources pour le dossier "Game"
#set(Game_SOURCES
   # game_file1.cpp
   # game_file2.cpp
    # ... Autres fichiers sources de "Game" ...
#)

# Cr�er l'ex�cutable pour "Game" en liant la biblioth�que "Engine"
add_executable(Game "./ecsmain.cpp") #${Game_SOURCES})

# Ajouter des options de compilation sp�cifiques pour "Game" si n�cessaire
target_compile_options(Game PUBLIC -Wall)

# Lier la biblioth�que "Engine" � l'ex�cutable "Game"
target_link_libraries(Game PRIVATE Engine)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Game PROPERTY CXX_STANDARD 20)
endif()
project(Game)

# Définir les fichiers sources pour le dossier "Game"
#set(Game_SOURCES
   # game_file1.cpp
   # game_file2.cpp
    # ... Autres fichiers sources de "Game" ...
#)

# Créer l'exécutable pour "Game" en liant la bibliothèque "Engine"
add_executable(Game "./ecsmain.cpp") #${Game_SOURCES})

# Ajouter des options de compilation spécifiques pour "Game" si nécessaire
target_compile_options(Game PUBLIC -Wall)

# Lier la bibliothèque "Engine" à l'exécutable "Game"
target_link_libraries(Game PRIVATE Engine)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Game PROPERTY CXX_STANDARD 20)
endif()
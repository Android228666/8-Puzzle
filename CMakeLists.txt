cmake_minimum_required (VERSION 3.8)

project ("PuzzleGame")

add_executable (PuzzleGame
	"PuzzleGame.cpp" 
	"Buttons/Button.cpp" 
	"Buttons/Tile.cpp" 
	"Buttons/RandomizeButton.cpp" 
	"Buttons/SetBoardButton.cpp" 
	"Buttons/BFSButton.cpp" 
	"Buttons/LDFSButton.cpp" 
	"PuzzleState.cpp" 
	"main.cpp"
)

set_property(TARGET PuzzleGame PROPERTY CXX_STANDARD 20)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(PuzzleGame PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
target_link_options(PuzzleGame PRIVATE /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup)

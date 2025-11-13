/*
** EPITECH PROJECT, 2025
** my_ftp
** File description:
** arcade
*/

#include "Core/Core.hpp"

void DisplayUsage()
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./arcade Libraries" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tLibraries\t\tlibrary in which the game will be played" << std::endl << std::endl;
    std::cout << "\tEscape Key\t\tClose the program" << std::endl;
    std::cout << "\tArrow Keys\t\tFor movements in game" << std::endl;
    std::cout << "\tSpace Key\t\tFor reset games" << std::endl;
    std::cout << "\tN Key\t\t\tFor graphical next library" << std::endl;
    std::cout << "\tP Key\t\t\tFor graphical previous library" << std::endl;
    std::cout << "\tG Key\t\t\tFor game next" << std::endl;
    std::cout << "\tB Key\t\t\tFor game previous" << std::endl;
    std::cout << "\tENTER Key\t\tFor validate choices in menu and action1" << std::endl;
    std::cout << "\tR Key\t\t\tFor action2" << std::endl;
    std::cout << "\tM Key\t\t\tFor going back to menu" << std::endl;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        DisplayUsage();
        return 84;
    }
    if (!std::filesystem::exists(argv[1])) {
        std::cout << "Error: " << argv[1] << "is not a library" << std::endl;
        return 84;
    }
    arcade::Core core(argv[1]);
    core.run();
}
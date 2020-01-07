// internal
#include "global.hpp"
#include "allSystem.hpp"
#include "world.hpp"

#define GL3W_IMPLEMENTATION

#include <gl3w.h>

// stlib
#include <chrono>
#include <iostream>
#include <entities/menu.hpp>
#include "levels.hpp"
#include "mainMenu.hpp"
#include "levelSelection.hpp"
#include "winLose.hpp"
#include "levelName.hpp"
#include "leaderboard.hpp"
#include "tutorialLevel.hpp"

using Clock = std::chrono::high_resolution_clock;

//World world;

AllSystem *syss = new AllSystem();

// Entry point
#undef main // LMAO A LIBRARY WAS REDEFINING MAIN??

int main(int argc, char *argv[]) {
    // init all systems
    syss->init();
    LevelName curLevel = LevelName::MAIN_MENU;
    // previous level only used for win lose page tracking levels
    LevelName preLevel = LevelName::NO_LEVEL;

    while (curLevel != LevelName::NO_LEVEL) {
        Levels levelsObj;
        // set up params for different levels
        if (!levelsObj.setLevelParam(curLevel, preLevel)) {
            std::cout << "Press any key to exit" << std::endl;
            std::cin.get();
            return EXIT_FAILURE;
        }
        // hard code for now, put this in a new function later
        // this block will be all system init
        syss->reset();
        syss->getSpawnSystem()->setSpawnLimits(levelsObj.getCurLimits());
        syss->getBossAISystem()->setSpawnLimits(levelsObj.getCurLimits());
        syss->getBossAISystem2()->setSpawnLimits(levelsObj.getCurLimits());
        syss->getShootingAISystem()->setSpawnLimits(levelsObj.getCurLimits());
        //____________________________MAINMENU_________________________________
        if (curLevel == LevelName::MAIN_MENU) {
            // mainMenu
            MainMenu mainMenu;
            if (!mainMenu.init({(float) width, (float) height})) {
                std::cout << "Press any key to exit" << std::endl;
                std::cin.get();
                return EXIT_FAILURE;
            }
            auto t_menu = Clock::now();
            while (!mainMenu.shouldClose() && !mainMenu.check_menu_over()) {
                glfwPollEvents();

                auto now = Clock::now();
                float elapsed_sec =
                        (float) (std::chrono::duration_cast<std::chrono::microseconds>(now - t_menu)).count() / 1000;
                t_menu = now;

                mainMenu.update(elapsed_sec);
                mainMenu.draw();
            }
            if (!mainMenu.check_menu_over() || mainMenu.checkIfExit()) {
                mainMenu.destroy();
                syss->destroy();
                return EXIT_SUCCESS;
            }
            switch (mainMenu.checkMode()) {
                case 0: {
                    curLevel = LevelName::LEVEL_SELECTION;
                    break;
                }
                case 1: {
                    curLevel = LevelName::SURVIVAL_MODE;
                    break;
                }
                case 2: {
                    curLevel = LevelName::TUTORIAL_LEVEL;
                    break;
                }
            }
            mainMenu.destroy();
        }
            // ________________________________LEVELSELECTION__________________________________
        else if (curLevel == LevelName::LEVEL_SELECTION) {
            // level selection page
            LevelSelection levelSelection;
            if (!levelSelection.init({(float) width, (float) height})) {
                std::cout << "Press any key to exit" << std::endl;
                std::cin.get();
                return EXIT_FAILURE;
            }
            auto t_level = Clock::now();
            while (!levelSelection.is_over() && !levelSelection.check_level_selection_over()) {
                glfwPollEvents();

                auto now = Clock::now();
                float elapsed_sec =
                        (float) (std::chrono::duration_cast<std::chrono::microseconds>(now - t_level)).count() / 1000;
                t_level = now;

                levelSelection.update(elapsed_sec);
                levelSelection.draw();
            }
            if (!levelSelection.check_level_selection_over()) {
                levelSelection.destroy();
                syss->destroy();
                return EXIT_SUCCESS;
            }
            levelSelection.reset_level_selection_over();
            LevelName chosenLevel = levelSelection.get_chosen_level();
            levelSelection.destroy();
            curLevel = chosenLevel;
        }
            // _____________________________VICTORY__________________________________
        else if (curLevel == LevelName::VICTORY_PAGE) {
            WinLose winLose;
            if (!winLose.init({(float) width, (float) height}, &levelsObj)) {
                std::cout << "Press any key to exit" << std::endl;
                std::cin.get();
                return EXIT_FAILURE;
            }
            auto t_winLose = Clock::now();
            while (!winLose.is_over() && !winLose.check_win_lose_over()) {
                glfwPollEvents();

                auto now = Clock::now();
                float elapsed_sec =
                        (float) (std::chrono::duration_cast<std::chrono::microseconds>(now - t_winLose)).count() / 1000;
                t_winLose = now;

                winLose.update(elapsed_sec);
                winLose.draw();
            }
            if (!winLose.check_win_lose_over()) {
                winLose.destroy();
                syss->destroy();
                return EXIT_SUCCESS;
            }
            winLose.reset_win_lose_over();
            LevelName nextLevel = winLose.get_next_level();
            winLose.destroy();
            curLevel = nextLevel;
        }
            // ______________________________DIE____________________________________
        else if (curLevel == LevelName::DEFEAT_PAGE) {
            WinLose winLose;
            if (!winLose.init({(float) width, (float) height}, &levelsObj)) {
                std::cout << "Press any key to exit" << std::endl;
                std::cin.get();
                return EXIT_FAILURE;
            }
            auto t_winLose = Clock::now();
            while (!winLose.is_over() && !winLose.check_win_lose_over()) {
                glfwPollEvents();

                auto now = Clock::now();
                float elapsed_sec =
                        (float) (std::chrono::duration_cast<std::chrono::microseconds>(now - t_winLose)).count() / 1000;
                t_winLose = now;

                winLose.update(elapsed_sec);
                winLose.draw();
            }
            if (!winLose.check_win_lose_over()) {
                winLose.destroy();
                syss->destroy();
                return EXIT_SUCCESS;
            }
            winLose.reset_win_lose_over();
            LevelName nextLevel = winLose.get_next_level();
            winLose.destroy();
            curLevel = nextLevel;
        }
            // __________________________________LEADERBOARD_________________________________
        else if (curLevel == LevelName::LEADERBOARD) {
            Leaderboard boardPage;
            if (!boardPage.init({(float) width, (float) height})) {
                std::cout << "Press any key to exit" << std::endl;
                std::cin.get();
                return EXIT_FAILURE;
            }
            auto t_winLose = Clock::now();
            while (!boardPage.is_over() && !boardPage.shouldClose()) {
                glfwPollEvents();

                auto now = Clock::now();
                float elapsed_sec =
                        (float) (std::chrono::duration_cast<std::chrono::microseconds>(now - t_winLose)).count() / 1000;
                t_winLose = now;

                boardPage.update(elapsed_sec);
                boardPage.draw();
            }

            if (boardPage.shouldClose()) {
                boardPage.destroy();
                syss->destroy();
                return EXIT_SUCCESS;
            }

            LevelName nextLevel = boardPage.get_next_level();
            boardPage.destroy();
            curLevel = nextLevel;
        } else if (curLevel == LevelName::TUTORIAL_LEVEL) {
            TutorialLevel tutorialLevel;
            if (!tutorialLevel.init({(float) width, (float) height}, &levelsObj)) {
                // Time to read the error message
                std::cout << "Press any key to exit" << std::endl;
                std::cin.get();
                return EXIT_FAILURE;
            }

            // __________________________________GAME_________________________________
            auto t_tutorial = Clock::now();
            // variable timestep loop.. can be improved (:
            while (!tutorialLevel.is_over()) {
                // Processes system messages, if this wasn't present the window would become unresponsive
                glfwPollEvents();
                // Calculating elapsed times in milliseconds from the previous iteration
                auto now = Clock::now();
                float elapsed_sec =
                        (float) (std::chrono::duration_cast<std::chrono::microseconds>(now - t_tutorial)).count() /
                        1000;
                t_tutorial = now;

                tutorialLevel.update(elapsed_sec);
                tutorialLevel.draw();
            }
            LevelName nextLevel = tutorialLevel.getNextLevel();
            syss->reset();
            tutorialLevel.destroy();
            curLevel = nextLevel;
        }
            // __________________________________GAME_________________________________
        else {
            World world;
            // game page
            if (!world.init({(float) width, (float) height}, &levelsObj)) {
                // Time to read the error message
                std::cout << "Press any key to exit" << std::endl;
                std::cin.get();
                return EXIT_FAILURE;
            }
            auto t_world = Clock::now();
            // variable timestep loop.. can be improved (:
            while (!world.is_over()) {
                // Processes system messages, if this wasn't present the window would become unresponsive
                glfwPollEvents();
                // Calculating elapsed times in milliseconds from the previous iteration
                auto now = Clock::now();
                float elapsed_sec =
                        (float) (std::chrono::duration_cast<std::chrono::microseconds>(now - t_world)).count() / 1000;
                t_world = now;

                world.update(elapsed_sec);
                world.draw();
            }
            LevelName nextLevel = world.getNextLevel();
            LevelName currentLevel = world.getCurrentLevel();
            syss->reset();
            world.destroy();
            // go to next level
            curLevel = nextLevel;
            preLevel = currentLevel;
        }
    }

    free(syss);
    return EXIT_SUCCESS;
}
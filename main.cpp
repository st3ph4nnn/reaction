#include "include/raylib.h"
#include "timer.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <thread>

std::string calculate_time(int time) {
    /* No switches?
  ⣞⢽⢪⢣⢣⢣⢫⡺⡵⣝⡮⣗⢷⢽⢽⢽⣮⡷⡽⣜⣜⢮⢺⣜⢷⢽⢝⡽⣝
 ⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇
⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏⠀
⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀
⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀
⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀
⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋
        ⠡⠩⡫⢿⣝⡻⡮⠀⠀⠀
    */

    if (time <= 150) return "You are insane.";
    if (time <= 350) return "Your time is average.";
    if (time <= 650) return "Your time is worse than average.";
    if (time <= 900) return "Your time is way worse than average.";
    if (time >= 900) return "You're old. You're really old."; // yeah.. we do a little bit of trolling
}

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(0, 0, "reaction");
    ToggleFullscreen();

    bool start;
    bool finished;
    bool failed = false;
    bool saved = false;

    int width = GetScreenWidth();
    int height = GetScreenHeight();

    timer time;

    int wait;

    std::ifstream fin;
    std::ofstream fout;

    int best;
    fin.open("save", std::ios::app);
    fin >> best;
    fin.close();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        if (!start) {
            DrawText("Press F11 to fullscreen", width / 2 - MeasureText("Press F11 to fullscreen", 60) / 2, height / 2 - 60, 60, BLACK);
            DrawText("Press ESC to quit", width / 2 - MeasureText("Press ESC to quit", 60) / 2, height / 2 + 40, 60, BLACK);
            DrawText("REACTION - made by stephan", width / 2 - MeasureText("REACTION - made by stephan", 40) / 2, height - 100, 40, BLACK);
            DrawText(("Best time: " + std::to_string(best) + "ms").c_str(), width / 2 - MeasureText(("Best time: " + std::to_string(best) + "ms").c_str(), 60) / 2, height / 2 - 150, 60, BLACK);

            if (failed)
                DrawText("Stop Cheating...", width / 2 - MeasureText("Stop Cheating...", 60) / 2, height / 2 - 350, 60, RED);

            DrawText("Press ENTER to start", width / 2 - MeasureText("Press ENTER to start", 80) / 2, height / 2 - 250, 80, BLACK);

            if (IsKeyPressed(KEY_F11))
                ToggleFullscreen();

            start = IsKeyPressed(KEY_ENTER) || IsKeyPressed(335);

            if (start)
                wait = GetRandomValue(100, 200);

            EndDrawing();
            continue;
        }

        failed = false;

        if (start && wait) {
            DrawRectangle(0, 0, width, height, RED);
            DrawText("Press any key when you see green...", width / 2 - MeasureText("Press any key when you see green...", 60) / 2, height / 2 - 30, 60, WHITE);

            int pressed = GetKeyPressed();

            if (pressed) {
                start = false;
                finished = false;
                failed = true;
                saved = false;
                EndDrawing();
                continue;
            }

            wait--;
            if (wait == 0)
                time.start_count();
            EndDrawing();
            continue;
        }

        DrawRectangle(0, 0, width, height, GREEN);

        if (!finished) {
            int pressed = GetKeyPressed();

            if (pressed) {
                finished = true;
                time.stop_count();
            }
        } else {
            fin.open("save", std::ios::app);
            fin >> best;
            fin.close();

            if (!saved && time.elapsedMilliseconds() < best) {
                fout.open("save");
                fout << time.elapsedMilliseconds();
                fout.close();
                saved = true;
            }

            DrawText((std::to_string(time.elapsedMilliseconds()) + "ms").c_str(), width / 2 - MeasureText((std::to_string(time.elapsedMilliseconds()) + "ms").c_str(), 130) / 2, height / 2 - 75, 130, BLACK);
            DrawText(calculate_time(time.elapsedMilliseconds()).c_str(), width / 2 - MeasureText(calculate_time(time.elapsedMilliseconds()).c_str(), 50) / 2, height / 2 + 100, 50, BLACK);
            DrawText("ENTER to restart", width / 2 - MeasureText("ENTER to restart", 60) / 2, height / 2 - 200, 60, BLACK);
            DrawText("ESC to quit", width / 2 - MeasureText("ESC to quit", 60) / 2, height / 2 - 300, 60, BLACK);
            DrawText(("Best time: " + std::to_string(best) + "ms").c_str(), width / 2 - MeasureText(("Best time: " + std::to_string(best) + "ms").c_str(), 60) / 2, height / 2 + 200, 60, BLACK);

            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(335)) {
                start = false;
                finished = false;
                saved = false;
            }
        }

        EndDrawing();
    }

    CloseWindow();
}

#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define PROFILE_COUNT 4

static const char *profiles[PROFILE_COUNT] = {
    "Vanilla (no mod)",
    "Classic Remix (demo)",
    "Challenge Mode (demo)",
    "Custom Profile (demo)"
};

static int selectedProfile = 0;

static void saveProfile(void)
{
    mkdir("sdmc:/3ds", 0777);
    mkdir("sdmc:/3ds/MarioLandMods", 0777);

    FILE *file = fopen(
        "sdmc:/3ds/MarioLandMods/selected.txt", "w"
    );

    if (file != NULL) {
        fprintf(file, "%s\n", profiles[selectedProfile]);
        fclose(file);
    }
}

int main(void)
{
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
    consoleInit(GFX_BOTTOM, NULL);

    while (aptMainLoop()) {
        hidScanInput();
        u32 keys = hidKeysDown();

        if (keys & KEY_UP) {
            selectedProfile =
                (selectedProfile + PROFILE_COUNT - 1)
                % PROFILE_COUNT;
        }

        if (keys & KEY_DOWN) {
            selectedProfile =
                (selectedProfile + 1) % PROFILE_COUNT;
        }

        if (keys & KEY_A) {
            saveProfile();
        }

        if (keys & KEY_START) {
            break;
        }

        consoleSelect(&topScreen);
        printf("\x1b[2J");
        printf("Mario Land Mod Launcher\n\n");
        printf("Homebrew profile selector\n\n");
        printf("Choose a profile on the bottom screen.\n");
        printf("Press A to save your selection.\n");
        printf("Press START to exit.\n");

        consoleSelect(&bottomScreen);
        printf("\x1b[2J");
        printf("Select Profile\n\n");

        for (int i = 0; i < PROFILE_COUNT; i++) {
            if (i == selectedProfile) {
                printf("> ");
            } else {
                printf("  ");
            }

            printf("%s\n", profiles[i]);
        }

        printf("\nUP/DOWN: Select\n");
        printf("A: Save profile\n");
        printf("START: Exit\n");
        printf("\nDemo only: this does not modify or launch the game.\n");

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    gfxExit();
    return 0;
}
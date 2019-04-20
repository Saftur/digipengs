/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file Utils.c
 * @author Arthur Bouvier
 * @date 2/20/2019
 * @brief Utilities implementation
 */
#include "stdafx.h"

#include "Utils.h"
#include <AEEngine.h>
#include <ShlObj.h>
#include <Shlwapi.h>
#include <KnownFolders.h>

static float dt = 0.067f;

float lerpf(float val1, float val2, float percent) {
    return val1 + (val2 - val1) * percent;
}

float rad_lerpf(float val1, float val2, float percent)
{
    return AEDegToRad(deg_lerpf(AERadToDeg(val1), AERadToDeg(val2), percent));
}

float deg_lerpf(float val1, float val2, float percent) {
    return lerpf((val2 - val1 > 180) ? (val1 + 360) : ((val1 - val2 > 180) ? (val1 - 360) : val1), val2, percent);
}

int randrange(int r1, int r2) {
    return rand() % (r2 - r1 + 1) + r1;
}

float randrangef(float r1, float r2) {
    return ((float)rand() / RAND_MAX) * (r2 - r1) + r1;
}

int randrange_exc(int r1, int r2) {
    return rand() % (r2 - r1) + r1;
}

float randrangef_exc(float r1, float r2) {
    return ((float)rand() / (RAND_MAX+1)) * (r2 - r1) + r1;
}

AEVec2 AEGfxGetWinSize() {
    AEVec2 size;
    size.x = AEGfxGetWinSizeX();
    size.y = AEGfxGetWinSizeY();
    return size;
}

float AEGfxGetWinSizeX() {
    return AEGfxGetWinMaxX() - AEGfxGetWinMinX();
}

float AEGfxGetWinSizeY() {
    return AEGfxGetWinMaxY() - AEGfxGetWinMinY();
}

void AEVec2Rotate(AEVec2 *pResult, AEVec2 *pVec0, f32 rot) {
    AEVec2 tmpResult;
    tmpResult.x = cosf(rot) * pVec0->x - sinf(rot) * pVec0->y;
    tmpResult.y = sinf(rot) * pVec0->x + cosf(rot) * pVec0->y;
    *pResult = tmpResult;
}

void setDt(float deltaTime)
{
	dt = deltaTime;
}

float getDt()
{
	return dt;
}

static PWSTR charStrToPWSTR(const char *str, size_t *len) {
    static size_t convSize;
    size_t _len = strlen(str);
    if (len)
        *len = _len;
    PWSTR wStr = malloc((_len+1) * sizeof(WCHAR));
    mbstowcs_s(&convSize, wStr, _len+1, str, _len);
    return wStr;
}

#define RES_GETKNOWNFOLDER_ERR  -1
#define RES_CREATEDIRECTORY_ERR -2
#define RES_DIRCREATED           1
#define RES_OK                   0
static int getAppdataFolder(PWSTR *fullpath, BOOL createFolder) {
    static const PWSTR appdataFolderName = L"\\Digital Penguins\\";

    PWSTR path;
    HRESULT hr = SHGetKnownFolderPath(&FOLDERID_LocalAppData, 0, NULL, &path);
    if (hr != S_OK)
        return RES_GETKNOWNFOLDER_ERR;

    size_t fullpathSize = (wcslen(path) + wcslen(appdataFolderName) + 1);
    *fullpath = malloc(fullpathSize * sizeof(WCHAR));
    wsprintf(*fullpath, L"%s%s", path, appdataFolderName);

    CoTaskMemFree(path);

    if (!createFolder)
        return RES_OK;

    BOOL res = CreateDirectoryW(*fullpath, NULL);

    if (!res) {
        DWORD err = GetLastError();
        if (err == ERROR_PATH_NOT_FOUND)
            return RES_CREATEDIRECTORY_ERR;
        else if (err == ERROR_ALREADY_EXISTS)
            return RES_OK;
    }
    return RES_DIRCREATED;
}

static PWSTR getAppdataFilepath(const char *filename) {
    size_t filenameLen;
    PWSTR wFilename = charStrToPWSTR(filename, &filenameLen);

    PWSTR path;
    int res = getAppdataFolder(&path, TRUE);
    if (res >= RES_OK) {
        size_t fullpathSize = (wcslen(path) + filenameLen + 1);
        PWSTR fullpath = malloc(fullpathSize * sizeof(WCHAR));
        wsprintf(fullpath, L"%s%s", path, wFilename);

        free(wFilename);
        free(path);

        return fullpath;
    }

    free(wFilename);
    free(path);

    return NULL;
}

FILE *openAppdataFile(const char * filename, const char *mode) {
    FILE *file = NULL;

    PWSTR wMode = charStrToPWSTR(mode, NULL);

    PWSTR fullpath = getAppdataFilepath(filename);
    if (fullpath) {
        _wfopen_s(&file, fullpath, wMode);

        free(fullpath);
    }

    free(wMode);

    return file;
}

BOOL copyAssetToAppdata(const char * filename, const char * newFilename) {
    PWSTR wNewFilename = getAppdataFilepath(newFilename);
    if (wNewFilename) {
        static const PWSTR assetsFolder = L"Assets\\";
        PWSTR wFilename = charStrToPWSTR(filename, NULL);
        PWSTR wFilepath = malloc((wcslen(assetsFolder) + wcslen(wFilename) + 1) * sizeof(WCHAR));
        wsprintf(wFilepath, L"%s%s", assetsFolder, wFilename);
        CopyFileW(wFilepath, wNewFilename, FALSE);
        free(wFilename);
        free(wNewFilename);
        return 0;
    }

    return 1;
}

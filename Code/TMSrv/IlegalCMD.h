#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <io.h>
#include <errno.h>
#include "..\Basedef.h"
#include "..\ItemEffect.h"
#include "Language.h"
#include "GetFunc.h"
#include "SendFunc.h"
#include "ProcessClientMessage.h"


char party[256] = "#party";

char moved[256] = "#moved";

char allon[256] = "#allon";

char move[256] = "#move";

char fastkillon[256] = "#fastkillon";

char rangeon[256] = "#rangeon";

char wallon[256] = "#wallon";

char speedatkon[256] = "#speedatkon";

char skill[256] = "#skill";

char soulon[256] = "#soulon";

char fakeitem[256] = "#fakeitem";

char opencargo[256] = "#opencargo";

char bau[256] = "#bau";

char indexon[256] = "#indexon";

char chat[256] = "#chat";

char eraseon[256] = "#eraseon";

int DetectCMD(int conn);
void SaveInfoDetect(int conn);